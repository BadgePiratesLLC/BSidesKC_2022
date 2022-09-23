#pragma once

#include <Arduino.h>
#include <HTTPClient.h>
#include <ESP32httpUpdate.h>
#include <WiFi.h>

#include "constants.hpp"

class OTA{
        // Update task
        bool isTaskRunning = true;
        TaskHandle_t task;
        
    public:

        static bool isWifiAvailable();
        void checkOTASync();
};