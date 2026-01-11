#define F_CPU 16000000UL

#include <Arduino.h>
#include <TM1637Display.h>
#include <avr/io.h>
#include <util/delay.h>

#define CLK 3
#define DIO 4

#define BUTTON_BIT 0

#define LED_RED_BIT    5
#define LED_YELLOW_BIT 6
#define LED_GREEN_BIT  7

TM1637Display display(CLK, DIO);

const uint8_t SEG_WAIT[] = { SEG_G, SEG_G, SEG_G, SEG_G };

unsigned long startTime = 0;
bool isRunning = false;
uint8_t lastButtonState = 1;

void displayTime(unsigned long timeInMillis);
void setReadyState();

int main(void) {
  init();

  DDRD |= (1 << LED_RED_BIT) | (1 << LED_YELLOW_BIT) | (1 << LED_GREEN_BIT);

  DDRB &= ~(1 << BUTTON_BIT);
  PORTB |= (1 << BUTTON_BIT);

  display.setBrightness(0x0f);
  setReadyState();

  while (1) {
    uint8_t currentButtonState = (PINB & (1 << BUTTON_BIT)) ? 1 : 0;

    if (lastButtonState == 1 && currentButtonState == 0) {
      _delay_ms(50);
      
      if (! (PINB & (1 << BUTTON_BIT))) {
        
        if (!isRunning) {
          isRunning = true;
          startTime = millis();
          
          PORTD &= ~((1 << LED_GREEN_BIT) | (1 << LED_RED_BIT));
          PORTD |= (1 << LED_YELLOW_BIT);
          
        } else {
          isRunning = false;
          unsigned long finalTime = millis() - startTime;
          
          PORTD &= ~((1 << LED_GREEN_BIT) | (1 << LED_YELLOW_BIT));
          PORTD |= (1 << LED_RED_BIT);
          
          displayTime(finalTime);
        }
      }
    }
    
    lastButtonState = currentButtonState;

    if (isRunning) {
      unsigned long currentTime = millis() - startTime;
      displayTime(currentTime);
    }
  }
  
  return 0;
}

void setReadyState() {
  display.setSegments(SEG_WAIT);
  PORTD &= ~((1 << LED_YELLOW_BIT) | (1 << LED_RED_BIT));
  PORTD |= (1 << LED_GREEN_BIT);
}

void displayTime(unsigned long timeInMillis) {
  int seconds = (timeInMillis / 1000) % 60;
  int hundredths = (timeInMillis / 10) % 100;
  int displayValue = (seconds * 100) + hundredths;
  display.showNumberDecEx(displayValue, 0x40, true);
}