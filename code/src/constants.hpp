#pragma once

#include <Arduino.h>

const int version = 0;
const bool OTA_ENABLED = true;

const int LED_B = 3;
const int LED_S1 = 34;
const int LED_I = 4;
const int LED_D = 33;
const int LED_E = 5;
const int LED_S2 = 26;

const int LED_0 = 6;
const int LED_1 = 21;
const int LED_2 = 14;
const int LED_3 = 35;
const int LED_4 = 10;
const int LED_5 = 15;
const int LED_6 = 36;
const int LED_7 = 11;
const int LED_8 = 16;
const int LED_9 = 37;
const int LED_10 = 12;
const int LED_11 = 17;

// in case patrick's rotary switch breaks
//const unsigned int ROTARY_SWITCH = GPIO_NUM_0;
const unsigned int ROTARY_SWITCH = GPIO_NUM_7;

const bool DEBUG = false;
const bool VERBOSE = true;
const bool INVERT_DIR = false;
const int INTERVAL = 500;                  // ms
const int BLING_MODE_TIMEOUT_INTERVAL = 6; // 500ms * 2  = ~one seconds

const int PIN_IN1 = 13;
const int PIN_IN2 = 38;
const int ROTARYSTEPS = 1;
const int ROTARYMIN = 0;
const int ROTARYMAX = 11;
const int NUM_BLING = 2;

const int CODE_0_ADDR = 0;
const int CODE_1_ADDR = 1;
const int CODE_2_ADDR = 2;
const int CODE_3_ADDR = 3;
const int CODE_4_ADDR = 4;
const int CODE_5_ADDR = 5;
const int CODE_JENNY_ADDR = 6;

// leave space because we are saving strings? I dunno how it works
const int WIFI_SSID_ADDR = 50;
const int WIFI_PASSWORD_ADDR = 30;

const int CODE_0[7] = {3, 1, 4, 1, 5, 9, 2}; // pi
const int CODE_1[7] = {1, 2, 3, 4, 5, 0 ,0}; // space balls
const int CODE_2[7] = {4, 2, 0, 0, 0, 0, 0}; // 42
const int CODE_3[7] = {1, 7, 2, 0, 0, 0, 0}; // 172
const int CODE_4[7] = {1, 3, 3, 7, 0, 0, 0}; // leet
const int CODE_5[7] = {6, 6, 6, 0, 0, 0, 0}; // mark of the devil
const int CODE_RESET[7] = {1, 1, 1, 1, 1, 1}; // reset
const int CODE_JENNY[7] = {8, 6, 7, 5, 3, 0, 9};

const String HELP_MSG = "Thank you for coming to BSidesKC and hacking on the badge. ";
const String JENNY_HELP_MSG = "If the wifi isn't working try calling jenny.";
const String CREDITS_MSG = "Building badges for fun not profit, this badge was brought to you by rixon, networkgeek, pecord, icona_p0p, JiggleBilly, MrARM, fg and Codexmafia.";
const String SPACE_BALLS_MSG = "Next hint is _JNGI1dI-e8";