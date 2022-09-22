#pragma once

#include <Arduino.h>
#include <HTTPClient.h>
#include <HttpsOTAUpdate.h>
#include <WiFi.h>

#include "constants.hpp"

class OTA{
        // Update task
        bool isTaskRunning = true;
        TaskHandle_t task;
        
    public:

        static void updateTask(void *parameter);
        static bool isWifiAvailable();
        
        void checkUpdate();
        void stopUpdate();
};