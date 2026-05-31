  
    const form = document.getElementById('entryForm');
    const statusBox = document.getElementById('statusBox');
    const resetButton = document.getElementById('resetButton');
    const crewRows = document.getElementById('crewRows');
    const addCrewButton = document.getElementById('addCrewButton');
    const boatType = document.getElementById('boatType');



    function getBoatLimit() {
      return BOAT_TYPE_LIMITS[boatType.value] || 1;
    }

    function formatBoatLimitLabel(limit) {
      return `${limit} ${limit === 1 ? 'miejsce' : 'miejsc'} w łodzi`;
    }

    function createAthleteRow(data = {}, crewCard) {
      const row = document.createElement('div');
      row.className = 'athlete-row';
      row.innerHTML = `
        <div class="athlete-row-header">
          <p class="athlete-row-title">Zawodnik</p>
          <button type="button" class="remove-athlete">Usuń</button>
        </div>
        <div class="field-grid">
          <div class="field">
            <label>Imię</label>
            <input name="firstName" placeholder="np. Jan" value="${escapeHtml(data.firstName || '')}" required />
          </div>
          <div class="field">
            <label>Nazwisko</label>
            <input name="lastName" placeholder="np. Kowalski" value="${escapeHtml(data.lastName || '')}" required />
          </div>
          <div class="field">
            <label>Data urodzenia</label>
            <input name="birthDate" type="date" value="${escapeHtml(data.birthDate || '')}" required />
          </div>
          <div class="field">
            <label>Płeć</label>
            <select name="sex" required>
              <option value="">Wybierz</option>
              <option value="M" ${data.sex === 'M' ? 'selected' : ''}>M</option>
              <option value="K" ${data.sex === 'K' ? 'selected' : ''}>K</option>
            </select>
          </div>
        </div>
      `;

      row.querySelector('.remove-athlete').addEventListener('click', () => {
        if (crewCard.querySelectorAll('.athlete-row').length > 1) {
          row.remove();
          updateCrewAthleteState(crewCard);
        }
      });

      return row;
    }

    function syncCrewAthletes(crewCard, athleteDataList = []) {
      const athleteRowsContainer = crewCard.querySelector('.athlete-rows');
      athleteRowsContainer.innerHTML = '';

      const limit = getBoatLimit();
      const athletes = athleteDataList.slice(0, limit);
      const initialRows = athletes.length > 0 ? athletes : [{}];

      initialRows.forEach((athlete) => {
        athleteRowsContainer.appendChild(createAthleteRow(athlete, crewCard));
      });

      updateCrewAthleteState(crewCard);
    }

    function updateCrewAthleteState(crewCard) {
      const athleteRowsContainer = crewCard.querySelector('.athlete-rows');
      const limit = getBoatLimit();
      const rows = Array.from(athleteRowsContainer.querySelectorAll('.athlete-row'));
      const addAthleteButton = crewCard.querySelector('.add-athlete-button');
      const limitLabel = crewCard.querySelector('.crew-limit');
      const capacityChip = crewCard.querySelector('.crew-capacity');
      const warning = crewCard.querySelector('.crew-limit-warning');

      if (rows.length > limit) {
        rows.slice(limit).forEach((row) => row.remove());
      }

      const currentCount = athleteRowsContainer.querySelectorAll('.athlete-row').length;
      limitLabel.textContent = `Limit: ${currentCount}/${limit} zawodników`;
      if (capacityChip) {
        capacityChip.textContent = `${boatType.value} • ${formatBoatLimitLabel(limit)}`;
      }

      if (currentCount < limit) {
        warning.textContent = '';
      }
    }

    function createCrewCard(data = {}) {
      const crewCard = document.createElement('div');
      crewCard.className = 'crew-card';
      crewCard.innerHTML = `
        <div class="crew-card-header">
          <div>
            <p class="crew-card-title">Osada</p>
            <p class="crew-limit">Limit: 0/0 zawodników</p>
          </div>
          <button type="button" class="remove-crew">Usuń osadę</button>
        </div>
        <div class="field-grid">
          <div class="field">
            <label>Nazwa osady</label>
            <input name="crewName" placeholder="np. Osada A" value="${escapeHtml(data.crewName || '')}" required />
          </div>
          <div class="field">
            <label>Klub</label>
            <input name="clubName" placeholder="np. AZS Szczecin" value="${escapeHtml(data.clubName || '')}" required />
          </div>
          <div class="field">
            <label>Miasto klubu</label>
            <input name="clubCity" placeholder="np. Szczecin" value="${escapeHtml(data.clubCity || '')}" required />
          </div>
          <div class="field">
            <label>Tor</label>
            <input name="lane" placeholder="np. Tor 2" value="${escapeHtml(data.lane || '')}" required />
          </div>
          <div class="field">
            <label>Miejsce</label>
            <input name="place" type="number" min="1" step="1" placeholder="np. 1" value="${escapeHtml(data.place || '')}" />
          </div>
          <div class="field">
            <label>Czas</label>
            <input name="time" type="text" placeholder="np. 06:12.45" value="${escapeHtml(data.time || '')}" />
          </div>
        </div>
        <div class="crew-athletes">
          <div class="crew-athletes-head">
            <label>Zawodnicy</label>
            <span class="chip crew-capacity">${boatType.value} • ${formatBoatLimitLabel(getBoatLimit())}</span>
          </div>
          <div class="athlete-rows"></div>
          <div class="actions actions--start">
            <button type="button" class="btn btn-secondary add-athlete-button">Dodaj zawodnika</button>
            <span class="crew-limit-warning" aria-live="polite"></span>
          </div>
          <p class="crew-note">Liczba zawodników jest ograniczona przez wybrany typ łodzi.</p>
        </div>
      `;

      crewCard.querySelector('.remove-crew').addEventListener('click', () => {
        if (crewRows.children.length > 1) {
          crewCard.remove();
        } else {
          crewCard.querySelectorAll('input').forEach((input) => {
            input.value = '';
          });
          syncCrewAthletes(crewCard);
        }
      });

      crewCard.querySelector('.add-athlete-button').addEventListener('click', () => {
        const athleteRowsContainer = crewCard.querySelector('.athlete-rows');
        const warning = crewCard.querySelector('.crew-limit-warning');

        if (athleteRowsContainer.querySelectorAll('.athlete-row').length < getBoatLimit()) {
          athleteRowsContainer.appendChild(createAthleteRow({}, crewCard));
          warning.textContent = '';
          updateCrewAthleteState(crewCard);
        } else {
          warning.textContent = 'Osiągnięto maksymalną liczbę zawodników dla tej łodzi.';
        }
      });

      syncCrewAthletes(crewCard, data.athletes || []);

      return crewCard;
    }

    function collectAthletes(crewCard) {
      return Array.from(crewCard.querySelectorAll('.athlete-row')).map((row) => ({
        firstName: row.querySelector('input[name="firstName"]').value.trim(),
        lastName: row.querySelector('input[name="lastName"]').value.trim(),
        birthDate: row.querySelector('input[name="birthDate"]').value,
        sex: row.querySelector('select[name="sex"]').value
      })).filter((athlete) => athlete.firstName && athlete.lastName);
    }

    function collectCrews() {
      return Array.from(crewRows.querySelectorAll('.crew-card')).map((crewCard) => ({
        crewName: crewCard.querySelector('input[name="crewName"]').value.trim(),
        clubName: crewCard.querySelector('input[name="clubName"]').value.trim(),
        clubCity: crewCard.querySelector('input[name="clubCity"]').value.trim(),
        lane: crewCard.querySelector('input[name="lane"]').value.trim(),
        place: crewCard.querySelector('input[name="place"]').value.trim(),
        time: crewCard.querySelector('input[name="time"]').value.trim(),
        athletes: collectAthletes(crewCard)
      })).filter((crew) => crew.crewName && crew.clubName && crew.clubCity && crew.lane && crew.athletes.length > 0);
    }

    function syncAllCrewCards() {
      Array.from(crewRows.querySelectorAll('.crew-card')).forEach((crewCard) => {
        syncCrewAthletes(crewCard, collectAthletes(crewCard));
      });
    }

    function setStatus(type, title, text) {
      statusBox.className = `status ${type || ''}`.trim();
      statusBox.innerHTML = `
        <h2 class="status-title">${title}</h2>
        <p class="status-text">${text}</p>
      `;
    }

    async function submitEntry(event) {
      event.preventDefault();

      const payload = {
        regattaName: document.getElementById('regattaName').value.trim(),
        regattaPlace: document.getElementById('regattaPlace').value.trim(),
        raceDate: document.getElementById('raceDate').value,
        category: document.getElementById('category').value.trim(),
        distance: document.getElementById('distance').value.trim(),
        stage: document.getElementById('stage').value.trim(),
        boatType: boatType.value,
        crews: collectCrews()
      };

      if (payload.crews.length === 0) {
        setStatus('error', 'Brak danych', 'Dodaj przynajmniej jedną osadę z kompletnym składem zawodników.');
        return;
      }

      try {
        setStatus('success', 'Zapisywanie...', 'Dane są właśnie wysyłane do bazy.');

        const response = await fetch('/api/records', {
          method: 'POST',
          headers: {
            'Content-Type': 'application/json'
          },
          body: JSON.stringify(payload)
        });

        const result = await response.json();

        if (!response.ok) {
          throw new Error(result.error || result.message || 'Nie udało się zapisać danych.');
        }

        const preservedRegattaName = payload.regattaName;
        const preservedRegattaPlace = payload.regattaPlace;
        const preservedRaceDate = payload.raceDate;

        form.reset();
        document.getElementById('regattaName').value = preservedRegattaName;
        document.getElementById('regattaPlace').value = preservedRegattaPlace;
        document.getElementById('raceDate').value = preservedRaceDate;
        crewRows.innerHTML = '';
        crewRows.appendChild(createCrewCard());

        setStatus(
          'success',
          'Dane zapisane',
          `Dodano wynik dla ${result.summary.regattaName}. Zapisano ${result.summary.crews.length} osad${result.summary.crews.length === 1 ? 'ę' : 'y'}.`
        );
      } catch (error) {
        setStatus('error', 'Błąd zapisu', error.message);
      }
    }

    resetButton.addEventListener('click', () => {
      form.reset();
      crewRows.innerHTML = '';
      crewRows.appendChild(createCrewCard());
      setStatus('success', 'Formularz wyczyszczony', 'Możesz wprowadzić nowy wynik od początku.');
    });

    addCrewButton.addEventListener('click', () => {
      crewRows.appendChild(createCrewCard());
    });

    boatType.addEventListener('change', syncAllCrewCards);
    form.addEventListener('submit', submitEntry);

    crewRows.appendChild(createCrewCard());
