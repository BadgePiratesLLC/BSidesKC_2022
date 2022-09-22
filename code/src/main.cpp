#include <Arduino.h>

#include <AsyncTCP.h>
#include <BfButton.h>
#include <EEPROM.h>
#include <ESPAsyncWebServer.h>
#include <RotaryEncoder.h>
#include <WebSerial.h>
#include <WiFi.h>

#include "constants.hpp"
#include "hardware.hpp"
#include "Flasher.hpp"

static int pos = 0;
static int dir = 0;
static int currentNumber = 0;
static int lastNumber = 0;


int inputPosition = 0;
int userInputLength = 7;
static int userInput[7] = {0, 0, 0, 0, 0, 0, 0};

static bool isCode0Unlocked = false;
static bool isCode1Unlocked = false;
static bool isCode2Unlocked = false;
static bool isCode3Unlocked = false;
static bool isCode4Unlocked = false;
static bool isCode5Unlocked = false;
static bool isCodeJennyUnlocked = false;

static String ssid = "SAFE-";
static String password = "";

enum ProgramState
{
  BLING_MODE = 0,
  INPUT_MODE = 1
};

enum ProgramState previousState = INPUT_MODE;
enum ProgramState currentState = INPUT_MODE;

unsigned long previousTime = 0;
unsigned long currentTime = 0;
unsigned long lastWifiMsgTimeMs = 0;
int numIntervalsWithoutInput = 0;
bool hasInputChangedDuringInterval = false;
bool wifiSerialOn = false;

BfButton btn(BfButton::STANDALONE_DIGITAL, ROTARY_SWITCH, true, LOW);

AsyncWebServer server(80);

// helper methods
// wraps both serial and web serial println methods 
// so we don't always have to call (or forget)
// OTA MODE: Webserial might be neutered for both security and action conflicts.
void SerialPrintln(String msg) {
  if (wifiSerialOn) {
    WebSerial.println(msg);
  }
  Serial.println(msg);
}

void SerialPrintln(int msg) {
  if (wifiSerialOn) {
    WebSerial.println(msg);
  }
  Serial.println(msg);
}

void SerialPrint(String msg) {
  if (wifiSerialOn) {
    WebSerial.print(msg);
  }
  Serial.print(msg);
}

void SerialPrint(int msg) {
  if (wifiSerialOn) {
    WebSerial.print(msg);
  }
  Serial.print(msg);
}

/* Message callback of WebSerial */
void recvMsg(uint8_t *data, size_t len) {
  String d = "";
  for(int i=0; i < len; i++){
    d += char(data[i]);
  }

  if (d.indexOf("help") != -1) {
    SerialPrintln("<< " + d);
    SerialPrintln(HELP_MSG + " " + JENNY_HELP_MSG);
  } else if (d.indexOf("credits")) {
    SerialPrintln("<< " + d);
    SerialPrintln(CREDITS_MSG);
  } else {  
    SerialPrintln("Received Data...");
    SerialPrintln(d);
  }

  lastWifiMsgTimeMs = millis();
}

void setupWifiSerial() {  
  if (password.length() == 0 && ssid.length() == 9) {
    Serial.println("Setting up wifi for the first time...");
    // we need a unique SSID and PW for each badge, use micros to get a random time offset for the PW
    delay(50);
    long time = micros();
    char passwordRaw[16];
    ltoa(time, passwordRaw, 10);
    // cast it as a string
    String password = String(passwordRaw);
    int passwordLength = password.length();
    // uuse the last 3 of the password for the ssid
    String uniqueSSID = password.substring(passwordLength-3, passwordLength);
    bool success = ssid.concat(uniqueSSID);
    password.concat("1");
    char SSID[ssid.length()+1];
    char PASSWORD[password.length()+1];
    
    ssid.toCharArray(SSID, ssid.length()+1);
    password.toCharArray(PASSWORD, password.length()+1);
    WiFi.softAP(SSID, PASSWORD);

    SerialPrint("SSID: ");
    SerialPrintln(SSID);
    SerialPrint("Password: ");
    SerialPrintln(PASSWORD);
    
    // save wifi password to eeprom
    EEPROM.writeString(WIFI_SSID_ADDR, SSID);
    EEPROM.writeString(WIFI_PASSWORD_ADDR, PASSWORD);
    EEPROM.commit();
  } else {
    SerialPrintln("Jenny is fixing the wifi...");
    int ssidLength = ssid.length() + 1;
    int passwordLength = password.length() + 1;
    char SSID[ssidLength];
    char PASSWORD[passwordLength];
    ssid.toCharArray(SSID, ssidLength);
    password.toCharArray(PASSWORD, passwordLength);
    WiFi.softAP(SSID, PASSWORD);

    SerialPrint("SSID: ");
    SerialPrintln(SSID);
    SerialPrint("Password: ");
    SerialPrintln(PASSWORD);
  }
  
  IPAddress IP = WiFi.softAPIP();
  Serial.println("Web Serial: http://" + IP.toString() + "/");
  WebSerial.begin(&server, "/");
  WebSerial.msgCallback(recvMsg);
  server.begin();
  wifiSerialOn = true;
  lastWifiMsgTimeMs = millis();
}

Flasher led1 = Flasher();
// Setup a RotaryEncoder with 2 steps per latch for the 2 signal input pins:
RotaryEncoder encoder(PIN_IN1, PIN_IN2, RotaryEncoder::LatchMode::TWO03);



void resetUserInput()
{
  inputPosition = 0;
  for (int i = 0; i < userInputLength; i++)
  {
    userInput[i] = 0;
  }
}

// TODO can probably make this better ;) 
void checkIsValidCode()
{
  boolean isCode0 = true;
  boolean isCode1 = true;
  boolean isCode2 = true;
  boolean isCode3 = true;
  boolean isCode4 = true;
  boolean isCode5 = true;
  boolean isCodeJenny = true;
  boolean isCodeReset = true;

  int i = 0;
  //Check code 1
  while (i < userInputLength && isCode0)
  {
    isCode0 = userInput[i] == CODE_0[i];
    i++;
  }

  i = 0;
  while (i < userInputLength && isCodeJenny)
  {
    isCodeJenny = userInput[i] == CODE_JENNY[i];
    i++;
  }

  i = 0;
  while (i < userInputLength && isCodeReset)
  {
    isCodeReset = userInput[i] == CODE_RESET[i];
    i++;
  }

  i = 0;
  while (i < userInputLength && isCodeJenny)
  {
    isCodeJenny = userInput[i] == CODE_JENNY[i];
    i++;
  }

  i = 0;
  while (i < userInputLength && isCode1)
  {
    isCode1 = userInput[i] == CODE_1[i];
    i++;
  }

  i = 0;
  while (i < userInputLength && isCode2)
  {
    isCode2 = userInput[i] == CODE_2[i];
    i++;
  }

  i = 0;
  while (i < userInputLength && isCode3)
  {
    isCode3 = userInput[i] == CODE_3[i];
    i++;
  }

  i = 0;
  while (i < userInputLength && isCode4)
  {
    isCode4 = userInput[i] == CODE_4[i];
    i++;
  }

  i = 0;
  while (i < userInputLength && isCode5)
  {
    isCode5 = userInput[i] == CODE_5[i];
    i++;
  }

  if (isCodeReset) {
    Serial.println("Resetting EEPROM");
    isCode0Unlocked = false;
    isCode1Unlocked = false;
    isCode2Unlocked = false;
    isCode3Unlocked = false;
    isCode4Unlocked = false;
    isCode5Unlocked = false;
    EEPROM.writeBool(CODE_0_ADDR, false);
    EEPROM.writeBool(CODE_1_ADDR, false);
    EEPROM.writeBool(CODE_2_ADDR, false);
    EEPROM.writeBool(CODE_3_ADDR, false);
    EEPROM.writeBool(CODE_4_ADDR, false);
    EEPROM.writeBool(CODE_5_ADDR, false);
    EEPROM.writeBool(CODE_JENNY_ADDR, false);
    EEPROM.writeString(WIFI_SSID_ADDR, "");
    EEPROM.writeString(WIFI_PASSWORD_ADDR, "");
    EEPROM.commit();
  }

  if (isCode0)
  {
    isCode0Unlocked = true;
    EEPROM.writeBool(CODE_0_ADDR, isCode0Unlocked);
    Serial.println("CODE 0 MATCHES");
  }

  if (isCodeJenny)
  {
    isCodeJennyUnlocked = true;
    EEPROM.writeBool(CODE_JENNY_ADDR, isCodeJennyUnlocked);
    Serial.println("CODE JENNY TYPED IN");
    setupWifiSerial();
  }

  if(isCode1){
    isCode1Unlocked = true;
    EEPROM.writeBool(CODE_1_ADDR, isCode1Unlocked);
    Serial.print("CODE 1 MATCHES:");
  }
  
  if(isCode2){
    isCode2Unlocked = true;
    EEPROM.writeBool(CODE_2_ADDR, isCode2Unlocked);
    Serial.println("CODE 2 MATCHES");
  }

  if(isCode3){
    isCode3Unlocked = true;
    EEPROM.writeBool(CODE_3_ADDR, isCode3Unlocked);
    Serial.println("CODE 3 MATCHES");
  }

  if(isCode4){
    isCode4Unlocked = true;
    EEPROM.writeBool(CODE_4_ADDR, isCode4Unlocked);
    Serial.println("CODE 4 MATCHES");
  }

  if(isCode5){
    isCode5Unlocked = true;
    EEPROM.writeBool(CODE_5_ADDR, isCode5Unlocked);
    Serial.println("CODE 5 MATCHES");
  }

  if (isCode0 || isCode1 || isCode2 || isCode3 || isCode4 || isCode5 || isCodeJennyUnlocked) {
    EEPROM.commit();
  }

}

void logCode()
{
  SerialPrint("User Input: ");
  for (int i = 0; i < userInputLength; i++)
  {
    SerialPrint(userInput[i]);
  }
  SerialPrintln("");
}

void pressHandler(BfButton *btn, BfButton::press_pattern_t pattern)
{
  switch (pattern)
  {
  case BfButton::SINGLE_PRESS:
    if (currentState == BLING_MODE)
    {
      led1.handleBlingChange();
    }
    else
    {
      numIntervalsWithoutInput = 0;
      userInput[inputPosition] = currentNumber;
      logCode();
      checkIsValidCode();
      if (inputPosition < userInputLength)
      {
        inputPosition++;
      }
      else
      {
        resetUserInput();
      }
    }
    break;

  case BfButton::DOUBLE_PRESS:
    Serial.println("Double push");
    break;

  case BfButton::LONG_PRESS:
    Serial.println("Long push");
    break;
  }
}



// TODO copied from BlinkyLights.ino - ghetto, needs clean up, don't use delay, blocks for five seconds
void blingMode(unsigned long currentTime)
{
  if (currentState == BLING_MODE && previousState != BLING_MODE)
  {
    resetUserInput();
    Hardware::turnOffAllLights();
    if (DEBUG) {
      Serial.println("doing bling mode stuffz");
    }
  }
  led1.Update(currentTime);
}

bool hasInputChanged()
{
  Hardware::readEncoder(encoder, currentNumber, lastNumber, pos);
  if (lastNumber != currentNumber)
    return true;
  return false;
}

// TODO see about using interupts for detecting when the input changes
void inputMode(bool hasInputChanged)
{
  if(isCode0Unlocked) {
    digitalWrite(LED_B, HIGH);
  }

  if(isCode1Unlocked) {
    digitalWrite(LED_S1, HIGH);
  }

  if(isCode2Unlocked) {
    digitalWrite(LED_I, HIGH);
  }

  if(isCode3Unlocked) {
    digitalWrite(LED_D, HIGH);
  }

  if(isCode4Unlocked) {
    digitalWrite(LED_E, HIGH);
  }

  if(isCode5Unlocked) {
    digitalWrite(LED_S2, HIGH);
  }

  if (currentState == INPUT_MODE && previousState == BLING_MODE)
  {
    Hardware::turnOffAllLights();
    if (DEBUG) {
      Serial.println("doing input mode stuffz");
    }
  }

  // currently handles spinning the encoder knob and updating the numbers
  // needs to also "save" off the number when they press the button
  if (hasInputChanged)
  {
    Hardware::updateNumber(lastNumber, currentNumber);
  }


}

IRAM_ATTR void checkPosition()
{
  encoder.tick(); // just call tick() to check the state.
}

void setup()
{
  EEPROM.begin(512);
  Serial.begin(115200);
  encoder.setPosition(0 / ROTARYSTEPS);
  Hardware::pullDownAllPins();
  Hardware::turnOffAllLights();

  // register interrupt routine
  attachInterrupt(digitalPinToInterrupt(PIN_IN1), checkPosition, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_IN2), checkPosition, CHANGE);

  // Butt stuff
  // Button settings
  btn.onPress(pressHandler)
      .onDoublePress(pressHandler)     // default timeout
      .onPressFor(pressHandler, 1000); // custom timeout for 1 second

  isCode0Unlocked = EEPROM.readBool(CODE_0_ADDR);  
  isCode1Unlocked = EEPROM.readBool(CODE_1_ADDR);
  isCode2Unlocked = EEPROM.readBool(CODE_2_ADDR);  
  isCode3Unlocked = EEPROM.readBool(CODE_3_ADDR);  
  isCode4Unlocked = EEPROM.readBool(CODE_4_ADDR);  
  isCode5Unlocked = EEPROM.readBool(CODE_5_ADDR);
  isCodeJennyUnlocked = EEPROM.readBool(CODE_JENNY_ADDR);

  String savedWifiSSID = EEPROM.readString(WIFI_SSID_ADDR);
  String savedWifiPwd = EEPROM.readString(WIFI_PASSWORD_ADDR);
  if (savedWifiPwd.length() > 0) {
    if (DEBUG) {
      Serial.print("Found existing wifi creds");
      Serial.print("SSID: ");
      Serial.println(savedWifiSSID);
      Serial.print("Password: ");
      Serial.println(savedWifiPwd);
    }
    ssid = savedWifiSSID;
    password = savedWifiPwd;
  }

  if (DEBUG) {
    Serial.print("isCode0Unlocked: ");
    Serial.println(isCode0Unlocked ? "true" : "false");
    Serial.print("isCode1Unlocked: ");
    Serial.println(isCode1Unlocked ? "true" : "false");
    Serial.print("isCode2Unlocked: ");
    Serial.println(isCode2Unlocked ? "true" : "false");
    Serial.print("isCode3Unlocked: ");
    Serial.println(isCode3Unlocked ? "true" : "false");
    Serial.print("isCode5Unlocked: ");
    Serial.println(isCode5Unlocked ? "true" : "false");
    Serial.print("isCode4Unlocked: ");
    Serial.println(isCode4Unlocked ? "true" : "false");
    Serial.print("isCodeJennyUnlocked: ");
    Serial.println(isCodeJennyUnlocked ? "true" : "false");
  }

  SerialPrintln(HELP_MSG);
  if (isCodeJennyUnlocked) {
    setupWifiSerial();
  } else {
    SerialPrintln(JENNY_HELP_MSG);
  }

  if (isCode0Unlocked || isCode2Unlocked || isCode3Unlocked || isCode4Unlocked || isCode5Unlocked || isCodeJennyUnlocked) {
    SerialPrintln(SPACE_BALLS_MSG);
  }
}

void loop() {
  encoder.tick();
  btn.read();

  previousState = currentState;
  currentTime = millis();
  bool inputChanged = hasInputChanged();

  if (inputChanged)
  {
    hasInputChangedDuringInterval = true;
  }

  // TODO move into a timer instead of doing it in the main loop
  // and/or look into using the encoder.getMillisBetweenRotations function
  if ((currentTime - previousTime) >= INTERVAL)
  {
    previousTime = currentTime;

    if (hasInputChangedDuringInterval)
    {
      hasInputChangedDuringInterval = false;
      numIntervalsWithoutInput = 0;
    }
    else
    {
      numIntervalsWithoutInput += 1;
    }
  }

  // if we go so long without any input fallback to bling mode
  if (numIntervalsWithoutInput >= BLING_MODE_TIMEOUT_INTERVAL)
  {
    currentState = BLING_MODE;
  }
  else
  {
    currentState = INPUT_MODE;
  }

  if (DEBUG && previousState != currentState)
  {
    Serial.print("Interval time has passed: ");
    Serial.print(INTERVAL);
    Serial.print("ms, hasInputChangedDuringInterval: ");
    Serial.print(hasInputChangedDuringInterval ? "true" : "false");
    Serial.print(", numIntervalsWithoutInput: ");
    Serial.print(numIntervalsWithoutInput);
    Serial.print(", current state: ");
    Serial.println(currentState == INPUT_MODE ? "input mode" : "bling mode");
  }

  // two states to start - "bling" mode and "input" mode
  // if the input hasn't changed for a second or two go into bling mode
  // once the knob moves, come out of bling mode into input mode

  // ghetto state machine
  switch (currentState)
  {
  case BLING_MODE:
    blingMode(currentTime);
    break;
  case INPUT_MODE:
    inputMode(inputChanged);
    break;
  default:
    inputMode(inputChanged);
  }

  if (isCodeJennyUnlocked && lastWifiMsgTimeMs != 0) {
    unsigned long timeSinceLastWifiMsgInMs = millis() - lastWifiMsgTimeMs;
    if (timeSinceLastWifiMsgInMs >= 60000 && wifiSerialOn) { 
      SerialPrintln("Last message recieved on wifi more than one minute ago, turning off wifi, you can reset the badge to turn it back on.");
      WiFi.disconnect(true);
      server.end();
      wifiSerialOn = false;
    }
  }
}

