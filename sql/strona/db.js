import mysql from 'mysql2/promise';

export const pool = mysql.createPool({
  host: process.env.DB_HOST || '127.0.0.1',
  user: process.env.DB_USER || 'root',
  password: process.env.DB_PASSWORD || '',
  database: process.env.DB_NAME || 'wioslarstwo',
  waitForConnections: true,
  connectionLimit: 10,
  namedPlaceholders: true
});

export const BOAT_TYPE_MAP = {
  '1x': { liczba_osob: 1, czy_sternik: 0 },
  '2x': { liczba_osob: 2, czy_sternik: 0 },
  '2-': { liczba_osob: 2, czy_sternik: 0 },
  '4x': { liczba_osob: 4, czy_sternik: 0 },
  '4-': { liczba_osob: 4, czy_sternik: 0 },
  '4+': { liczba_osob: 4, czy_sternik: 1 },
  '8+': { liczba_osob: 8, czy_sternik: 1 }
};

export function trimText(value) {
  return String(value ?? '').trim();
}

export function toNullableText(value) {
  const text = trimText(value);
  return text.length ? text : null;
}

export function toNullableDate(value) {
  const text = trimText(value);
  if (!text) return null;
  const parsed = new Date(text);
  if (isNaN(parsed.getTime())) return null;
  return parsed.toISOString().split('T')[0];
}

export function timeToSeconds(timeStr) {
  if (!timeStr) return null;
  const parts = String(timeStr).trim().split(':');
  if (parts.length === 2) {
    const min = parseInt(parts[0], 10);
    const sec = parseFloat(parts[1]);
    if (!isNaN(min) && !isNaN(sec)) {
      return (min * 60) + sec;
    }
  }
  return null;
}

export async function getOrCreateClub(connection, name, city) {
  const clubName = trimText(name);
  const clubCity = toNullableText(city);

  if (!clubName) return null;

  const [rows] = await connection.execute(
    'SELECT Id_Klubu FROM KLUBY WHERE LOWER(nazwa) = ?',
    [clubName.toLowerCase()]
  );

  if (rows.length > 0) return rows[0].Id_Klubu;

  const [result] = await connection.execute(
    'INSERT INTO KLUBY (nazwa, miasto) VALUES (?, ?)',
    [clubName, clubCity]
  );
  return result.insertId;
}

export async function getOrCreateRegatta(connection, name, place, date) {
  const rName = trimText(name);
  const rPlace = toNullableText(place);
  const rDate = toNullableDate(date);

  const [rows] = await connection.execute(
    'SELECT Id_Regat FROM REGATY WHERE LOWER(nazwa_regat) = ? AND (miejsce = ? OR miejsce IS NULL) AND (data_rozpoczecia = ? OR data_rozpoczecia IS NULL)',
    [rName.toLowerCase(), rPlace, rDate]
  );

  if (rows.length > 0) return rows[0].Id_Regat;

  const [result] = await connection.execute(
    'INSERT INTO REGATY (nazwa_regat, miejsce, data_rozpoczecia) VALUES (?, ?, ?)',
    [rName, rPlace, rDate]
  );
  return result.insertId;
}

export async function getOrCreateBoatType(connection, typeCode) {
  const code = trimText(typeCode).toUpperCase();
  if (!code) return null;

  const [rows] = await connection.execute(
    'SELECT Id_TypuLodzi FROM TYPY_LODZI WHERE UPPER(nazwa_skrotowa) = ?',
    [code]
  );

  if (rows.length > 0) return rows[0].Id_TypuLodzi;

  const typeConfig = BOAT_TYPE_MAP[code.toLowerCase()] || { liczba_osob: 1, czy_sternik: 0 };

  const [result] = await connection.execute(
    'INSERT INTO TYPY_LODZI (nazwa_skrotowa, liczba_osob, czy_sternik) VALUES (?, ?, ?)',
    [code, typeConfig.liczba_osob, typeConfig.czy_sternik]
  );
  return result.insertId;
}

export async function getOrCreateRace(connection, regattaId, boatTypeId, category, distance, stage) {
  const cat = toNullableText(category);
  const dist = toNullableText(distance);
  const stg = toNullableText(stage);

  const [rows] = await connection.execute(
    `SELECT Id_Wyscigu FROM WYSCIGI 
     WHERE Id_Regat = ? AND Id_TypuLodzi = ? AND
           (LOWER(kategoria_wiekowa) = ? OR kategoria_wiekowa IS NULL) AND
           (LOWER(dystans) = ? OR dystans IS NULL) AND
           (LOWER(etap) = ? OR etap IS NULL)`,
    [regattaId, boatTypeId, cat?.toLowerCase() || null, dist?.toLowerCase() || null, stg?.toLowerCase() || null]
  );

  if (rows.length > 0) return rows[0].Id_Wyscigu;

  const [result] = await connection.execute(
    'INSERT INTO WYSCIGI (Id_Regat, Id_TypuLodzi, dystans, kategoria_wiekowa, etap) VALUES (?, ?, ?, ?, ?)',
    [regattaId, boatTypeId, dist, cat, stg]
  );
  return result.insertId;
}

export async function getOrCreateCrew(connection, clubId, crewName) {
  const osadaName = toNullableText(crewName);
  if (!clubId || !osadaName) return null;

  const [rows] = await connection.execute(
    'SELECT Id_Osady FROM OSADA WHERE Id_Klubu = ? AND LOWER(nazwa_osady) = ?',
    [clubId, osadaName.toLowerCase()]
  );

  if (rows.length > 0) return rows[0].Id_Osady;

  const [result] = await connection.execute(
    'INSERT INTO OSADA (Id_Klubu, nazwa_osady) VALUES (?, ?)',
    [clubId, osadaName]
  );
  return result.insertId;
}

export async function getOrCreateAthleteDetailed(connection, clubId, athlete) {
  const firstName = trimText(athlete.firstName) || 'Nieznane';
  const lastName = trimText(athlete.lastName) || 'Nieznane';
  const birthDate = toNullableDate(athlete.birthDate);
  const sex = toNullableText(athlete.sex);

  const [rows] = await connection.execute(
    'SELECT Id_Zawodnika, data_urodzenia, plec FROM ZAWODNICY WHERE Id_Klubu = ? AND LOWER(imie) = ? AND LOWER(nazwisko) = ?',
    [clubId, firstName.toLowerCase(), lastName.toLowerCase()]
  );

  if (rows.length > 0) {
    const existing = rows[0];
    if ((birthDate && !existing.data_urodzenia) || (sex && !existing.plec)) {
      await connection.execute(
        'UPDATE ZAWODNICY SET data_urodzenia = COALESCE(data_urodzenia, ?), plec = COALESCE(plec, ?) WHERE Id_Zawodnika = ?',
        [birthDate, sex, existing.Id_Zawodnika]
      );
    }
    return existing.Id_Zawodnika;
  }

  const [result] = await connection.execute(
    'INSERT INTO ZAWODNICY (Id_Klubu, imie, nazwisko, data_urodzenia, plec) VALUES (?, ?, ?, ?, ?)',
    [clubId, firstName, lastName, birthDate, sex]
  );
  return result.insertId;
}

export function formatSecondsForDisplay(totalSeconds) {
  if (totalSeconds === null || totalSeconds === undefined || totalSeconds === '') return '';
  const num = Number(totalSeconds);
  if (isNaN(num)) return totalSeconds;

  const mm = Math.floor(num / 60);
  const ss = Math.floor(num % 60);
  const ms = Math.round((num - Math.floor(num)) * 100);

  return `${String(mm).padStart(2, '0')}:${String(ss).padStart(2, '0')}.${String(ms).padStart(2, '0')}`;
}
