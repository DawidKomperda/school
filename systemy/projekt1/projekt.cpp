// Biblioteki standardowe i systemowe:
// iostream - podstawowe operacje wejscia/wyjscia 
// pthread.h - obsluga watkow i semaforow (mutexow) w standardzie POSIX
// ncurses.h - biblioteka do tworzenia interfejsow tekstowych (TUI) w terminalu
// unistd.h, stdlib.h, time.h - funkcje systemowe, takie jak losowanie i usypianie (usleep)
#include <iostream>
#include <pthread.h>
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

// Definiujemy stala liczbe czytelnikow (5) oraz pisarzy (2)
#define NUM_READERS 5
#define NUM_WRITERS 2

// ZMIENNE WSPOLDZIELONE
// To "wspolny zasob" o ktory walcza watki. Pisarze go modyfikuja, czytelnicy sprawdzaja.
int resource_value = 0;
// Licznik aktywnych czytelnikow aktualnie bedacych w strefie krytycznej
int read_count = 0;

// MUTEXY - obiekty uzywane do synchronizacji i ochrony sekcji krytycznych przed jednoczesnym dostepem
pthread_mutex_t r_mutex = PTHREAD_MUTEX_INITIALIZER;  // Mutex chroniacy zmienna read_count przed rownoczesna modyfikacja przez dwoch czytelnikow
pthread_mutex_t w_mutex = PTHREAD_MUTEX_INITIALIZER;  // Mutex glowny, chroniacy wylacznosc dla zrodel zapisu (pisarz potrzebuje wylacznosci, czytelnicy rezerwuja go przed pisarzami)
pthread_mutex_t ui_mutex = PTHREAD_MUTEX_INITIALIZER; // Mutex chroniacy ekran terminala, upewnia sie ze dwa watki nie wypisza czegos jednoczesnie i nie zepsuja obrazu

// Mozliwe stany naszego watku
enum State { SLEEPING, WAITING, READING, WRITING };

// Struktura przechowujaca informacje o danym watku (ID i co aktualnie robi)
struct ThreadInfo {
    int id;
    State state;
};

// Tablice trzymajace informacje o kazdym uzytkowniku
ThreadInfo readers_info[NUM_READERS];
ThreadInfo writers_info[NUM_WRITERS];
// Flaga uzywana do uruchamiania / zakonczenia programu petla
bool running = true;

// Funkcja pomocnicza zamieniajaca stan (enum) na tekst wyswietlany na ekranie terminala
const char* stateToString(State s) {
    switch (s) {
        case SLEEPING: return "Spi     "; // Watek spi i wykonuje inne zadania
        case WAITING:  return "Czeka   "; // Watek ubiega sie o zasob
        case READING:  return "Czyta   "; // Czytelnik w sekcji krytycznej
        case WRITING:  return "Pisze   "; // Pisarz w sekcji krytycznej
        default:       return "Nieznany";
    }
}

// Funkcja odpowiedzialna za rysowanie calego ekranu interfejsu (ncurses)
void drawUI() {
    // Blokujemy dostep do ekranu, wiec jakikolwiek inny watek musi tu zaczekac az skonczymy odswiezac
    pthread_mutex_lock(&ui_mutex);
    clear(); // Wyczyszczenie terminala w bibliotece ncurses

    // Wyswietla tytul programu
    mvprintw(0, 20, "PROBLEM CZYTELNIKOW I PISARZY - WIZUALIZACJA");
    
    // Wypisuje aktualny stan generalnego zasobu
    mvprintw(2, 2, "Stan Zasobu: ");
    if (read_count > 0) {
        // Jezeli jest przynajmniej 1 czytelnik to go wypisz
        printw("Czytany przez %d", read_count);
    } else {
        // Jeżeli nie ma czytelnika to sprawdzamy czy pisarz wlasnie pisze
        bool writing = false;
        for (int i = 0; i < NUM_WRITERS; ++i) {
            if (writers_info[i].state == WRITING) {
                writing = true;
                break;
            }
        }
        if (writing) {
            printw("Modyfikowany przez pisarza");
        } else {
            printw("Wolny");
        }
    }
    // Wypisz na ekranie aktualna wartosc liczbowa zasobu (modyfikowana tylko przez Pisarzy)
    mvprintw(3, 2, "Aktualna wartosc danych: %d", resource_value);
    
    // Sekcja wyswietlajaca stany kazdego elementu wsrod CZYTELNIKOW
    mvprintw(5, 2, "--- CZYTELNICY ---");
    for (int i = 0; i < NUM_READERS; ++i) {
        mvprintw(6 + i, 2, "[Czytelnik %d] : %s", readers_info[i].id, stateToString(readers_info[i].state));
    }

    // Sekcja wyswietlajaca stany kazdego elementu wsrod PISARZY
    mvprintw(5, 40, "--- PISARZE ---");
    for (int i = 0; i < NUM_WRITERS; ++i) {
        mvprintw(6 + i, 40, "[Pisarz %d]    : %s", writers_info[i].id, stateToString(writers_info[i].state));
    }
    
    // Instrukcja wylaczania na samym dole okna
    mvprintw(LINES - 2, 2, "[Nacisnij 'q' aby zakonczyc]");
    
    // Renderuje wszystkie powyzsze zaplanowane napisy the-ncurses na faktyczny ekran terminala
    refresh();

    // Gotowe. Odblokowanie ekranu.
    pthread_mutex_unlock(&ui_mutex);
}

// Funkcja (worker), z ktora urchamiany jest Kazdy watek typu "CZYTELNIK"
void* readerWorker(void* arg) {
    int idx = *((int*)arg); // Pobiera id (0-4) watku, rzutujac je ze wskaznika na int
    
    while (running) {
        // Krok 1: Watek wykonuje swoja wlasna, osobista prace nie zwiazana z zasobem
        readers_info[idx].state = SLEEPING;
        drawUI(); // Aktualizuje widok z nowym stanem
        usleep((rand() % 3000 + 1000) * 1000); // spi losowy by od 1 do 4 sekund

        // Krok 2: Czytelnik chce uzyskac dostep do czytania (wchodzi w stan ubiegania sie "Czekania")
        readers_info[idx].state = WAITING;
        drawUI();

        // Krok 3: Ochrona zmiany liczby "read_count"
        pthread_mutex_lock(&r_mutex);
        read_count++;

        // Bardzo wazne: Jezeli to my jestesmy PIERWSZYM czytelnikiem – to my rezerwujemy dostep (w_mutex). 
        // W ten sposob zaden pisarz tam nie wejdzie dopoki strefie bedzie minimum jeden Czytelnik.
        if (read_count == 1) {
            pthread_mutex_lock(&w_mutex); 
        }
        pthread_mutex_unlock(&r_mutex); // Po wszystkim odblokowujemy modyfikacje samego licznika innym

        // Krok 4: Watek pomyslnie przedostal sie przez blokady! Wlasnie "Czyta" zmienne.
        readers_info[idx].state = READING;
        drawUI();
        usleep((rand() % 2000 + 1000) * 1000); // Czytanie potrwa 1-3 sekundy

        // Krok 5: Czas wyjsc. Blokujemy zmianie stanu licznika, aby bezpiecznie go obnizyc.
        pthread_mutex_lock(&r_mutex);
        read_count--;

        // Jezeli to my bylismy (OSTATNIM) zyjacym w tej chwii czytelnikiem tam w srodku, to 
        // to my otwieramy bramę na caly swiat dla reszty oczekujacych w kolejce - czyli zdejmjemy w_mutex pisarzom.
        if (read_count == 0) {
            pthread_mutex_unlock(&w_mutex); 
        }
        pthread_mutex_unlock(&r_mutex); // Odblokowanie modyfikacji licznika
    }
    return NULL;
}

// Funkcja z ktora uruchamiany jest każdy watek typu "PISARZ"
void* writerWorker(void* arg) {
    int idx = *((int*)arg);
    
    while (running) {
        // Krok 1: Watek wykonuje swoja zewnetrzna modyfikacje we wlasnym czasie.
        writers_info[idx].state = SLEEPING;
        drawUI();
        usleep((rand() % 4000 + 2000) * 1000); // spi miedy 2-6 sec

        // Krok 2: Ustawiamy stan na "Czeka". Watek zaraz pownie zapuka do bram zamku zasobu.
        writers_info[idx].state = WAITING;
        drawUI();

        // Krok 3: Zadanie dostepu absolutnego / Ochrona zasobu na sekcje krytyczna
        // Ten sam zamek uzywaja zarowno inni pisarze jak i grupowo bronia go po swojej stronie czytelnicy
        pthread_mutex_lock(&w_mutex);

        // Krok 4: Wejscie do obszaru krytycznego. Tylko i jednen pisarz to PISZE na calej tablicy.
        writers_info[idx].state = WRITING;
        resource_value += 10; // Zmiana wartosci symulujaca zapis
        drawUI();
        usleep((rand() % 2000 + 1000) * 1000); // Modyfikacja bedzia trwala 1 do 3 sek.

        // Krok 5: Skonczyl modyfikacje, wiec zdejmuje zamek oddajac mozliwosc dostepu innym czekajacym
        pthread_mutex_unlock(&w_mutex);
    }
    return NULL;
}

int main() {
    // Inicjalizacja ziarna losowosci, aby kazde wejscia byly zawsze losowe
    srand(time(NULL));

    // -------------- INICJALIZACJA INTERFEJSU TEXTOWEGO (NCURSES) ---------------
    initscr();    // Inicjalizacja trybu tworzenia narzedzia okienkowego the Curses
    cbreak();     // Wylaczenie buforowania. Aplikacja nie bedzie musiala czekac az zapukasz enter, po kazdym klawiszu z klawy od razu przesle on dane
    noecho();     // Wylaczenie "echa" znakow z klawiatury na ekran
    curs_set(0);  // Ukrycie standardowego natywnego migajacego kursora klawiatury dla podniescienia jakosci GUI terminala
    nodelay(stdscr, TRUE); // Funkjca getch nie spausuje programu zatrzymujac nam pule watkow i interface, jezeli uzytkownik nic nie nacisal to ona po prostu przewija ja dalej 

    // -------------- PRZYGOTOWANIE STRUKTUR DANYCH ---------------
    for (int i = 0; i < NUM_READERS; ++i) {
        readers_info[i].id = i + 1;
        readers_info[i].state = SLEEPING;
    }
    for (int i = 0; i < NUM_WRITERS; ++i) {
        writers_info[i].id = i + 1;
        writers_info[i].state = SLEEPING;
    }

    // Deklarujemy obiekty identyfikatorow powstalych processow dla Posix
    pthread_t readers[NUM_READERS];
    pthread_t writers[NUM_WRITERS];
    int r_idx[NUM_READERS];
    int w_idx[NUM_WRITERS];

    // Uruchomienie fizycznie w petli wszystkich procesow powolnych z ramienia CZYTELNIKOW  
    for (int i = 0; i < NUM_READERS; ++i) {
        r_idx[i] = i; // Wazne jest przekazanie lokalnie pamieci ID wlasnego int'a, tak aby watek nie mial wspolnego "i" zapodanego jako referencja w c-pointerze (inaczej by sie wszystkie nadpisaly zanim 1 by poszla)
        pthread_create(&readers[i], NULL, readerWorker, &r_idx[i]);
    }

    // Uruchomienie wszystkich procesow powolnych powolnych PISARZY funkcja 'writerWorker'
    for (int i = 0; i < NUM_WRITERS; ++i) {
        w_idx[i] = i;
        pthread_create(&writers[i], NULL, writerWorker, &w_idx[i]);
    }

    // Pierwsze ręczne narysowanie ramki okienka na wejsciu
    drawUI();

    // Glowna petla aplikacji przechwytująca klawisze
    int ch;
    while (running) {
        ch = getch(); // Pobiera znak z wejscia 
        if (ch == 'q' || ch == 'Q') {
            running = false; // "running" staje sie false i nakaze wylaczyc wszystie watki
        }
        usleep(100000); // Nie blokujacy delay by nie zajezdzac procesu bez sensu czekajaca petla ciaglego pobierania
    }

    // Oczekiwanie na zakonczenie procesow The Ncurses
    endwin();

    return 0; // Pomyslny koniec
}
