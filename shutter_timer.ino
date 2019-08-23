/* ATtiny85 Low-Power Timer */

#include <avr/sleep.h>

// Utility macros
#define adc_disable() (ADCSRA &= ~(1<<ADEN)) // disable ADC (before power-off)
#define adc_enable()  (ADCSRA |=  (1<<ADEN)) // re-enable ADC

// constants 
const int Speaker = 1;              // speaker pin
const int Lamp = 0;
const unsigned long Alarm = 180000; // alarm time - 3 minutes
unsigned long StartTime = 0;        // start time

void setup()
{
  pinMode(Lamp, OUTPUT);
  pinMode(Speaker, OUTPUT);
  adc_disable(); // ADC uses ~320uA
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  OSCCAL -= 4; //Calibrate 8 MHz timer - unique per chip
}

void enterSleep(void)
{
  sleep_enable();
  sleep_cpu();
}

void playBeep(unsigned int freq, unsigned int count, int length)
{
    for (int i=0; i < count; i++)
    {
      tone(Speaker, freq, length);
      delay(2 * length);
    }
}

void flashLed(int wait)
{
    digitalWrite(Lamp, HIGH);
    delay(wait);
    digitalWrite(Lamp, LOW);
}

// Main loop ----------------------------------------------

void loop()
{
  // Long flash
  digitalWrite(Lamp, HIGH);
  playBeep(800, 1, 250);
  digitalWrite(Lamp, LOW);
  
  do
  {
    // Flash light
    flashLed(3);
    delay(2000);
  } while (millis() + 10000 - StartTime < Alarm);
  
  do
  {
    // Play warning beeps
    flashLed(10);
    playBeep(300, 1, 35);
    delay(1000);
  } while (millis() - StartTime < Alarm);
  
  // Alarm
  playBeep(1500, 32, 20);
  enterSleep();
  // Continue after reset
}
