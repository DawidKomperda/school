#include <iostream>
#include <pthread.h>
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define NUM_READERS 5
#define NUM_WRITERS 2

// Shared variables
int resource_value = 0;
int read_count = 0;

// Synchronization
pthread_mutex_t r_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t w_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t ui_mutex = PTHREAD_MUTEX_INITIALIZER; 

enum State { SLEEPING, WAITING, READING, WRITING };

struct ThreadInfo {
    int id;
    State state;
};

ThreadInfo readers_info[NUM_READERS];
ThreadInfo writers_info[NUM_WRITERS];
bool running = true;

const char* stateToString(State s) {
    switch (s) {
        case SLEEPING: return "Spi     ";
        case WAITING:  return "Czeka   ";
        case READING:  return "Czyta   ";
        case WRITING:  return "Pisze   ";
        default:       return "Nieznany";
    }
}

void drawUI() {
    pthread_mutex_lock(&ui_mutex);
    clear();

    mvprintw(0, 20, "PROBLEM CZYTELNIKOW I PISARZY - WIZUALIZACJA");
    
    // Status zasobu
    mvprintw(2, 2, "Stan Zasobu: ");
    if (read_count > 0) {
        printw("Czytany przez %d", read_count);
    } else {
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
    mvprintw(3, 2, "Aktualna wartosc danych: %d", resource_value);
    
    // Readers list
    mvprintw(5, 2, "--- CZYTELNICY ---");
    for (int i = 0; i < NUM_READERS; ++i) {
        mvprintw(6 + i, 2, "[Czytelnik %d] : %s", readers_info[i].id, stateToString(readers_info[i].state));
    }

    // Writers list
    mvprintw(5, 40, "--- PISARZE ---");
    for (int i = 0; i < NUM_WRITERS; ++i) {
        mvprintw(6 + i, 40, "[Pisarz %d]    : %s", writers_info[i].id, stateToString(writers_info[i].state));
    }
    
    mvprintw(LINES - 2, 2, "[Nacisnij 'q' aby zakonczyc]");
    
    refresh();
    pthread_mutex_unlock(&ui_mutex);
}

void* readerWorker(void* arg) {
    int idx = *((int*)arg);
    
    while (running) {
        // Obliczanie
        readers_info[idx].state = SLEEPING;
        drawUI();
        usleep((rand() % 3000 + 1000) * 1000); // 1-4 sec

        // Chce wejść
        readers_info[idx].state = WAITING;
        drawUI();

        // Ochrona read_count
        pthread_mutex_lock(&r_mutex);
        read_count++;
        // Pierwszy czytelnik blokuje prawo do pisania
        if (read_count == 1) {
            pthread_mutex_lock(&w_mutex); 
        }
        pthread_mutex_unlock(&r_mutex);

        // --- CZYTANIE KRYTYCZNE ---
        readers_info[idx].state = READING;
        drawUI();
        usleep((rand() % 2000 + 1000) * 1000); // czytanie trwa 1-3 sec

        // Wychodzenie
        pthread_mutex_lock(&r_mutex);
        read_count--;
        // Ostatni czytelnik odblokowuje prawo do pisania
        if (read_count == 0) {
            pthread_mutex_unlock(&w_mutex); 
        }
        pthread_mutex_unlock(&r_mutex);
    }
    return NULL;
}

void* writerWorker(void* arg) {
    int idx = *((int*)arg);
    
    while (running) {
        // Inne zadania
        writers_info[idx].state = SLEEPING;
        drawUI();
        usleep((rand() % 4000 + 2000) * 1000); // 2-6 sec

        // Chce wpisać
        writers_info[idx].state = WAITING;
        drawUI();

        // Ochrona zasobu na pisanie
        pthread_mutex_lock(&w_mutex);

        // --- PISANIE KRYTYCZNE ---
        writers_info[idx].state = WRITING;
        resource_value += 10; // Zmiana wartosci udowadniajaca operacje zapisu
        drawUI();
        usleep((rand() % 2000 + 1000) * 1000);

        // Zwalnianie zasobu
        pthread_mutex_unlock(&w_mutex);
    }
    return NULL;
}

int main() {
    srand(time(NULL));

    // CURSES inicjalizacja
    initscr();
    cbreak();
    noecho();
    curs_set(0); 
    nodelay(stdscr, TRUE);

    // Konfiguracja wątków
    for (int i = 0; i < NUM_READERS; ++i) {
        readers_info[i].id = i + 1;
        readers_info[i].state = SLEEPING;
    }
    for (int i = 0; i < NUM_WRITERS; ++i) {
        writers_info[i].id = i + 1;
        writers_info[i].state = SLEEPING;
    }

    pthread_t readers[NUM_READERS];
    pthread_t writers[NUM_WRITERS];
    int r_idx[NUM_READERS];
    int w_idx[NUM_WRITERS];

    for (int i = 0; i < NUM_READERS; ++i) {
        r_idx[i] = i;
        pthread_create(&readers[i], NULL, readerWorker, &r_idx[i]);
    }

    for (int i = 0; i < NUM_WRITERS; ++i) {
        w_idx[i] = i;
        pthread_create(&writers[i], NULL, writerWorker, &w_idx[i]);
    }

    // Odswiez interfejs startowy
    drawUI();

    int ch;
    while (running) {
        ch = getch();
        if (ch == 'q' || ch == 'Q') {
            running = false;
        }
        usleep(100000); 
    }

    // Clean up
    endwin();

    return 0;
}
