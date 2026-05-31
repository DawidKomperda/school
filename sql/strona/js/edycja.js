  

    const searchForm = document.getElementById('searchForm');
    const clearFiltersButton = document.getElementById('clearFiltersButton');
    const regattaHints = document.getElementById('regattaHints');
    const categoryDistanceSelect = document.getElementById('categoryDistance');
    const resultsBody = document.getElementById('resultsBody');
    const resultsBar = document.getElementById('resultsBar');
    const resultsCount = document.getElementById('resultsCount');
    const editForm = document.getElementById('editForm');
    const selectedStartIdInput = document.getElementById('selectedStartId');
    const selectionStatus = document.getElementById('selectionStatus');
    const crewRows = document.getElementById('crewRows');
    const clearSelectionButton = document.getElementById('clearSelectionButton');

    const searchInputs = {
      regattaName: document.getElementById('regattaName'),
      regattaPlace: document.getElementById('regattaPlace'),
      raceDate: document.getElementById('raceDate'),
      boatType: document.getElementById('boatType'),
      categoryDistance: document.getElementById('categoryDistance'),
      raceDistance: document.getElementById('raceDistance'),
      raceStage: document.getElementById('raceStage'),
      athleteName: document.getElementById('athleteName'),
      athleteSex: document.getElementById('athleteSex'),
      clubName: document.getElementById('clubName'),
      clubCity: document.getElementById('clubCity'),
      lane: document.getElementById('lane'),
      place: document.getElementById('place'),
      raceTime: document.getElementById('raceTime')
    };

    const editInputs = {
      regattaName: document.getElementById('editRegattaName'),
      regattaPlace: document.getElementById('editRegattaPlace'),
      raceDate: document.getElementById('editRaceDate'),
      category: document.getElementById('editCategory'),
      distance: document.getElementById('editDistance'),
      stage: document.getElementById('editStage')
    };

    let currentRecords = [];
    let selectedStartId = null;
    let selectedRow = null;
    let athleteRowCounter = 0;


    function normalizeText(value) {
      return String(value ?? '').trim();
    }

    function matchesText(value, query) {
      return normalizeText(value).toLowerCase().includes(normalizeText(query).toLowerCase());
    }

    function splitMultiValue(value) {
      return normalizeText(value)
        .split(/[;,\n]/)
        .map((part) => part.trim())
        .filter(Boolean);
    }

    function formatDateIso(value) {
      if (!value) {
        return '';
      }

      const date = new Date(value);

      if (Number.isNaN(date.getTime())) {
        return normalizeText(value);
      }

      const year = date.getUTCFullYear();
      const month = String(date.getUTCMonth() + 1).padStart(2, '0');
      const day = String(date.getUTCDate()).padStart(2, '0');
      return `${year}-${month}-${day}`;
    }

    function formatTime(value) {
      return normalizeText(value);
    }

    function formatBoatLimitLabel(limit) {
      return limit === 1 ? '1 miejsce w łodzi' : `${limit} miejsc w łodzi`;
    }

    function getBoatLimit(card = document) {
      const boatType = card.querySelector('select[name="boatType"]');
      return BOAT_TYPE_LIMITS[boatType?.value] || 1;
    }

    function getSearchFilters() {
      return {
        regattaName: normalizeText(searchInputs.regattaName.value),
        regattaPlace: normalizeText(searchInputs.regattaPlace.value),
        raceDate: normalizeText(searchInputs.raceDate.value),
        boatType: normalizeText(searchInputs.boatType.value),
        categoryDistance: normalizeText(searchInputs.categoryDistance.value),
        raceDistance: normalizeText(searchInputs.raceDistance.value),
        raceStage: normalizeText(searchInputs.raceStage.value),
        athleteName: normalizeText(searchInputs.athleteName.value),
        athleteSex: normalizeText(searchInputs.athleteSex.value),
        clubName: normalizeText(searchInputs.clubName.value),
        clubCity: normalizeText(searchInputs.clubCity.value),
        lane: normalizeText(searchInputs.lane.value),
        place: normalizeText(searchInputs.place.value),
        raceTime: normalizeText(searchInputs.raceTime.value)
      };
    }

    function buildQuery(filters) {
      const params = new URLSearchParams();

      Object.entries(filters).forEach(([key, value]) => {
        if (value) {
          params.set(key, value);
        }
      });

      return params.toString();
    }

    function getFilteredRecords() {
      const filters = getSearchFilters();
      const athleteQueries = splitMultiValue(filters.athleteName);

      return currentRecords.filter((record) => {
        const regattaNameMatch = !filters.regattaName || matchesText(record.regatta, filters.regattaName);
        const regattaPlaceMatch = !filters.regattaPlace || matchesText(record.regattaPlace, filters.regattaPlace);
        const dateMatch = !filters.raceDate || formatDateIso(record.dateIso) === filters.raceDate;
        const boatTypeMatch = !filters.boatType || matchesText(record.boatType, filters.boatType);
        const categoryMatch = !filters.categoryDistance || `${record.category} / ${record.distance}` === filters.categoryDistance;
        const distanceMatch = !filters.raceDistance || matchesText(record.distance, filters.raceDistance);
        const stageMatch = !filters.raceStage || matchesText(record.stage, filters.raceStage);
        const athleteMatch = athleteQueries.length === 0 || athleteQueries.some((query) => record.athletes.some((athlete) => matchesText(athlete, query)));
        const athleteSexMatch = !filters.athleteSex || record.athleteSexes.some((sex) => matchesText(sex, filters.athleteSex));
        const clubMatch = !filters.clubName || matchesText(record.club, filters.clubName) || matchesText(record.crew, filters.clubName);
        const clubCityMatch = !filters.clubCity || matchesText(record.clubCity, filters.clubCity);
        const laneMatch = !filters.lane || matchesText(record.lane, filters.lane);
        const placeMatch = !filters.place || matchesText(String(record.place || ''), filters.place);
        const timeMatch = !filters.raceTime || matchesText(record.time, filters.raceTime);

        return regattaNameMatch && regattaPlaceMatch && dateMatch && boatTypeMatch && categoryMatch && distanceMatch && stageMatch && athleteMatch && athleteSexMatch && clubMatch && clubCityMatch && laneMatch && placeMatch && timeMatch;
      });
    }

    function renderHints(records) {
      const regattaOptions = new Set();
      const categoryOptions = new Set();

      records.forEach((record) => {
        if (record.regatta) {
          regattaOptions.add(record.regatta);
        }

        if (record.category && record.distance) {
          categoryOptions.add(`${record.category} / ${record.distance}`);
        }
      });

      regattaHints.innerHTML = '';
      Array.from(regattaOptions).sort().forEach((value) => {
        const option = document.createElement('option');
        option.value = value;
        regattaHints.appendChild(option);
      });

      const currentSelection = categoryDistanceSelect.value;
      categoryDistanceSelect.innerHTML = '<option value="">Wszystkie</option>';

      Array.from(categoryOptions).sort().forEach((value) => {
        const option = document.createElement('option');
        option.value = value;
        option.textContent = value;
        categoryDistanceSelect.appendChild(option);
      });

      if (Array.from(categoryOptions).includes(currentSelection)) {
        categoryDistanceSelect.value = currentSelection;
      }
    }

    function setSelectionMessage(title, text, variant = '') {
      selectionStatus.className = variant ? `status ${variant}` : 'status';
      selectionStatus.innerHTML = `
        <p class="status-title">${escapeHtml(title)}</p>
        <p class="status-text">${escapeHtml(text)}</p>
      `;
    }

    function renderTable(records) {
      resultsBody.innerHTML = '';
      resultsBar.classList.add('visible');
      resultsCount.textContent = `Znaleziono ${records.length} wyników`;

      if (records.length === 0) {
        const row = document.createElement('tr');
        row.innerHTML = '<td class="empty" colspan="10">Brak wyników dla wybranych filtrów.</td>';
        resultsBody.appendChild(row);
        return;
      }

      records.forEach((record) => {
        const row = document.createElement('tr');
        row.className = 'editable-row';
        row.dataset.startId = String(record.startId);

        if (selectedStartId && String(record.startId) === String(selectedStartId)) {
          row.classList.add('selected');
          selectedRow = row;
        }

        row.innerHTML = `
          <td>
            <strong>${escapeHtml(record.date || '')}</strong><br />
            <span class="muted">${escapeHtml(record.regatta || '-')}</span>
            <div class="pill">${escapeHtml(record.regattaPlace || '-')}</div>
          </td>
          <td>${escapeHtml(record.boatType || '-')}</td>
          <td>${escapeHtml(record.category || '-')}<br /><span class="muted">${escapeHtml(record.distance || '-')}</span></td>
          <td>${escapeHtml(record.stage || '-')}</td>
          <td>${escapeHtml(record.lane || '-')}</td>
          <td>${escapeHtml(record.place || '-')}</td>
          <td><strong>${escapeHtml(record.crew || '-')}</strong><br /><span class="muted">(${escapeHtml(record.club || '-')})</span></td>
          <td>${escapeHtml(record.clubCity || '-')}</td>
          <td>${escapeHtml((record.athletes || []).join(', '))}</td>
          <td><strong>${escapeHtml(record.time || '-')}</strong></td>
        `;

        row.addEventListener('click', () => {
          loadRecordForEdit(record.startId, row);
        });

        resultsBody.appendChild(row);
      });
    }

    async function loadRecords() {
      const query = buildQuery(getSearchFilters());
      const url = query ? `/api/records?${query}` : '/api/records';

      resultsCount.textContent = 'Wczytywanie rekordów...';

      try {
        const response = await fetch(url);
        const data = await response.json();

        if (!response.ok) {
          throw new Error(data.message || 'Nie udało się pobrać rekordów.');
        }

        currentRecords = data.results || data.records || [];
        renderHints(currentRecords);
        renderTable(currentRecords);
      } catch (error) {
        resultsBar.classList.add('visible');
        resultsCount.textContent = 'Wystąpił błąd podczas pobierania danych';
        resultsBody.innerHTML = `<tr><td class="empty" colspan="10">${escapeHtml(error.message)}</td></tr>`;
      }
    }

    function createAthleteRow(data = {}) {
      athleteRowCounter += 1;
      const rowId = athleteRowCounter;
      const row = document.createElement('div');
      row.className = 'athlete-row';
      row.innerHTML = `
        <div class="athlete-row-header">
          <p class="athlete-row-title">Zawodnik ${rowId}</p>
          <button type="button" class="remove-athlete">Usuń zawodnika</button>
        </div>
        <div class="field-grid">
          <div class="field">
            <label for="athlete-${rowId}-firstName">Imię</label>
            <input id="athlete-${rowId}-firstName" name="firstName" placeholder="np. Jan" value="${escapeHtml(data.firstName || '')}" required />
          </div>
          <div class="field">
            <label for="athlete-${rowId}-lastName">Nazwisko</label>
            <input id="athlete-${rowId}-lastName" name="lastName" placeholder="np. Kowalski" value="${escapeHtml(data.lastName || '')}" required />
          </div>
          <div class="field">
            <label for="athlete-${rowId}-birthDate">Data urodzenia</label>
            <input id="athlete-${rowId}-birthDate" name="birthDate" type="date" value="${escapeHtml(data.birthDate || '')}" required />
          </div>
          <div class="field">
            <label for="athlete-${rowId}-sex">Płeć</label>
            <select id="athlete-${rowId}-sex" name="sex" required>
              <option value="">Wybierz</option>
              <option value="M" ${data.sex === 'M' ? 'selected' : ''}>M</option>
              <option value="K" ${data.sex === 'K' ? 'selected' : ''}>K</option>
            </select>
          </div>
        </div>
      `;

      row.querySelector('.remove-athlete').addEventListener('click', () => {
        const card = row.closest('.crew-card');
        row.remove();

        if (card && card.querySelectorAll('.athlete-row').length === 0) {
          card.querySelector('.athlete-rows').appendChild(createAthleteRow());
        }

        updateCrewAthleteState(card);
      });

      return row;
    }

    function updateCrewAthleteState(card, showWarning = false) {
      if (!card) {
        return;
      }

      const boatType = card.querySelector('select[name="boatType"]');
      const capacityChip = card.querySelector('.crew-capacity');
      const warning = card.querySelector('.crew-limit-warning');
      const addButton = card.querySelector('.add-athlete-button');
      const limit = getBoatLimit(card);
      const athletes = card.querySelectorAll('.athlete-row');

      if (capacityChip && boatType) {
        capacityChip.textContent = `${boatType.value} • ${formatBoatLimitLabel(limit)}`;
      }

      if (warning) {
        warning.textContent = showWarning && athletes.length >= limit
          ? `Dla łodzi ${boatType.value || 'wybranej'} można dodać maksymalnie ${limit} zawodników.`
          : '';
      }

      if (addButton) {
        addButton.disabled = false;
      }
    }

    function syncCrewAthletes(card, athletes = []) {
      const athleteRows = card.querySelector('.athlete-rows');
      const limit = getBoatLimit(card);

      while (athleteRows.children.length > limit) {
        athleteRows.lastElementChild.remove();
      }

      while (athleteRows.children.length < Math.max(1, Math.min(limit, athletes.length || 1))) {
        const athlete = athletes[athleteRows.children.length] || {};
        athleteRows.appendChild(createAthleteRow(athlete));
      }

      if (athletes.length > limit) {
        athletes.slice(limit).forEach(() => {});
      }

      updateCrewAthleteState(card, false);
    }

    function createCrewCard(data = {}) {
      const card = document.createElement('div');
      card.className = 'crew-card';
      card.innerHTML = `
        <div class="crew-card-header">
          <p class="crew-card-title">Osada</p>
          <span class="chip crew-capacity">4x • 4 miejsc w łodzi</span>
        </div>
        <div class="field-grid">
          <div class="field field--wide">
            <label for="editBoatType">Typ łodzi</label>
            <select id="editBoatType" name="boatType" required>
              <option value="1x">1x</option>
              <option value="2x">2x</option>
              <option value="2-">2-</option>
              <option value="4x">4x</option>
              <option value="4-">4-</option>
              <option value="4+">4+</option>
              <option value="8+">8+</option>
            </select>
          </div>
          <div class="field">
            <label for="editCrewName">Nazwa osady</label>
            <input id="editCrewName" name="crewName" placeholder="np. Osada A" value="${escapeHtml(data.crewName || '')}" required />
          </div>
          <div class="field">
            <label for="editClubName">Nazwa klubu</label>
            <input id="editClubName" name="clubName" placeholder="np. AZS Szczecin" value="${escapeHtml(data.clubName || '')}" required />
          </div>
          <div class="field">
            <label for="editClubCity">Miasto klubu</label>
            <input id="editClubCity" name="clubCity" placeholder="np. Szczecin" value="${escapeHtml(data.clubCity || '')}" required />
          </div>
          <div class="field">
            <label for="editLane">Tor</label>
            <input id="editLane" name="lane" placeholder="np. Tor 2" value="${escapeHtml(data.lane || '')}" required />
          </div>
          <div class="field">
            <label for="editPlace">Miejsce</label>
            <input id="editPlace" name="place" type="number" min="1" step="1" placeholder="np. 1" value="${escapeHtml(data.place || '')}" />
          </div>
          <div class="field field--compact">
            <label for="editRaceTime">Czas</label>
            <input id="editRaceTime" name="time" type="text" placeholder="np. 06:12.45" value="${escapeHtml(data.time || '')}" />
          </div>
        </div>
        <div class="crew-athletes">
          <div class="crew-athletes-head">
            <p class="crew-limit">Skład zawodników</p>
            <div class="crew-limit-warning"></div>
          </div>
          <div class="athlete-rows"></div>
          <div class="actions actions--start">
            <button type="button" class="btn btn-secondary add-athlete-button">Dodaj zawodnika</button>
          </div>
        </div>
      `;

      const boatType = card.querySelector('select[name="boatType"]');
      const addButton = card.querySelector('.add-athlete-button');

      boatType.value = data.boatType || '4x';
      syncCrewAthletes(card, data.athletes || []);

      boatType.addEventListener('change', () => {
        syncCrewAthletes(card, collectAthletes(card));
      });

      addButton.addEventListener('click', () => {
        const limit = getBoatLimit(card);
        const athleteRows = card.querySelector('.athlete-rows');

        if (athleteRows.children.length >= limit) {
          updateCrewAthleteState(card, true);
          return;
        }

        athleteRows.appendChild(createAthleteRow());
        updateCrewAthleteState(card, false);
      });

      return card;
    }

    function collectAthletes(card) {
      return Array.from(card.querySelectorAll('.athlete-row')).map((row) => ({
        firstName: row.querySelector('input[name="firstName"]').value.trim(),
        lastName: row.querySelector('input[name="lastName"]').value.trim(),
        birthDate: row.querySelector('input[name="birthDate"]').value,
        sex: row.querySelector('select[name="sex"]').value
      })).filter((athlete) => athlete.firstName && athlete.lastName && athlete.birthDate && athlete.sex);
    }

    function buildEditPayload() {
      const crewCard = crewRows.querySelector('.crew-card');

      if (!crewCard) {
        return null;
      }

      return {
        regattaName: editInputs.regattaName.value.trim(),
        regattaPlace: editInputs.regattaPlace.value.trim(),
        raceDate: editInputs.raceDate.value,
        category: editInputs.category.value.trim(),
        distance: editInputs.distance.value.trim(),
        stage: editInputs.stage.value.trim(),
        boatType: crewCard.querySelector('select[name="boatType"]').value,
        crewName: crewCard.querySelector('input[name="crewName"]').value.trim(),
        clubName: crewCard.querySelector('input[name="clubName"]').value.trim(),
        clubCity: crewCard.querySelector('input[name="clubCity"]').value.trim(),
        lane: crewCard.querySelector('input[name="lane"]').value.trim(),
        place: crewCard.querySelector('input[name="place"]').value.trim(),
        time: crewCard.querySelector('input[name="time"]').value.trim(),
        athletes: collectAthletes(crewCard)
      };
    }

    function populateEditForm(record) {
      selectedStartId = record.startId;
      selectedStartIdInput.value = record.startId;
      selectedRow?.classList.remove('selected');

      editInputs.regattaName.value = record.regattaName || '';
      editInputs.regattaPlace.value = record.regattaPlace || '';
      editInputs.raceDate.value = record.dateIso || '';
      editInputs.category.value = record.category || '';
      editInputs.distance.value = record.distance || '';
      editInputs.stage.value = record.stage || '';

      crewRows.innerHTML = '';
      crewRows.appendChild(createCrewCard({
        crewName: record.crewName || '',
        clubName: record.clubName || '',
        clubCity: record.clubCity || '',
        lane: record.lane || '',
        place: record.place || '',
        time: record.time || '',
        boatType: record.boatType || '4x',
        athletes: record.athletes || []
      }));

      updateSelectedRow(record.startId);
      setSelectionMessage(
        'Rekord wczytany',
        `Wybrano start ${record.startId}. Możesz teraz zmienić pola i zapisać aktualizację.`,
        ''
      );
    }

    function updateSelectedRow(startId) {
      resultsBody.querySelectorAll('tr').forEach((row) => {
        row.classList.toggle('selected', row.dataset.startId === String(startId));

        if (row.dataset.startId === String(startId)) {
          selectedRow = row;
        }
      });
    }

    async function loadRecordForEdit(startId, rowElement = null) {
      selectedRow = rowElement || selectedRow;

      try {
        const response = await fetch(`/api/records/${startId}`);
        const data = await response.json();

        if (!response.ok) {
          throw new Error(data.message || 'Nie udało się pobrać rekordu do edycji.');
        }

        populateEditForm(data.record);
      } catch (error) {
        setSelectionMessage('Nie udało się wczytać rekordu', error.message, 'error');
      }
    }

    function resetSelection() {
      selectedStartId = null;
      selectedStartIdInput.value = '';
      selectedRow?.classList.remove('selected');
      selectedRow = null;
      editForm.reset();
      crewRows.innerHTML = '';
      crewRows.appendChild(createCrewCard());
      setSelectionMessage('Brak zaznaczonego rekordu', 'Kliknij wiersz w tabeli, aby wczytać dane do formularza poniżej.', '');
    }

    async function submitEdit(event) {
      event.preventDefault();

      if (!selectedStartId) {
        setSelectionMessage('Brak rekordu do zapisu', 'Najpierw kliknij wiersz w tabeli, aby wybrać rekord.', 'error');
        return;
      }

      const payload = buildEditPayload();

      if (!payload || payload.athletes.length === 0) {
        setSelectionMessage('Brak danych do zapisu', 'Uzupełnij wymagane pola formularza i przynajmniej jednego zawodnika.', 'error');
        return;
      }

      try {
        const response = await fetch(`/api/records/${selectedStartId}`, {
          method: 'PUT',
          headers: {
            'Content-Type': 'application/json'
          },
          body: JSON.stringify(payload)
        });

        const data = await response.json();

        if (!response.ok) {
          throw new Error(data.message || 'Nie udało się zaktualizować rekordu.');
        }

        if (data.record) {
          populateEditForm(data.record);
        }

        await loadRecords();
        setSelectionMessage('Zmiany zapisane', 'Rekord został zaktualizowany w bazie danych.', 'success');
      } catch (error) {
        setSelectionMessage('Błąd zapisu', error.message, 'error');
      }
    }

    function clearSearchFilters() {
      Object.values(searchInputs).forEach((input) => {
        input.value = '';
      });
      loadRecords();
    }

    searchForm.addEventListener('submit', (event) => {
      event.preventDefault();
      loadRecords();
    });

    clearFiltersButton.addEventListener('click', clearSearchFilters);
    clearSelectionButton.addEventListener('click', resetSelection);
    editForm.addEventListener('submit', submitEdit);

    crewRows.appendChild(createCrewCard());
    setSelectionMessage('Brak zaznaczonego rekordu', 'Kliknij wiersz w tabeli, aby wczytać dane do formularza poniżej.', '');
    loadRecords();
