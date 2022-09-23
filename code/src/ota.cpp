#include "ota.hpp"
#include "constants.hpp" // Not what you're supposed to do but I want intellicode or whatever it's named to shut up.

// I hate doing this but I don't want to waste an hour fixing it.
const char *WIFI_OTA_SSID PROGMEM = "PlexpodGuests";
const char *WIFI_OTA_PW PROGMEM = "@plexpod";
const char *OTA_BASE_URL PROGMEM = "http://discord.gr/";

// Checks whether or not our wifi can be seen
bool OTA::isWifiAvailable()
{
    if (DEBUG)
    {
        Serial.println("Scan init.");
    }
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    int n = WiFi.scanNetworks();
    if (DEBUG)
    {
        Serial.print(n);
        Serial.println(" networks found");
    }

    if (n == 0)
    {
        if (DEBUG)
        {
            Serial.println("OTA found no wifi networks, please check board.");
        }
    }
    else
    {
        for (int k = 0; k < n; ++k)
        {
            if (WiFi.SSID(k) == WIFI_OTA_SSID)
            {
                return true;
            }
        }
    }

    return false;
}

void OTA::checkOTASync()
{
    // Since this is a task, we don't get to use the memory of the OTA class.
    HTTPClient httpClient;

    // Set Lights to show progress
    // B-Start
    digitalWrite(LED_B, HIGH);
    // Check wifi
    if (!isWifiAvailable())
    {
        digitalWrite(LED_0, HIGH);
        digitalWrite(LED_3, HIGH);
        digitalWrite(LED_6, HIGH);
        digitalWrite(LED_9, HIGH);
        if (DEBUG)
        {
            Serial.println("OTA Wifi wasn't found.(LEDS:0,3,6,9)");
        }
        delay(10000);
        ESP.restart();
    }

    // Connect wifi
    WiFi.persistent(false); // Don't auto-connect on boot
    WiFi.begin(WIFI_OTA_SSID, WIFI_OTA_PW);

    // Wait some time to connect to wifi
    for (int i = 0; i < 25 && WiFi.status() != WL_CONNECTED; i++)
    {
        if (DEBUG)
        {
            Serial.print(".");
        }
        delay(1000);
    }

    // Check if wifi failed to connect
    if (WiFi.status() != WL_CONNECTED)
    {
        if (DEBUG)
        {
            Serial.print("WIFI FAILED TO CONNECT!");
        }
        WiFi.disconnect();
        digitalWrite(LED_0, HIGH);
        digitalWrite(LED_1, HIGH);
        digitalWrite(LED_3, HIGH);
        digitalWrite(LED_6, HIGH);
        digitalWrite(LED_9, HIGH);
        if (DEBUG)
        {
            Serial.println("Wifi didn't connect.(LEDS:0,1,3,6,9)");
        }
        delay(10000);
        ESP.restart();
        return;
    }
    if (DEBUG)
    {
        Serial.print("WiFi connected.");
    }
    // S1 - WiFi Connected
    digitalWrite(LED_S1, HIGH);

    // Check update server
    // Try to download the manifest(pull file version, containing an int)
    char urlbuf[50];
    strcpy(urlbuf, OTA_BASE_URL);
    strcat(urlbuf, "version");
    httpClient.begin(urlbuf);
    int httpCode = httpClient.GET();

    if (httpCode == 200)
    {
        // I - Manifest downloaded
        digitalWrite(LED_I, HIGH);

        // Check
        String newFWVersion = httpClient.getString();
        if (DEBUG)
        {
            Serial.print("Current firmware version: ");
        }
        Serial.println(version);
        if (DEBUG)
        {
            Serial.print("Available firmware version: ");
        }
        Serial.println(newFWVersion);

        int newVersion = newFWVersion.toInt();
        if (newVersion > version)
        {
            // D - Downloading update
            digitalWrite(LED_D, HIGH);

            Serial.println("UPDATING. \"DO NOT TURN OFF YOUR COMPUTER\"");
            char binbuf[50];
            strcpy(binbuf, OTA_BASE_URL);
            strcat(binbuf, "firmware.bin");
            t_httpUpdate_return ret = ESPhttpUpdate.update(binbuf);
            Serial.println("HTTP FINISHED");
            switch (ret)
            {
            case HTTP_UPDATE_FAILED:
                Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
                // 1 2 3 HTTP_UPDATE_FAILD manual reboot
                digitalWrite(LED_1, HIGH);
                digitalWrite(LED_2, HIGH);
                digitalWrite(LED_3, HIGH);
                for(;;){
                    delay(200);
                }
                break;

            case HTTP_UPDATE_NO_UPDATES:
                Serial.println("HTTP_UPDATE_NO_UPDATES");
                // 7,6,5 latest V
                digitalWrite(LED_E, HIGH);
                digitalWrite(LED_S2, HIGH);
                digitalWrite(LED_7, HIGH);
                digitalWrite(LED_6, HIGH);
                digitalWrite(LED_5, HIGH);
                delay(10000);
                ESP.restart();
                break;

            case HTTP_UPDATE_OK:
                Serial.println("HTTP_UPDATE_OK");
                digitalWrite(LED_E, HIGH);
                digitalWrite(LED_S2, HIGH);
                ESP.restart();
                break;
            }
        } else {
            // 7,6,5 - Latest version
            digitalWrite(LED_D, HIGH);
            digitalWrite(LED_E, HIGH);
            digitalWrite(LED_S2, HIGH);
            digitalWrite(LED_7, HIGH);
            digitalWrite(LED_6, HIGH);
            digitalWrite(LED_5, HIGH);
            delay(10000);
            ESP.restart();
        }
        WiFi.disconnect();
    }
    else
    {
        if (DEBUG)
        {
            Serial.println("HTTP didn't throw a 200 :(");
            Serial.println(urlbuf);
            Serial.println(httpCode);
            WiFi.disconnect();
        }
    }
}