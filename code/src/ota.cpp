#include "ota.hpp"
#include "constants.hpp" // Not what you're supposed to do but I want intellicode or whatever it's named to shut up.

// I hate doing this but I don't want to waste an hour fixing it.
const char *WIFI_OTA_SSID PROGMEM = "PlexpodGuests";
const char *WIFI_OTA_PW PROGMEM = "@plexpod";
const char *OTA_BASE_URL PROGMEM = "https://discord.gr/";
const char *OTA_CERTIFICATE PROGMEM = R"(
-----BEGIN CERTIFICATE-----
MIIFKjCCBBKgAwIBAgISA4CxE2XAIHNYMjkR5W/KNOdhMA0GCSqGSIb3DQEBCwUA
MDIxCzAJBgNVBAYTAlVTMRYwFAYDVQQKEw1MZXQncyBFbmNyeXB0MQswCQYDVQQD
EwJSMzAeFw0yMjA5MjIwMDMyMzBaFw0yMjEyMjEwMDMyMjlaMBUxEzARBgNVBAMT
CmRpc2NvcmQuZ3IwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCrxxsM
7cYB+Oqps88IF0+iy3w0xGYS5u/zmBd5yWXuZkwfmpJ9M+4H+i4VYve08x/VTy6x
Z6hJQr/jzJq3MEbCaPUoqWRpb0xLZCTJ3O1Gn6Qfwu9vNtC8aSe44tYYcEAstPXu
j/cNjG4Dkudd1j68u8lbKBCgWvY39eGeFSNybo5pAQmkjKTJ19sFAZBIS5AgjDh6
CmB0eRgmMI5gCxe5JKCA3z8UANMJ5zRHNWN8VNKgneFX0csT0zwwJJeO6jQAn8xs
DGr3VLxeYNxGMcIJ3tnD42MejxzFkJDo2oa+ffHDHxqGaZsL4LIMRwjIklkrZi/6
oTihLxBl9pf9FoczAgMBAAGjggJVMIICUTAOBgNVHQ8BAf8EBAMCBaAwHQYDVR0l
BBYwFAYIKwYBBQUHAwEGCCsGAQUFBwMCMAwGA1UdEwEB/wQCMAAwHQYDVR0OBBYE
FGNOFYVWWqSUAsIWQqSll5o4AleXMB8GA1UdIwQYMBaAFBQusxe3WFbLrlAJQOYf
r52LFMLGMFUGCCsGAQUFBwEBBEkwRzAhBggrBgEFBQcwAYYVaHR0cDovL3IzLm8u
bGVuY3Iub3JnMCIGCCsGAQUFBzAChhZodHRwOi8vcjMuaS5sZW5jci5vcmcvMCUG
A1UdEQQeMByCCmRpc2NvcmQuZ3KCDnd3dy5kaXNjb3JkLmdyMEwGA1UdIARFMEMw
CAYGZ4EMAQIBMDcGCysGAQQBgt8TAQEBMCgwJgYIKwYBBQUHAgEWGmh0dHA6Ly9j
cHMubGV0c2VuY3J5cHQub3JnMIIBBAYKKwYBBAHWeQIEAgSB9QSB8gDwAHYA36Ve
q2iCTx9sre64X04+WurNohKkal6OOxLAIERcKnMAAAGDYtMthQAABAMARzBFAiEA
7qcWPXEb84GwdMBNwmQkzIYHrq5Ua7ZSVh+XNPA9OUwCIDPKgDo7/uCVp/hpMlXE
PRrprzX/VR9tKhhrQZ/7FXDvAHYARqVV63X6kSAwtaKJafTzfREsQXS+/Um4havy
/HD+bUcAAAGDYtMtvwAABAMARzBFAiAVdR+GF977cq3EGmW1Hbw5/swfCspdzqF4
qRMJwoZ3qQIhAKlA4yjjujS/+LoamBmwEj5ymb+3YBfrs2OJKaQt6xw8MA0GCSqG
SIb3DQEBCwUAA4IBAQAkoWevEhzqCv+pYOvHnUQnkAj5q83Xx2JQRz85CEN1Q3yR
fsf6vIqWJVgnp7Zg7UKAxIHE0fi8B3rVfwA7UC8o7b1OW/GhmIiLdAoq4lHjufkX
uGuQ5iruINMu/qQF2JPUghGSW92KCNQMjK/aX4RXTJDL5B69UjLDLwsGPemiRHWL
Imu8C+dLUkIWiAw8+OK7AGhpnKv6CkTifXi+9rdRY21ncXwKOQITWNuSV7jEFKLb
fZNPneCcx/g4J8xnYp/gYjkS5X7vUZVdQLMlbr/Z8psa+Fk7JuXS7sbr9luoPqqx
N5GNtKmA1fJBgAE2v+fkPt0XpptF8FWH9dNSk419
-----END CERTIFICATE-----
)";


// Checks whether or not our wifi can be seen
bool OTA::isWifiAvailable(){
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    int n = WiFi.scanNetworks();
    
    if (n == 0){
        if(DEBUG){
            Serial.println("OTA found no wifi networks, please check board.");
        }
    } else {
        for (int k = 0; k < n; ++k){
            if(WiFi.SSID(k) == WIFI_OTA_SSID){
                return true;
            }
        }
    }

    return false;
}

void OTA::updateTask(void *parameter){
    // Since this is a task, we don't get to use the memory of the OTA class.
    HTTPClient httpClient;

    // Check to see if our wifi is online
    if(!isWifiAvailable){
        if(DEBUG){
            Serial.println("OTA WiFi network not found");
        }
        vTaskDelete(NULL); // Should stop here, return is redundant but I don't have a board to test.
        return;
    }

    // Connect to WiFi
    WiFi.persistent(false); // Don't auto-connect on boot
    WiFi.begin(WIFI_OTA_SSID, WIFI_OTA_PW);

    // Wait some time to connect to wifi
    for (int i = 0; i < 25 && WiFi.status() != WL_CONNECTED; i++)
    {
        if(DEBUG){Serial.print(".");}
        delay(1000);
    }
    
    // Check if wifi failed to connect
    if(WiFi.status() != WL_CONNECTED){
        if(DEBUG){Serial.print("WIFI FAILED TO CONNECT!");}
        vTaskDelete(NULL); // Should stop here, return is redundant but I don't have a board to test.
        return;
    }

    // Try to download the manifest(pull file version, containing an int)
    char urlbuf[50];
    strcpy(urlbuf, OTA_BASE_URL);
    strcat(urlbuf, "version");

    httpClient.begin(urlbuf);
    int httpCode = httpClient.GET();

    if (httpCode == 200)
    {
        String newFWVersion = httpClient.getString();
        if(DEBUG){Serial.print("Current firmware version: ");}
        Serial.println(version);
        if(DEBUG){Serial.print("Available firmware version: ");}
        Serial.println(newFWVersion);

        int newVersion = newFWVersion.toInt();
        if (newVersion > version){
            Serial.println("UPDATING. \"DO NOT TURN OFF YOUR COMPUTER\"");
            char binbuf[50];
            strcpy(binbuf, OTA_BASE_URL);
            strcat(binbuf, "binary");
            HttpsOTA.begin(binbuf, OTA_CERTIFICATE);

            // Check update status every 100ms
            bool looping = true;
            while(looping){
                switch (HttpsOTA.status())
                {
                case HTTPS_OTA_SUCCESS:
                    ESP.restart();
                    break;

                case HTTPS_OTA_ERR:
                case HTTPS_OTA_FAIL:
                    Serial.println("THE UPDATE HAS FAILED.");
                    looping = false; // free up cycles
                    break;
                    
                default:
                    break;
                }
                delay(100);
            }
        }
    }
}

// Used during setup() to see if updates are available
void OTA::checkUpdate(){
    /*
    * Since we want to check the OTA status during
    * runtime without impacting the boot time, we
    * are going to have to run the OTA check under
    * a seperate thread.
    */
   xTaskCreatePinnedToCore(
      updateTask, /* Function to implement the task */
      "OTATask",   /* Name of the task */
      1000,       /* Stack size in words */
      NULL,       /* Task input parameter */
      0,          /* Priority of the task */
      &task,    /* Task handle. */
      0);         /* Core where the task should run */
}

// Kill any hung or running OTA threads if webserial activated
void OTA::stopUpdate(){
    if(isTaskRunning){
        isTaskRunning = false;
        vTaskDelete(task);
    }
}