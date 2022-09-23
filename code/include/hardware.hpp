#pragma once

#include <Arduino.h>

#include "constants.hpp"

void sleep();
void turnOnAllLights();
void turnOffAllLights();
void confirmationFlash();
void errorFlash();
void pullDownAllPins();
void turnOffNumber(int numeral);
void turnOnNumber(int numeral);