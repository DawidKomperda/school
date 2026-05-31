// shared.js
// Global constants and generic helper functions

const BOAT_TYPE_LIMITS = {
  '1x': 1,
  '2x': 2,
  '2-': 2,
  '4x': 4,
  '4-': 4,
  '4+': 4,
  '8+': 8
};

function escapeHtml(value) {
  return String(value ?? '')
    .replace(/&/g, '&amp;')
    .replace(/</g, '&lt;')
    .replace(/>/g, '&gt;')
    .replace(/"/g, '&quot;')
    .replace(/'/g, '&#039;');
}

function formatSecondsForDisplay(totalSeconds) {
  if (totalSeconds === null || totalSeconds === undefined || totalSeconds === '') return '';
  const num = Number(totalSeconds);
  if (isNaN(num)) return totalSeconds;

  const mm = Math.floor(num / 60);
  const ss = Math.floor(num % 60);
  const ms = Math.round((num - Math.floor(num)) * 100);

  return `${String(mm).padStart(2, '0')}:${String(ss).padStart(2, '0')}.${String(ms).padStart(2, '0')}`;
}
