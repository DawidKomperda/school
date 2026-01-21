// Definicja częstotliwości taktowania procesora (16 MHz) - ważne dla funkcji opóźniających
#define F_CPU 16000000UL

#include <Arduino.h>
#include <TM1637Display.h>
#include <avr/io.h>
#include <util/delay.h>

// Definicje pinów dla wyświetlacza
#define CLK 3
#define DIO 4

// Definicja bitu dla przycisku (na porcie B)
#define BUTTON_BIT 0

// Definicje bitów dla diod LED (na porcie D)
#define LED_RED_BIT    5
#define LED_YELLOW_BIT 6
#define LED_GREEN_BIT  7

// Inicjalizacja obiektu obsługującego wyświetlacz 7-segmentowy TM1637
TM1637Display display(CLK, DIO);

// Tablica definiująca wygląd segmentów dla stanu oczekiwania (cztery myślniki "- - - -")
const uint8_t SEG_WAIT[] = { SEG_G, SEG_G, SEG_G, SEG_G };

// Zmienne globalne do obsługi logiki stopera
unsigned long startTime = 0;   // Przechowuje czas rozpoczęcia odliczania (w milisekundach)
bool isRunning = false;        // Flaga określająca, czy stoper aktualnie odlicza czas
uint8_t lastButtonState = 1;   // Przechowuje poprzedni stan przycisku (do wykrywania zbocza)

// Deklaracje funkcji
void displayTime(unsigned long timeInMillis);
void setReadyState();

int main(void) {
  // Inicjalizacja biblioteki Arduino (potrzebna m.in. do funkcji millis())
  init();

  // KONFIGURACJA PORTÓW WEJŚCIA/WYJŚCIA (Rejestry DDR)
  
  // Ustawienie pinów diod LED jako WYJŚCIA (OUTPUT) na porcie D.
  // Używamy operacji bitowej OR (|=), aby ustawić jedynki na pozycjach 5, 6 i 7, nie ruszając innych bitów.
  DDRD |= (1 << LED_RED_BIT) | (1 << LED_YELLOW_BIT) | (1 << LED_GREEN_BIT);

  // Ustawienie pinu przycisku jako WEJŚCIE (INPUT) na porcie B.
  // Używamy operacji AND z negacją (&= ~), aby wyzerować bit 0.
  DDRB &= ~(1 << BUTTON_BIT);
  
  // Włączenie wbudowanego rezystora podciągającego (INPUT_PULLUP) dla przycisku.
  // Zapisanie jedynki do rejestru PORT na pinie wejściowym aktywuje Pull-up.
  PORTB |= (1 << BUTTON_BIT);

  // Ustawienie jasności wyświetlacza na maksimum (0x0f)
  display.setBrightness(0x0f);
  
  // Ustawienie stanu początkowego (zielona dioda, myślniki na ekranie)
  setReadyState();

  // GŁÓWNA PĘTLA PROGRAMU (nieskończona)
  while (1) {
    // Odczyt aktualnego stanu przycisku z rejestru PINB.
    // Jeśli bit jest ustawiony, w zmiennej ląduje 1 (przycisk puszczony - pullup), jeśli zerem - 0 (wciśnięty).
    uint8_t currentButtonState = (PINB & (1 << BUTTON_BIT)) ? 1 : 0;

    // WYKRYWANIE ZBOCZA OPADAJĄCEGO (Moment wciśnięcia przycisku)
    // Sprawdzamy czy poprzednio przycisk był puszczony (1) A teraz jest wciśnięty (0).
    if (lastButtonState == 1 && currentButtonState == 0) {
      
      // ELIMINACJA DRGAŃ STYKÓW (Debouncing)
      _delay_ms(50); // Czekamy 50ms na ustabilizowanie się sygnału
      
      // Sprawdzamy ponownie, czy przycisk nadal jest wciśnięty
      if (! (PINB & (1 << BUTTON_BIT))) {
        
        // LOGIKA STEROWANIA STOPEREM
        if (!isRunning) {
          // *** START STOPERA ***
          isRunning = true;
          startTime = millis(); // Zapamiętujemy aktualny czas systemowy jako start
          
          // Wyłączamy diodę zieloną i czerwoną
          PORTD &= ~((1 << LED_GREEN_BIT) | (1 << LED_RED_BIT));
          // Włączamy diodę żółtą (sygnalizacja pracy)
          PORTD |= (1 << LED_YELLOW_BIT);
          
        } else {
          // *** STOP STOPERA ***
          isRunning = false;
          // Obliczamy czas końcowy: aktualny czas minus czas startu
          unsigned long finalTime = millis() - startTime;
          
          // Wyłączamy diodę zieloną i żółtą
          PORTD &= ~((1 << LED_GREEN_BIT) | (1 << LED_YELLOW_BIT));
          // Włączamy diodę czerwoną (sygnalizacja zatrzymania/wyniku)
          PORTD |= (1 << LED_RED_BIT);
          
          // Wyświetlamy ostateczny wynik na wyświetlaczu
          displayTime(finalTime);
        }
      }
    }
    
    // Aktualizacja stanu przycisku dla następnej iteracji pętli
    lastButtonState = currentButtonState;

    // Jeśli stoper działa, aktualizujemy wyświetlacz w czasie rzeczywistym
    if (isRunning) {
      unsigned long currentTime = millis() - startTime;
      displayTime(currentTime);
    }
  }
  
  return 0;
}

// Funkcja ustawiająca system w stan gotowości
void setReadyState() {
  // Wyświetla myślniki "----"
  display.setSegments(SEG_WAIT);
  
  // Wyłącza diodę żółtą i czerwoną
  PORTD &= ~((1 << LED_YELLOW_BIT) | (1 << LED_RED_BIT));
  // Włącza diodę zieloną (gotowość)
  PORTD |= (1 << LED_GREEN_BIT);
}

// Funkcja przeliczająca milisekundy na format SS:MM (Sekundy : Setne sekundy)
void displayTime(unsigned long timeInMillis) {
  // Obliczenie sekund (całkowita liczba sekund modulo 60, by liczyć 0-59)
  int seconds = (timeInMillis / 1000) % 60;
  
  // Obliczenie setnych części sekundy
  // Dzielimy przez 10 (bo 1 sekunda = 1000ms, a chcemy zakres 0-99), a potem modulo 100
  int hundredths = (timeInMillis / 10) % 100;
  
  // Złożenie liczby do wyświetlenia w formacie 4-cyfrowym (np. 1234 -> 12:34)
  int displayValue = (seconds * 100) + hundredths;
  
  // Wyświetlenie liczby dziesiętnej
  // 0x40 włącza dwukropek (COLON) na środku wyświetlacza
  // true oznacza, że wiodące zera będą wyświetlane (np. 01:05 zamiast 1: 5)
  display.showNumberDecEx(displayValue, 0x40, true);
}