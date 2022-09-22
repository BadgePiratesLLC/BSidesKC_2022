#pragma once

#include <Arduino.h>

#include "constants.hpp"

class Flasher
{
  // Class Member Variables
  // These are initialized at startup
  int ledPin = LED_B; // the number of the LED pin
  long OnTime = 25;   // milliseconds of on-time
  long OffTime = 25;  // milliseconds of off-time
  int interval = 25;
  int index = 0;
  int selectedBling = 0;
  const static int PATTERN_1_INDEX_MAX = 132;
  const static int PATTERN_2_INDEX_MAX = 24;

  int pattern[PATTERN_1_INDEX_MAX][2] = {
      // bsides letters on then off in forward order
      {LED_B, HIGH},
      {LED_B, LOW},
      {LED_S1, HIGH},
      {LED_S1, LOW},
      {LED_I, HIGH},
      {LED_I, LOW},
      {LED_D, HIGH},
      {LED_D, LOW},
      {LED_E, HIGH},
      {LED_E, LOW},
      {LED_S2, HIGH},
      {LED_S2, LOW},
      // bsides letters on then off in backwards order
      {LED_S2, HIGH},
      {LED_S2, LOW},
      {LED_E, HIGH},
      {LED_E, LOW},
      {LED_D, HIGH},
      {LED_D, LOW},
      {LED_I, HIGH},
      {LED_I, LOW},
      {LED_S1, HIGH},
      {LED_S1, LOW},
      {LED_B, HIGH},
      {LED_B, LOW},
      // all the number leds on and off in forward order
      {LED_0, HIGH},
      {LED_0, LOW},
      {LED_1, HIGH},
      {LED_1, LOW},
      {LED_2, HIGH},
      {LED_2, LOW},
      {LED_3, HIGH},
      {LED_3, LOW},
      {LED_4, HIGH},
      {LED_4, LOW},
      {LED_5, HIGH},
      {LED_5, LOW},
      {LED_6, HIGH},
      {LED_6, LOW},
      {LED_7, HIGH},
      {LED_7, LOW},
      {LED_8, HIGH},
      {LED_8, LOW},
      {LED_9, HIGH},
      {LED_9, LOW},
      {LED_10, HIGH},
      {LED_10, LOW},
      {LED_11, HIGH},
      {LED_11, LOW},
      // all the number leds on then off in backwards order
      {LED_11, HIGH},
      {LED_11, LOW},
      {LED_10, HIGH},
      {LED_10, LOW},
      {LED_9, HIGH},
      {LED_9, LOW},
      {LED_8, HIGH},
      {LED_8, LOW},
      {LED_7, HIGH},
      {LED_7, LOW},
      {LED_6, HIGH},
      {LED_6, LOW},
      {LED_5, HIGH},
      {LED_5, LOW},
      {LED_4, HIGH},
      {LED_4, LOW},
      {LED_3, HIGH},
      {LED_3, LOW},
      {LED_2, HIGH},
      {LED_2, LOW},
      {LED_1, HIGH},
      {LED_1, LOW},
      {LED_0, HIGH},
      {LED_0, LOW},
      // light up all the letters then turn them all off in reverse order
      {LED_B, HIGH},
      {LED_S1, HIGH},
      {LED_I, HIGH},
      {LED_D, HIGH},
      {LED_E, HIGH},
      {LED_S2, HIGH},
      {LED_S2, LOW},
      {LED_E, LOW},
      {LED_D, LOW},
      {LED_I, LOW},
      {LED_S1, LOW},
      {LED_B, LOW},
      // light up all the numbers in order then turn them all off in reverse order
      {LED_0, HIGH},
      {LED_1, HIGH},
      {LED_2, HIGH},
      {LED_3, HIGH},
      {LED_4, HIGH},
      {LED_5, HIGH},
      {LED_6, HIGH},
      {LED_7, HIGH},
      {LED_8, HIGH},
      {LED_9, HIGH},
      {LED_10, HIGH},
      {LED_11, HIGH},
      {LED_11, LOW},
      {LED_10, LOW},
      {LED_9, LOW},
      {LED_8, LOW},
      {LED_7, LOW},
      {LED_6, LOW},
      {LED_5, LOW},
      {LED_4, LOW},
      {LED_3, LOW},
      {LED_2, LOW},
      {LED_1, LOW},
      {LED_0, LOW}};

  int inputPattern[PATTERN_2_INDEX_MAX][2] = {
      // bsides letters on then off in forward order
      {LED_B, HIGH},
      {LED_B, LOW},
      {LED_S1, HIGH},
      {LED_S1, LOW},
      {LED_I, HIGH},
      {LED_I, LOW},
      {LED_D, HIGH},
      {LED_D, LOW},
      {LED_E, HIGH},
      {LED_E, LOW},
      {LED_S2, HIGH},
      {LED_S2, LOW},
      // bsides letters on then off in backwards order
      {LED_S2, HIGH},
      {LED_S2, LOW},
      {LED_E, HIGH},
      {LED_E, LOW},
      {LED_D, HIGH},
      {LED_D, LOW},
      {LED_I, HIGH},
      {LED_I, LOW},
      {LED_S1, HIGH},
      {LED_S1, LOW},
      {LED_B, HIGH},
      {LED_B, LOW},
  };

  // These maintain the current state
  int ledState;                 // ledState used to set the LED
  unsigned long previousMillis; // will store last time LED was updated

  // Constructor - creates a Flasher
  // and initializes the member variables and state
public:
  Flasher()
  {
    ledState = LOW;
    previousMillis = 0;
  }

  void Update(unsigned long currentMillis);
  void handleBlingChange();
};