  
    const statusBox = document.getElementById('statsStatus');
    const kpiStarts = document.getElementById('kpiStarts');
    const kpiRegattas = document.getElementById('kpiRegattas');
    const kpiClubs = document.getElementById('kpiClubs');
    const kpiAthletes = document.getElementById('kpiAthletes');

    function setStatus(title, text, type) {
      statusBox.querySelector('.status-title').textContent = title;
      statusBox.querySelector('.status-text').textContent = text;
      statusBox.classList.remove('success', 'error');
      if (type) statusBox.classList.add(type);
    }

    function formatNumber(value) {
      return Number(value || 0).toLocaleString('pl-PL');
    }

    function normalizeSeries(series) {
      if (!Array.isArray(series)) return [];
      return series
        .map((item) => ({
          label: String(item.label || 'Brak danych'),
          value: Number(item.value || 0)
        }))
        .filter((item) => item.value > 0);
    }

    function getPalette(length) {
      const base = [
        '#0f766e',
        '#1d4ed8',
        '#c2410c',
        '#0f172a',
        '#16a34a',
        '#a21caf',
        '#0369a1',
        '#be123c',
        '#4338ca',
        '#b45309'
      ];
      return Array.from({ length }, (_, i) => base[i % base.length]);
    }

    function renderBars(containerId, series) {
      const root = document.getElementById(containerId);
      if (!root) return;

      if (!series.length) {
        root.innerHTML = '<p class="helper">Brak danych do wyswietlenia.</p>';
        return;
      }

      const maxValue = Math.max(...series.map((item) => item.value), 1);
      root.innerHTML = series
        .map((item) => {
          const width = Math.max(4, Math.round((item.value / maxValue) * 100));
          return `
            <div class="bar-row">
              <div class="bar-head">
                <span class="bar-label">${item.label}</span>
                <strong class="bar-value">${item.value}</strong>
              </div>
              <div class="bar-track">
                <span class="bar-fill" style="width:${width}%"></span>
              </div>
            </div>
          `;
        })
        .join('');
    }

    function renderDonut(containerId, series) {
      const root = document.getElementById(containerId);
      if (!root) return;

      if (!series.length) {
        root.innerHTML = '<p class="helper">Brak danych do wyswietlenia.</p>';
        return;
      }

      const total = series.reduce((sum, item) => sum + item.value, 0);
      const palette = getPalette(series.length);
      let current = 0;
      const slices = series
        .map((item, index) => {
          const start = current;
          const percent = (item.value / total) * 100;
          current += percent;
          return `${palette[index]} ${start.toFixed(2)}% ${current.toFixed(2)}%`;
        })
        .join(', ');

      const legend = series
        .map((item, index) => {
          const percent = total ? ((item.value / total) * 100).toFixed(1) : '0.0';
          return `
            <li class="donut-legend-item">
              <span class="donut-dot" style="background:${palette[index]}"></span>
              <span class="donut-text">${item.label}</span>
              <strong>${item.value} (${percent}%)</strong>
            </li>
          `;
        })
        .join('');

      root.innerHTML = `
        <div class="donut-layout">
          <div class="donut-ring" style="background:conic-gradient(${slices})"></div>
          <ul class="donut-legend">${legend}</ul>
        </div>
      `;
    }

    function renderCharts(stats) {
      const clubs = normalizeSeries(stats.clubs);
      const boats = normalizeSeries(stats.boats);
      const categories = normalizeSeries(stats.categories);
      const genders = normalizeSeries(stats.genders);

      renderBars('clubsChart', clubs);
      renderDonut('boatsChart', boats);
      renderBars('categoriesChart', categories);
      renderDonut('gendersChart', genders);
    }

    async function loadStats() {
      try {
        const response = await fetch('/api/stats');
        const payload = await response.json();

        if (!response.ok || !payload.success) {
          throw new Error(payload.error || 'Nie udalo sie pobrac danych statystycznych.');
        }

        const totals = payload.totals || {};
        kpiStarts.textContent = formatNumber(totals.totalStarts);
        kpiRegattas.textContent = formatNumber(totals.totalRegattas);
        kpiClubs.textContent = formatNumber(totals.totalClubs);
        kpiAthletes.textContent = formatNumber(totals.totalAthletes);

        renderCharts(payload);
        setStatus('Statystyki gotowe', 'Dane zostaly pobrane i zwizualizowane na wykresach.', 'success');
      } catch (error) {
        setStatus('Blad ladowania', error.message || 'Wystapil nieoczekiwany blad podczas pobierania danych.', 'error');
      }
    }

    loadStats();
