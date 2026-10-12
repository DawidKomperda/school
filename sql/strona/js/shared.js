// shared.js
// Plik zawiera globalne stałe i uniwersalne funkcje pomocnicze używane na stronach aplikacji.

// Słownik określający maksymalną liczbę zawodników dla danego typu łodzi.
const BOAT_TYPE_LIMITS = {
  '1x': 1,
  '2x': 2,
  '2-': 2,
  '4x': 4,
  '4-': 4,
  '4+': 4,
  '8+': 8
};

// Funkcja zabezpieczająca przed atakami XSS poprzez zamianę znaków specjalnych HTML na ich encje.
function escapeHtml(value) {
  return String(value ?? '')
    .replace(/&/g, '&amp;')
    .replace(/</g, '&lt;')
    .replace(/>/g, '&gt;')
    .replace(/"/g, '&quot;')
    .replace(/'/g, '&#039;');
}

// Funkcja formatująca czas w sekundach na format minutowy i sekundowy (mm:ss.setne).
function formatSecondsForDisplay(totalSeconds) {
  if (totalSeconds === null || totalSeconds === undefined || totalSeconds === '') return '';
  const num = Number(totalSeconds);
  if (isNaN(num)) return totalSeconds;

  const mm = Math.floor(num / 60);
  const ss = Math.floor(num % 60);
  const ms = Math.round((num - Math.floor(num)) * 100);

  return `${String(mm).padStart(2, '0')}:${String(ss).padStart(2, '0')}.${String(ms).padStart(2, '0')}`;
}
