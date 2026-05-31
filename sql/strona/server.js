import express from 'express';
import path from 'path';
import { fileURLToPath } from 'url';
import {
  pool,
  trimText,
  toNullableText,
  getOrCreateClub,
  getOrCreateRegatta,
  getOrCreateBoatType,
  getOrCreateRace,
  getOrCreateCrew,
  getOrCreateAthleteDetailed,
  timeToSeconds,
  formatSecondsForDisplay
} from './db.js';

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

const app = express();
const port = process.env.PORT || 3000;

app.use(express.json());
app.use(express.static(__dirname));

function splitAthleteQueries(value) {
  return String(value || '')
    .split(/[,.;\n]+/)
    .map((part) => part.trim())
    .filter(Boolean);
}

function mapRowsToListRecord(rows) {
  const firstRow = rows[0];
  const athletes = [];
  const athleteSexes = [];

  rows.forEach((row) => {
    if (row.imie || row.nazwisko) {
      athletes.push([row.imie, row.nazwisko].filter(Boolean).join(' ').trim());
      athleteSexes.push(row.plec || '');
    }
  });

  return {
    startId: firstRow.startId,
    dateIso: firstRow.dateIso,
    date: firstRow.date,
    regatta: firstRow.regattaName,
    regattaPlace: firstRow.regattaPlace,
    boatType: firstRow.boatType,
    category: firstRow.category,
    distance: firstRow.distance,
    stage: firstRow.stage,
    lane: firstRow.lane || '',
    place: firstRow.place ?? null,
    crew: firstRow.crewName,
    club: firstRow.clubName,
    clubCity: firstRow.clubCity,
    athletes,
    athleteSexes,
    time: firstRow.timeValue || ''
  };
}

function mapRowsToDetailRecord(rows) {
  const firstRow = rows[0];
  const athletes = rows
    .filter((row) => row.imie || row.nazwisko)
    .map((row) => ({
      firstName: row.imie || '',
      lastName: row.nazwisko || '',
      birthDate: row.birthDateIso || '',
      sex: row.plec || '',
      position: row.pozycja || null
    }));

  return {
    startId: firstRow.startId,
    raceId: firstRow.raceId,
    regattaId: firstRow.regattaId,
    boatTypeId: firstRow.boatTypeId,
    crewId: firstRow.crewId,
    clubId: firstRow.clubId,
    dateIso: firstRow.dateIso,
    date: firstRow.date,
    regattaName: firstRow.regattaName,
    regattaPlace: firstRow.regattaPlace,
    boatType: firstRow.boatType,
    category: firstRow.category,
    distance: firstRow.distance,
    stage: firstRow.stage,
    lane: firstRow.lane || '',
    place: firstRow.place ?? null,
    crewName: firstRow.crewName,
    clubName: firstRow.clubName,
    clubCity: firstRow.clubCity,
    athletes,
    time: firstRow.timeValue || ''
  };
}

function groupRowsByStart(rows) {
  const grouped = new Map();
  rows.forEach((row) => {
    if (!grouped.has(row.startId)) {
      grouped.set(row.startId, []);
    }
    grouped.get(row.startId).push(row);
  });
  return grouped;
}

const SELECT_START_DETAILS_SQL = `
  SELECT 
    S.Id_Startu AS startId,
    W.Id_Wyscigu AS raceId,
    REG.Id_Regat AS regattaId,
    T.Id_TypuLodzi AS boatTypeId,
    O.Id_Osady AS crewId,
    K.Id_Klubu AS clubId,
    REG.data_rozpoczecia AS dateIso,
    DATE_FORMAT(REG.data_rozpoczecia, '%d.%m.%Y') AS date,
    REG.nazwa_regat AS regattaName,
    REG.miejsce AS regattaPlace,
    T.nazwa_skrotowa AS boatType,
    W.kategoria_wiekowa AS category,
    W.dystans AS distance,
    W.etap AS stage,
    S.tor_u AS lane,
    S.miejsce AS place,
    O.nazwa_osady AS crewName,
    K.nazwa AS clubName,
    K.miasto AS clubCity,
    Z.imie,
    Z.nazwisko,
    DATE_FORMAT(Z.data_urodzenia, '%Y-%m-%d') AS birthDateIso,
    Z.plec,
    SK.pozycja,
    CASE
      WHEN S.czas IS NULL THEN ''
      ELSE CONCAT(
        LPAD(FLOOR(S.czas / 60), 2, '0'),
        ':',
        LPAD(FLOOR(MOD(S.czas, 60)), 2, '0'),
        '.',
        LPAD(ROUND((S.czas - FLOOR(S.czas)) * 100), 2, '0')
      )
    END AS timeValue
  FROM START S
  JOIN WYSCIGI W ON S.Id_Wyscigu = W.Id_Wyscigu
  JOIN REGATY REG ON W.Id_Regat = REG.Id_Regat
  JOIN TYPY_LODZI T ON W.Id_TypuLodzi = T.Id_TypuLodzi
  JOIN OSADA O ON S.Id_Osady = O.Id_Osady
  JOIN KLUBY K ON O.Id_Klubu = K.Id_Klubu
  LEFT JOIN SKLAD_START SK ON S.Id_Startu = SK.Id_Startu
  LEFT JOIN ZAWODNICY Z ON SK.Id_Zawodnika = Z.Id_Zawodnika
`;

app.get('/api/records', async (req, res) => {
  try {
    const regattaName = trimText(req.query.regattaName);
    const regattaPlace = trimText(req.query.regattaPlace);
    const raceDate = trimText(req.query.raceDate || req.query.date);
    const boatType = trimText(req.query.boatType);
    const categoryDistance = trimText(req.query.categoryDistance);
    const raceDistance = trimText(req.query.raceDistance);
    const raceStage = trimText(req.query.raceStage || req.query.stage);
    const athleteName = trimText(req.query.athleteName);
    const athleteSex = trimText(req.query.athleteSex);
    const clubName = trimText(req.query.clubName);
    const clubCity = trimText(req.query.clubCity);
    const lane = trimText(req.query.lane);
    const finishPlace = trimText(req.query.place);
    const raceTime = trimText(req.query.raceTime || req.query.time);

    const where = [];
    const params = [];

    if (regattaName) {
      where.push('REG.nazwa_regat LIKE ?');
      params.push(`%${regattaName}%`);
    }

    if (regattaPlace) {
      where.push('REG.miejsce LIKE ?');
      params.push(`%${regattaPlace}%`);
    }

    if (raceDate) {
      where.push("DATE_FORMAT(REG.data_rozpoczecia, '%Y-%m-%d') = ?");
      params.push(raceDate);
    }

    if (boatType) {
      where.push('T.nazwa_skrotowa LIKE ?');
      params.push(`%${boatType}%`);
    }

    if (categoryDistance) {
      where.push('CONCAT(W.kategoria_wiekowa, " / ", W.dystans) = ?');
      params.push(categoryDistance);
    }

    if (raceDistance) {
      where.push('W.dystans LIKE ?');
      params.push(`%${raceDistance}%`);
    }

    if (raceStage) {
      where.push('W.etap LIKE ?');
      params.push(`%${raceStage}%`);
    }

    if (athleteSex) {
      where.push('EXISTS (SELECT 1 FROM SKLAD_START SK2 JOIN ZAWODNICY Z2 ON Z2.Id_Zawodnika = SK2.Id_Zawodnika WHERE SK2.Id_Startu = S.Id_Startu AND Z2.plec = ?)');
      params.push(athleteSex);
    }

    if (clubName) {
      where.push('(K.nazwa LIKE ? OR O.nazwa_osady LIKE ?)');
      params.push(`%${clubName}%`, `%${clubName}%`);
    }

    if (clubCity) {
      where.push('K.miasto LIKE ?');
      params.push(`%${clubCity}%`);
    }

    if (lane) {
      where.push('S.tor_u LIKE ?');
      params.push(`%${lane}%`);
    }

    if (finishPlace) {
      where.push('CAST(S.miejsce AS CHAR) LIKE ?');
      params.push(`%${finishPlace}%`);
    }

    if (raceTime) {
      where.push('CAST(S.czas AS CHAR) LIKE ?');
      params.push(`%${raceTime}%`);
    }

    const athleteQueries = splitAthleteQueries(athleteName);
    athleteQueries.forEach((query) => {
      where.push('EXISTS (SELECT 1 FROM SKLAD_START SK3 JOIN ZAWODNICY Z3 ON Z3.Id_Zawodnika = SK3.Id_Zawodnika WHERE SK3.Id_Startu = S.Id_Startu AND (CONCAT(Z3.imie, " ", Z3.nazwisko) LIKE ? OR CONCAT(Z3.nazwisko, " ", Z3.imie) LIKE ? OR Z3.imie LIKE ? OR Z3.nazwisko LIKE ?))');
      params.push(`%${query}%`, `%${query}%`, `%${query}%`, `%${query}%`);
    });

    const sql = `${SELECT_START_DETAILS_SQL}
      ${where.length ? `WHERE ${where.join(' AND ')}` : ''}
      ORDER BY REG.data_rozpoczecia DESC, S.Id_Startu DESC, SK.pozycja ASC`;

    const [rows] = await pool.execute(sql, params);

    const grouped = groupRowsByStart(rows);
    const results = Array.from(grouped.values()).map(mapRowsToListRecord);

    res.json({ count: results.length, results });
  } catch (error) {
    res.status(500).json({ message: 'Nie udało się pobrać rekordów.', error: error.message });
  }
});

app.get('/api/records/:startId', async (req, res) => {
  try {
    const [rows] = await pool.execute(
      `${SELECT_START_DETAILS_SQL}
       WHERE S.Id_Startu = ?
       ORDER BY SK.pozycja ASC`,
      [req.params.startId]
    );

    if (!rows.length) {
      return res.status(404).json({ message: 'Nie znaleziono rekordu.' });
    }

    res.json({ record: mapRowsToDetailRecord(rows) });
  } catch (error) {
    res.status(500).json({ message: 'Nie udało się pobrać rekordu.', error: error.message });
  }
});

app.put('/api/records/:startId', async (req, res) => {
  const connection = await pool.getConnection();

  try {
    await connection.beginTransaction();

    const startId = req.params.startId;
    const body = req.body || {};

    const regattaId = await getOrCreateRegatta(connection, body.regattaName, body.regattaPlace, body.raceDate);
    const boatTypeId = await getOrCreateBoatType(connection, body.boatType || '1x');
    const raceId = await getOrCreateRace(connection, regattaId, boatTypeId, body.category, body.distance, body.stage);
    const clubId = await getOrCreateClub(connection, body.clubName, body.clubCity);
    const crewId = await getOrCreateCrew(connection, clubId, body.crewName);

    const timeSecs = timeToSeconds(body.time);

    await connection.execute(
      'UPDATE START SET Id_Wyscigu = ?, Id_Osady = ?, czas = ?, miejsce = ?, tor_u = ? WHERE Id_Startu = ?',
      [raceId, crewId, timeSecs, toNullableText(body.place), toNullableText(body.lane), startId]
    );

    await connection.execute('DELETE FROM SKLAD_START WHERE Id_Startu = ?', [startId]);

    if (Array.isArray(body.athletes)) {
      for (const [i, a] of body.athletes.entries()) {
        const athId = await getOrCreateAthleteDetailed(connection, clubId, a);
        await connection.execute(
          'INSERT INTO SKLAD_START (Id_Zawodnika, Id_Startu, pozycja) VALUES (?, ?, ?)',
          [athId, startId, String(i + 1)]
        );
      }
    }

    await connection.commit();

    const [rows] = await connection.execute(
      `${SELECT_START_DETAILS_SQL}
       WHERE S.Id_Startu = ?
       ORDER BY SK.pozycja ASC`,
      [startId]
    );

    res.json({
      title: 'Zmiany zapisane',
      message: 'Rekord został zaktualizowany.',
      record: rows.length ? mapRowsToDetailRecord(rows) : null
    });
  } catch (err) {
    await connection.rollback();
    res.status(500).json({ message: 'Nie udało się zapisać zmian.', error: err.message });
  } finally {
    connection.release();
  }
});

app.post('/api/records', async (req, res) => {
  const connection = await pool.getConnection();

  try {
    await connection.beginTransaction();

    const {
      regattaName,
      regattaPlace,
      raceDate,
      category,
      distance,
      stage,
      boatType,
      crews = []
    } = req.body || {};

    const regattaId = await getOrCreateRegatta(connection, regattaName, regattaPlace, raceDate);
    const boatTypeId = await getOrCreateBoatType(connection, boatType);
    const raceId = await getOrCreateRace(connection, regattaId, boatTypeId, category, distance, stage);

    const insertedStarts = [];

    for (const crew of crews) {
      const clubId = await getOrCreateClub(connection, crew.clubName, crew.clubCity);
      const crewId = await getOrCreateCrew(connection, clubId, crew.crewName);

      const [startRes] = await connection.execute(
        'INSERT INTO START (Id_Wyscigu, Id_Osady, czas, miejsce, tor_u) VALUES (?, ?, ?, ?, ?)',
        [
          raceId,
          crewId,
          timeToSeconds(crew.time),
          toNullableText(crew.place),
          toNullableText(crew.lane)
        ]
      );

      const startId = startRes.insertId;

      const athletes = Array.isArray(crew.athletes) ? crew.athletes : [];
      for (let index = 0; index < athletes.length; index += 1) {
        const athleteId = await getOrCreateAthleteDetailed(connection, clubId, athletes[index]);
        await connection.execute(
          'INSERT INTO SKLAD_START (Id_Zawodnika, Id_Startu, pozycja) VALUES (?, ?, ?)',
          [athleteId, startId, String(index + 1)]
        );
      }

      insertedStarts.push({
        startId,
        crewName: crew.crewName,
        clubName: crew.clubName,
        lane: toNullableText(crew.lane),
        place: toNullableText(crew.place),
        time: formatSecondsForDisplay(timeToSeconds(crew.time)),
        athletes
      });
    }

    await connection.commit();

    res.status(201).json({
      message: 'Dane zostaly zapisane.',
      startId: insertedStarts[0]?.startId || null,
      summary: {
        regattaName,
        regattaPlace,
        raceDate,
        category,
        distance,
        boatType,
        crews: insertedStarts,
        crewName: insertedStarts[0]?.crewName || null,
        clubName: insertedStarts[0]?.clubName || null,
        lane: insertedStarts[0]?.lane || null,
        place: insertedStarts[0]?.place || null,
        time: insertedStarts[0]?.time || '',
        athletes: insertedStarts[0]?.athletes || []
      }
    });
  } catch (err) {
    await connection.rollback();
    res.status(500).json({ message: 'Nie udało się zapisać danych.', error: err.message });
  } finally {
    connection.release();
  }
});

app.get('/api/stats', async (req, res) => {
  try {
    const [[totals]] = await pool.execute(`
      SELECT
        (SELECT COUNT(*) FROM START) AS totalStarts,
        (SELECT COUNT(*) FROM REGATY) AS totalRegattas,
        (SELECT COUNT(*) FROM KLUBY) AS totalClubs,
        (SELECT COUNT(*) FROM ZAWODNICY) AS totalAthletes
    `);
    const [clubStats] = await pool.execute(`
      SELECT K.nazwa AS label, COUNT(S.Id_Startu) AS value FROM START S JOIN OSADA O ON S.Id_Osady = O.Id_Osady JOIN KLUBY K ON O.Id_Klubu = K.Id_Klubu GROUP BY K.Id_Klubu, K.nazwa ORDER BY value DESC LIMIT 10
    `);
    const [boatStats] = await pool.execute(`
      SELECT T.nazwa_skrotowa AS label, COUNT(S.Id_Startu) AS value FROM START S JOIN WYSCIGI W ON S.Id_Wyscigu = W.Id_Wyscigu JOIN TYPY_LODZI T ON W.Id_TypuLodzi = T.Id_TypuLodzi GROUP BY T.Id_TypuLodzi, T.nazwa_skrotowa ORDER BY value DESC
    `);
    const [categoryStats] = await pool.execute(`
      SELECT W.kategoria_wiekowa AS label, COUNT(S.Id_Startu) AS value FROM START S JOIN WYSCIGI W ON S.Id_Wyscigu = W.Id_Wyscigu WHERE W.kategoria_wiekowa IS NOT NULL AND TRIM(W.kategoria_wiekowa) <> '' GROUP BY W.kategoria_wiekowa ORDER BY value DESC
    `);
    const [genderStats] = await pool.execute(`
      SELECT plec AS label, COUNT(Id_Zawodnika) AS value FROM ZAWODNICY WHERE plec IS NOT NULL GROUP BY plec
    `);

    res.json({
      success: true,
      totals,
      clubs: clubStats,
      boats: boatStats,
      categories: categoryStats,
      genders: genderStats
    });
  } catch (error) {
    res.status(500).json({ success: false, error: 'Błąd bazy danych' });
  }
});

app.listen(port, () => {
  console.log(`Server listening on http://127.0.0.1:${port}`);
});
