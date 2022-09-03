#include <Arduino.h>
#include <RotaryEncoder.h>

#define PIN_IN1 13
#define PIN_IN2 38
#define ROTARYSTEPS 1
#define ROTARYMIN 0
#define ROTARYMAX 11

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

const bool DEBUG=true;
const bool VERBOSE=false;
const bool INVERT_DIR=false;

static int pos = 0;
static int dir = 0;
static int currentNumber = 0;
static int lastNumber = 0;

enum ProgramState {
    BLING_MODE = 0, 
    INPUT_MODE = 1
};

enum ProgramState previousState = INPUT_MODE;
enum ProgramState currentState = INPUT_MODE;

long previousTime = 0;
long currentTime = 0;
const int INTERVAL = 500; // ms
const int BLING_MODE_TIMEOUT_INTERVAL = 2; // 500ms * 2  = ~one seconds


// Setup a RotaryEncoder with 2 steps per latch for the 2 signal input pins:
RotaryEncoder encoder(PIN_IN1, PIN_IN2, RotaryEncoder::LatchMode::TWO03);

void turnOffAllLights() {
  digitalWrite(LED_0, LOW);
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
  digitalWrite(LED_3, LOW);
  digitalWrite(LED_4, LOW);
  digitalWrite(LED_5, LOW);
  digitalWrite(LED_6, LOW);
  digitalWrite(LED_7, LOW);
  digitalWrite(LED_8, LOW);
  digitalWrite(LED_9, LOW);
  digitalWrite(LED_10, LOW);
  digitalWrite(LED_11, LOW); 
}

//TODO make a lookup table for the numeral -> LED_X
void turnOnNumber(int numeral) {
    switch (numeral) {
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

void turnOffNumber(int numeral) {
    switch (numeral) {
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

// Setup LEDS
void pullDownAllPins() {
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

// Read the current position of the encoder and print out when changed.
void readEncoder() {
  int newPos = encoder.getPosition();
  int newDir = (int)(encoder.getDirection());
  // my board (pecord) has the encoder wired backwards
  // instead of fixing the solder I "fixed" it in code
  // if its going backwards for you flip that flag
  if (INVERT_DIR) {
    newDir *= -1;
  }

  // save off the previous number 
  lastNumber = currentNumber;
  // get the new number
  currentNumber += newDir;
  if (currentNumber > ROTARYMAX) {
    currentNumber = ROTARYMIN;
  } else if (currentNumber < ROTARYMIN) {
    currentNumber = ROTARYMAX;
  }

  if (pos != newPos) {
    pos = newPos;
  }

  if (VERBOSE) {
    Serial.print("pos:");
    Serial.print(newPos);
    Serial.print(" dir:");
    Serial.println(newDir);
  }
}

// TODO copied from BlinkyLights.ino - ghetto, needs clean up, don't use delay, blocks for five seconds
void blingMode() {
    if (currentState == BLING_MODE && previousState != BLING_MODE) {
        turnOffAllLights();
        Serial.println("doing bling mode stuffz");
    }
    // digitalWrite(3,HIGH);delay(25);
    // digitalWrite(3,LOW);delay(25);
    // digitalWrite(34,HIGH);delay(25);
    // digitalWrite(34,LOW);delay(25);
    // digitalWrite(4,HIGH);delay(25);
    // digitalWrite(4,LOW);delay(25);
    // digitalWrite(33,HIGH);delay(25);
    // digitalWrite(33,LOW);delay(25);
    // digitalWrite(5,HIGH);delay(25);
    // digitalWrite(5,LOW);delay(25);
    // digitalWrite(26,HIGH);delay(25);
    // digitalWrite(26,LOW);delay(25);

    // digitalWrite(26,HIGH);delay(25);
    // digitalWrite(26,LOW);delay(25);
    // digitalWrite(5,HIGH);delay(25);
    // digitalWrite(5,LOW);delay(25);
    // digitalWrite(33,HIGH);delay(25);
    // digitalWrite(33,LOW);delay(25);
    // digitalWrite(4,HIGH);delay(25);
    // digitalWrite(4,LOW);delay(25);
    // digitalWrite(34,HIGH);delay(25);
    // digitalWrite(34,LOW);delay(25);
    // digitalWrite(3,HIGH);delay(25);
    // digitalWrite(3,LOW);delay(25);

    // digitalWrite(6,HIGH);delay(25);
    // digitalWrite(6,LOW);delay(25);
    // digitalWrite(21,HIGH);delay(25);
    // digitalWrite(21,LOW);delay(25);
    // digitalWrite(14,HIGH);delay(25);
    // digitalWrite(14,LOW);delay(25);
    // digitalWrite(35,HIGH);delay(25);
    // digitalWrite(35,LOW);delay(25);
    // digitalWrite(10,HIGH);delay(25);
    // digitalWrite(10,LOW);delay(25);
    // digitalWrite(15,HIGH);delay(25);
    // digitalWrite(15,LOW);delay(25);
    // digitalWrite(36,HIGH);delay(25);
    // digitalWrite(36,LOW);delay(25);
    // digitalWrite(11,HIGH);delay(25);
    // digitalWrite(11,LOW);delay(25);
    // digitalWrite(16,HIGH);delay(25);
    // digitalWrite(16,LOW);delay(25);
    // digitalWrite(37,HIGH);delay(25);
    // digitalWrite(37,LOW);delay(25);
    // digitalWrite(12,HIGH);delay(25);
    // digitalWrite(12,LOW);delay(25);
    // digitalWrite(17,HIGH);delay(25);
    // digitalWrite(17,LOW);delay(25);

    // digitalWrite(17,HIGH);delay(25);
    // digitalWrite(17,LOW);delay(25);
    // digitalWrite(12,HIGH);delay(25);
    // digitalWrite(12,LOW);delay(25);
    // digitalWrite(37,HIGH);delay(25);
    // digitalWrite(37,LOW);delay(25);
    // digitalWrite(16,HIGH);delay(25);
    // digitalWrite(16,LOW);delay(25);
    // digitalWrite(11,HIGH);delay(25);
    // digitalWrite(11,LOW);delay(25);
    // digitalWrite(36,HIGH);delay(25);
    // digitalWrite(36,LOW);delay(25);
    // digitalWrite(15,HIGH);delay(25);
    // digitalWrite(15,LOW);delay(25);
    // digitalWrite(10,HIGH);delay(25);
    // digitalWrite(10,LOW);delay(25);
    // digitalWrite(35,HIGH);delay(25);
    // digitalWrite(35,LOW);delay(25);
    // digitalWrite(14,HIGH);delay(25);
    // digitalWrite(14,LOW);delay(25);
    // digitalWrite(21,HIGH);delay(25);
    // digitalWrite(21,LOW);delay(25);
    // digitalWrite(6,HIGH);delay(25);
    // digitalWrite(6,LOW);delay(25);

    // digitalWrite(3,HIGH);delay(25);
    // digitalWrite(34,HIGH);delay(25);
    // digitalWrite(4,HIGH);delay(25);
    // digitalWrite(33,HIGH);delay(25);
    // digitalWrite(5,HIGH);delay(25);
    // digitalWrite(26,HIGH);delay(1000);
    // digitalWrite(26,LOW);delay(25);
    // digitalWrite(5,LOW);delay(25);
    // digitalWrite(33,LOW);delay(25);
    // digitalWrite(4,LOW);delay(25);
    // digitalWrite(34,LOW);delay(25);
    // digitalWrite(3,LOW);delay(25);

    // digitalWrite(6,HIGH);delay(25);
    // digitalWrite(21,HIGH);delay(25);
    // digitalWrite(14,HIGH);delay(25);
    // digitalWrite(35,HIGH);delay(25);
    // digitalWrite(10,HIGH);delay(25);
    // digitalWrite(15,HIGH);delay(25);
    // digitalWrite(36,HIGH);delay(25);
    // digitalWrite(11,HIGH);delay(25);
    // digitalWrite(16,HIGH);delay(25);
    // digitalWrite(37,HIGH);delay(25);
    // digitalWrite(12,HIGH);delay(25);
    // digitalWrite(17,HIGH);delay(1000);
    // digitalWrite(17,LOW);delay(25);
    // digitalWrite(12,LOW);delay(25);
    // digitalWrite(37,LOW);delay(25);
    // digitalWrite(16,LOW);delay(25);
    // digitalWrite(11,LOW);delay(25);
    // digitalWrite(36,LOW);delay(25);
    // digitalWrite(15,LOW);delay(25);
    // digitalWrite(10,LOW);delay(25);
    // digitalWrite(35,LOW);delay(25);
    // digitalWrite(14,LOW);delay(25);
    // digitalWrite(21,LOW);delay(25);
    // digitalWrite(6,LOW);delay(25);
}

void updateNumber(int lastNumber, int currentNumber) {
  turnOffNumber(lastNumber);
  turnOnNumber(currentNumber);
}

bool hasInputChanged() {
    readEncoder();
    if (lastNumber != currentNumber) return true;
    return false;
}

// TODO see about using interupts for detecting when the input changes
void inputMode(bool hasInputChanged) {
    if (currentState == INPUT_MODE && previousState == BLING_MODE) {
      Serial.println("doing input mode stuffz");
    }
    // currently handles spinning the encoder knob and updating the numbers
    // needs to also "save" off the number when they press the button
    if (hasInputChanged) {
        updateNumber(lastNumber, currentNumber);
    }  
}

IRAM_ATTR void checkPosition() {
  encoder.tick(); // just call tick() to check the state.
}

void setup() {
  Serial.begin(115200);
  while (! Serial);
  encoder.setPosition(0 / ROTARYSTEPS); 
  pullDownAllPins();
  turnOffAllLights();
  
  // register interrupt routine
  attachInterrupt(digitalPinToInterrupt(PIN_IN1), checkPosition, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_IN2), checkPosition, CHANGE);
}

int numIntervalsWithoutInput = 0;
bool hasInputChangedDuringInterval = false;

void loop() {
    previousState = currentState;
    currentTime = millis();

    encoder.tick();
    bool inputChanged = hasInputChanged();

    if (inputChanged) { 
      hasInputChangedDuringInterval = true;
    }

    // TODO move into a timer instead of doing it in the main loop
    if (currentTime - previousTime >= INTERVAL) {
      previousTime = currentTime;

      if (hasInputChangedDuringInterval) {
        hasInputChangedDuringInterval = false;
        numIntervalsWithoutInput = 0;
      } else {
        numIntervalsWithoutInput += 1;
      }
    }

    if (numIntervalsWithoutInput >= BLING_MODE_TIMEOUT_INTERVAL) {
      currentState = BLING_MODE;
    } else {
      currentState = INPUT_MODE;
    }

    if (DEBUG && previousState != currentState) {
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

    //ghetto state machine
    switch(currentState) {
      case BLING_MODE:
        blingMode();
        break;
      case INPUT_MODE:
        inputMode(inputChanged);
        break;
      default:
        inputMode(inputChanged);
    }
  
} 
