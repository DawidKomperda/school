  
    const form = document.getElementById("searchForm");
    const regattaNameInput = document.getElementById("regattaName");
    const regattaPlaceInput = document.getElementById("regattaPlace");
    const raceDateInput = document.getElementById("raceDate");
    const boatTypeInput = document.getElementById("boatType");
    const categoryDistanceSelect = document.getElementById("categoryDistance");
    const raceDistanceInput = document.getElementById("raceDistance");
    const raceStageInput = document.getElementById("raceStage");
    const athleteNameInput = document.getElementById("athleteName");
    const athleteSexInput = document.getElementById("athleteSex");
    const clubNameInput = document.getElementById("clubName");
    const clubCityInput = document.getElementById("clubCity");
    const laneInput = document.getElementById("lane");
    const placeInput = document.getElementById("place");
    const raceTimeInput = document.getElementById("raceTime");
    const resultsBody = document.getElementById("resultsBody");
    const emptyState = document.getElementById("emptyState");
    const resultsBar = document.getElementById("resultsBar");
    const resultsCount = document.getElementById("resultsCount");
    const clearFilters = document.getElementById("clearFilters");
    const exportCsvButton = document.getElementById("exportCsv");
    const exportPdfButton = document.getElementById("exportPdf");
    const datalist = document.getElementById("regattaHints");

    let currentRecords = [];
    let currentFilters = {
      regattaName: "",
      regattaPlace: "",
      raceDate: "",
      boatType: "",
      categoryDistance: "",
      raceDistance: "",
      raceStage: "",
      athleteName: "",
      athleteSex: "",
      clubName: "",
      clubCity: "",
      lane: "",
      place: "",
      raceTime: ""
    };

    function matchesText(source, query) {
      return String(source || "").toLowerCase().includes(String(query || "").toLowerCase());
    }

    function splitMultiValue(input) {
      return String(input || "")
        .split(/[,.\n;]+/)
        .map((value) => value.trim())
        .filter(Boolean);
    }

    function formatTime(value) {
      const text = String(value ?? "").trim();

      if (!text) {
        return "-";
      }

      if (text.includes(":")) {
        return text;
      }

      const numeric = Number(text);

      if (!Number.isFinite(numeric)) {
        return text;
      }

      const totalHundredths = Math.round(numeric * 100);
      const minutes = Math.floor(totalHundredths / 6000);
      const remainder = totalHundredths % 6000;
      const seconds = Math.floor(remainder / 100);
      const hundredths = remainder % 100;

      return `${String(minutes).padStart(2, "0")}:${String(seconds).padStart(2, "0")}.${String(hundredths).padStart(2, "0")}`;
    }

    function formatDateIso(value) {
      if (!value) {
        return "";
      }

      return value;
    }

    function csvEscape(value) {
      const text = String(value ?? "");
      return `"${text.replace(/"/g, '""')}"`;
    }

    function getDisplayRows(records) {
      return records.map((record) => ({
        ...record,
        time: formatTime(record.time)
      }));
    }

    function renderHints(records) {
      const regattaOptions = new Set();
      const categoryOptions = new Set();

      records.forEach((record) => {
        regattaOptions.add(record.regatta);
        regattaOptions.add(record.regattaPlace);
        categoryOptions.add(`${record.category} / ${record.distance}`);
      });

      datalist.innerHTML = "";
      Array.from(regattaOptions).sort().forEach((value) => {
        const option = document.createElement("option");
        option.value = value;
        datalist.appendChild(option);
      });

      const currentSelection = categoryDistanceSelect.value;
      const options = Array.from(categoryOptions).sort();
      categoryDistanceSelect.innerHTML = '<option value="">Wszystkie</option>';
      options.forEach((value) => {
        const option = document.createElement("option");
        option.value = value;
        option.textContent = value;
        categoryDistanceSelect.appendChild(option);
      });
      categoryDistanceSelect.value = options.includes(currentSelection) ? currentSelection : "";
    }

    function renderTable(records) {
      resultsBody.innerHTML = "";
      resultsBar.classList.add("visible");
      resultsCount.textContent = `Znaleziono ${records.length} wyników spełniających kryteria`;

      if (records.length === 0) {
        emptyState.style.display = "block";
        emptyState.innerHTML = Object.values(currentFilters).some(Boolean)
          ? "Brak wyników dla wybranych filtrów."
          : "Baza nie zawiera jeszcze żadnych rekordów do wyświetlenia.";
        return;
      }

      emptyState.style.display = "none";

      getDisplayRows(records).forEach((record) => {
        const row = document.createElement("tr");
        row.innerHTML = `
          <td>
            <strong>${record.date}</strong><br />
            <span class="muted">${record.regatta}</span>
            <div class="pill">${record.regattaPlace}</div>
          </td>
          <td>${record.boatType || "-"}</td>
          <td>${record.category}<br /><span class="muted">${record.distance}</span></td>
          <td>${record.stage || "-"}</td>
          <td>${record.lane}</td>
          <td>${record.place ?? "-"}</td>
          <td><strong>${record.crew}</strong><br /><span class="muted">(${record.club})</span></td>
          <td>${record.clubCity || "-"}</td>
          <td>${record.athletes.join(", ")}</td>
          <td><strong>${record.time}</strong></td>
        `;
        resultsBody.appendChild(row);
      });
    }

    function getFilteredRecords() {
      const athleteQueries = splitMultiValue(currentFilters.athleteName);

      return currentRecords.filter((record) => {
        const regattaNameMatch = !currentFilters.regattaName || matchesText(record.regatta, currentFilters.regattaName);
        const regattaPlaceMatch = !currentFilters.regattaPlace || matchesText(record.regattaPlace, currentFilters.regattaPlace);
        const dateMatch = !currentFilters.raceDate || formatDateIso(record.dateIso) === currentFilters.raceDate;
        const boatTypeMatch = !currentFilters.boatType || matchesText(record.boatType, currentFilters.boatType);
        const categoryMatch = !currentFilters.categoryDistance || `${record.category} / ${record.distance}` === currentFilters.categoryDistance;
        const distanceMatch = !currentFilters.raceDistance || matchesText(record.distance, currentFilters.raceDistance);
        const stageMatch = !currentFilters.raceStage || matchesText(record.stage, currentFilters.raceStage);
        const athleteMatch = athleteQueries.length === 0 || athleteQueries.some((query) => record.athletes.some((athlete) => matchesText(athlete, query)));
        const athleteSexMatch = !currentFilters.athleteSex || record.athleteSexes.some((sex) => matchesText(sex, currentFilters.athleteSex));
        const clubMatch = !currentFilters.clubName || matchesText(record.club, currentFilters.clubName) || matchesText(record.crew, currentFilters.clubName);
        const clubCityMatch = !currentFilters.clubCity || matchesText(record.clubCity, currentFilters.clubCity);
        const laneMatch = !currentFilters.lane || matchesText(record.lane, currentFilters.lane);
        const placeMatch = !currentFilters.place || matchesText(String(record.place || ""), currentFilters.place);
        const timeMatch = !currentFilters.raceTime || matchesText(formatTime(record.time), currentFilters.raceTime) || matchesText(String(record.time || ""), currentFilters.raceTime);

        return regattaNameMatch && regattaPlaceMatch && dateMatch && boatTypeMatch && categoryMatch && distanceMatch && stageMatch && athleteMatch && athleteSexMatch && clubMatch && clubCityMatch && laneMatch && placeMatch && timeMatch;
      });
    }

    function exportCsv(records) {
      const headers = [
        "Data i regaty",
        "Typ łodzi",
        "Wyścig (kat. / dystans)",
        "Etap",
        "Tor",
        "Miejsce",
        "Osada (klub)",
        "Miasto klubu",
        "Skład osady (zawodnicy)",
        "Czas"
      ];

      const rows = records.map((record) => [
        `${record.date} - ${record.regatta} (${record.regattaPlace})`,
        record.boatType || "",
        `${record.category} / ${record.distance}`,
        record.stage || "",
        record.lane,
        record.place,
        `${record.crew} (${record.club})`,
        record.clubCity || "",
        record.athletes.join(", "),
        formatTime(record.time)
      ]);

      const csv = [headers, ...rows]
        .map((row) => row.map(csvEscape).join(","))
        .join("\n");

      const blob = new Blob(["\uFEFF" + csv], { type: "text/csv;charset=utf-8;" });
      const url = URL.createObjectURL(blob);
      const link = document.createElement("a");
      link.href = url;
      link.download = "wyniki-regat.csv";
      link.click();
      URL.revokeObjectURL(url);
    }

    function exportPdf(records) {
      const printWindow = window.open("", "_blank", "width=1200,height=900");

      if (!printWindow) {
        alert("Przeglądarka zablokowała nowe okno. Zezwól na wyskakujące okna i spróbuj ponownie.");
        return;
      }

      const rows = records.map((record) => `
        <tr>
          <td>${record.date}<br><span>${record.regatta}</span><br><span>${record.regattaPlace}</span></td>
          <td>${record.boatType || "-"}</td>
          <td>${record.category}<br><span>${record.distance}</span></td>
          <td>${record.stage || "-"}</td>
          <td>${record.lane}</td>
          <td>${record.place}</td>
          <td>${record.crew}<br><span>(${record.club})</span></td>
          <td>${record.clubCity || "-"}</td>
          <td>${record.athletes.join(", ")}</td>
          <td>${formatTime(record.time)}</td>
        </tr>
      `).join("");

      printWindow.document.write(`
        <!DOCTYPE html>
        <html lang="pl">
        <head>
          <meta charset="UTF-8" />
          <title>Wyniki regat - PDF</title>
          <style>
            body { font-family: Arial, sans-serif; margin: 24px; color: #10243c; }
            h1 { margin: 0 0 10px; }
            p { margin: 0 0 18px; color: #51617d; }
            table { width: 100%; border-collapse: collapse; }
            th, td { border: 1px solid #cfd8e6; padding: 10px; text-align: left; vertical-align: top; }
            th { background: #eef4fb; }
            span { color: #51617d; }
          </style>
        </head>
        <body>
          <h1>Wyniki regat</h1>
          <p>Znaleziono ${records.length} wyników spełniających kryteria.</p>
          <table>
            <thead>
              <tr>
                <th>Data i regaty</th>
                <th>Typ łodzi</th>
                <th>Wyścig (kat. / dystans)</th>
                <th>Etap</th>
                <th>Tor</th>
                <th>Miejsce</th>
                <th>Osada (klub)</th>
                <th>Miasto klubu</th>
                <th>Skład osady (zawodnicy)</th>
                <th>Czas</th>
              </tr>
            </thead>
            <tbody>${rows}</tbody>
          </table>
          <script>
            window.onload = function () {
              window.focus();
              window.print();
            };
          <\/script>
        </body>
        </html>
      `);
      printWindow.document.close();
    }

    async function loadRecords(filters = {}) {
      const query = new URLSearchParams();

      if (filters.regattaName) query.set("regattaName", filters.regattaName);
      if (filters.regattaPlace) query.set("regattaPlace", filters.regattaPlace);
      if (filters.raceDate) query.set("date", filters.raceDate);
      if (filters.boatType) query.set("boatType", filters.boatType);
      if (filters.categoryDistance) query.set("categoryDistance", filters.categoryDistance);
      if (filters.raceDistance) query.set("raceDistance", filters.raceDistance);
      if (filters.raceStage) query.set("stage", filters.raceStage);
      if (filters.athleteName) query.set("athleteName", filters.athleteName);
      if (filters.athleteSex) query.set("athleteSex", filters.athleteSex);
      if (filters.clubName) query.set("clubName", filters.clubName);
      if (filters.clubCity) query.set("clubCity", filters.clubCity);
      if (filters.lane) query.set("lane", filters.lane);
      if (filters.place) query.set("place", filters.place);
      if (filters.raceTime) query.set("time", filters.raceTime);

      const response = await fetch(`/api/records?${query.toString()}`);
      const payload = await response.json();

      if (!response.ok) {
        throw new Error(payload.error || payload.message || "Błąd pobierania danych");
      }

      currentRecords = payload.results || [];

      if (!filters.regattaName && !filters.regattaPlace && !filters.categoryDistance && !filters.athleteName && !filters.clubName && !filters.raceDate && !filters.raceTime) {
        renderHints(currentRecords);
      }

      renderTable(currentRecords);
    }

    form.addEventListener("submit", async (event) => {
      event.preventDefault();
      currentFilters = {
        regattaName: regattaNameInput.value.trim(),
        regattaPlace: regattaPlaceInput.value.trim(),
        raceDate: raceDateInput.value.trim(),
        boatType: boatTypeInput.value.trim(),
        categoryDistance: categoryDistanceSelect.value.trim(),
        raceDistance: raceDistanceInput.value.trim(),
        raceStage: raceStageInput.value.trim(),
        athleteName: athleteNameInput.value.trim(),
        athleteSex: athleteSexInput.value.trim(),
        clubName: clubNameInput.value.trim(),
        clubCity: clubCityInput.value.trim(),
        lane: laneInput.value.trim(),
        place: placeInput.value.trim(),
        raceTime: raceTimeInput.value.trim()
      };

      try {
        await loadRecords(currentFilters);
      } catch (error) {
        emptyState.style.display = "block";
        resultsBar.classList.add("visible");
        resultsCount.textContent = "Nie udało się pobrać danych z bazy";
        emptyState.innerHTML = `<strong>${error.message}</strong>`;
      }
    });

    clearFilters.addEventListener("click", async (event) => {
      event.preventDefault();
      regattaNameInput.value = "";
      regattaPlaceInput.value = "";
      raceDateInput.value = "";
      boatTypeInput.value = "";
      categoryDistanceSelect.value = "";
      raceDistanceInput.value = "";
      raceStageInput.value = "";
      athleteNameInput.value = "";
      athleteSexInput.value = "";
      clubNameInput.value = "";
      clubCityInput.value = "";
      laneInput.value = "";
      placeInput.value = "";
      raceTimeInput.value = "";
      currentFilters = {
        regattaName: "",
        regattaPlace: "",
        raceDate: "",
        boatType: "",
        categoryDistance: "",
        raceDistance: "",
        raceStage: "",
        athleteName: "",
        athleteSex: "",
        clubName: "",
        clubCity: "",
        lane: "",
        place: "",
        raceTime: ""
      };

      try {
        await loadRecords();
      } catch (error) {
        emptyState.style.display = "block";
        resultsBar.classList.add("visible");
        resultsCount.textContent = "Nie udało się pobrać danych z bazy";
        emptyState.innerHTML = `<strong>${error.message}</strong>`;
      }
    });

    exportCsvButton.addEventListener("click", () => exportCsv(getFilteredRecords()));
    exportPdfButton.addEventListener("click", () => exportPdf(getFilteredRecords()));

    loadRecords().catch((error) => {
      emptyState.style.display = "block";
      resultsBar.classList.add("visible");
      resultsCount.textContent = "Nie udało się pobrać danych z bazy";
      emptyState.innerHTML = `<strong>${error.message}</strong>`;
    });
