#pragma once

#include <Arduino.h>
#include <RotaryEncoder.h>

#include "constants.hpp"

class Hardware{
    public:
        static void turnOffAllLights();
        static void turnOnNumber(int numeral);
        static void turnOffNumber(int numeral);
        static void pullDownAllPins();
        static void readEncoder(RotaryEncoder encoder, int &currentNumber, int &lastNumber, int &pos);
        static void updateNumber(int lastNumber, int currentNumber);
};