#include "hardware.hpp"

void sleep() {
  esp_sleep_enable_timer_wakeup(1000000); // one second in microseconds
  esp_light_sleep_start();
}

void turnOffAllLights()
{
  
  for (int i = 0; i < 18; i++) {
    digitalWrite(allLeds[i], LOW);
  }
}

void turnOnAllLights()
{
  for (int i = 0; i < 18; i++) {
    digitalWrite(allLeds[i], HIGH);
  }
}

// Setup LEDS
void pullDownAllPins()
{
  pinMode(LED_B, OUTPUT);
  pinMode(LED_S1, OUTPUT);
  pinMode(LED_I, OUTPUT);
  pinMode(LED_D, OUTPUT);
  pinMode(LED_E, OUTPUT);
  pinMode(LED_S2, OUTPUT);
  pinMode(LED_0, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  pinMode(LED_5, OUTPUT);
  pinMode(LED_6, OUTPUT);
  pinMode(LED_7, OUTPUT);
  pinMode(LED_8, OUTPUT);
  pinMode(LED_9, OUTPUT);
  pinMode(LED_10, OUTPUT);
  pinMode(LED_11, OUTPUT);
}

void turnOffNumber(int numeral)
{
  switch (numeral)
  {
  case 0:
    digitalWrite(LED_0, LOW);
    break;
  case 1:
    digitalWrite(LED_1, LOW);
    break;
  case 2:
    digitalWrite(LED_2, LOW);
    break;
  case 3:
    digitalWrite(LED_3, LOW);
    break;
  case 4:
    digitalWrite(LED_4, LOW);
    break;
  case 5:
    digitalWrite(LED_5, LOW);
    break;
  case 6:
    digitalWrite(LED_6, LOW);
    break;
  case 7:
    digitalWrite(LED_7, LOW);
    break;
  case 8:
    digitalWrite(LED_8, LOW);
    break;
  case 9:
    digitalWrite(LED_9, LOW);
    break;
  case 10:
    digitalWrite(LED_10, LOW);
    break;
  case 11:
    digitalWrite(LED_11, LOW);
    break;
  default:
    break;
  }
}

// TODO make a lookup table for the numeral -> LED_X
void turnOnNumber(int numeral)
{
  switch (numeral)
  {
  case 0:
    digitalWrite(LED_0, HIGH);
    break;
  case 1:
    digitalWrite(LED_1, HIGH);
    break;
  case 2:
    digitalWrite(LED_2, HIGH);
    break;
  case 3:
    digitalWrite(LED_3, HIGH);
    break;
  case 4:
    digitalWrite(LED_4, HIGH);
    break;
  case 5:
    digitalWrite(LED_5, HIGH);
    break;
  case 6:
    digitalWrite(LED_6, HIGH);
    break;
  case 7:
    digitalWrite(LED_7, HIGH);
    break;
  case 8:
    digitalWrite(LED_8, HIGH);
    break;
  case 9:
    digitalWrite(LED_9, HIGH);
    break;
  case 10:
    digitalWrite(LED_10, HIGH);
    break;
  case 11:
    digitalWrite(LED_11, HIGH);
    break;
  default:
    break;
  }
}

void confirmationFlash() {
  turnOffAllLights();
  delay(50);
  turnOnAllLights();
  delay(50);
  turnOffAllLights();
  delay(50);
  turnOnAllLights();
  delay(50);
  turnOffAllLights();
  turnOffAllLights();
  delay(50);
  turnOnAllLights();
  delay(50);
  turnOffAllLights();
  delay(50);
  turnOnAllLights();
  delay(50);
  turnOffAllLights();
}