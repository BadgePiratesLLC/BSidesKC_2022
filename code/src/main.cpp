#include <Arduino.h>
#include <RotaryEncoder.h>

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

// Example for Arduino UNO with input signals on pin 2 and 3
#define PIN_IN1 13
#define PIN_IN2 38


#define ROTARYSTEPS 1
#define ROTARYMIN 0
#define ROTARYMAX 11

// Setup a RotaryEncoder with 4 steps per latch for the 2 signal input pins:
// RotaryEncoder encoder(PIN_IN1, PIN_IN2, RotaryEncoder::LatchMode::FOUR3);

// Setup a RotaryEncoder with 2 steps per latch for the 2 signal input pins:
RotaryEncoder encoder(PIN_IN1, PIN_IN2, RotaryEncoder::LatchMode::TWO03);

// Last known rotary position.
int lastPos = -1;

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

void turnOnNumber(int numeral) {
    turnOffAllLights();

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


void setup()
{
  Serial.begin(115200);
  while (! Serial);
  Serial.println("LimitedRotator example for the RotaryEncoder library.");
  encoder.setPosition(0 / ROTARYSTEPS); 


  // Setup LEDS
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

  turnOffAllLights();
}
static int pos = 0;
static int dir = 0;
static int currentNumber = 0;

static bool DEBUG=false;
// Read the current position of the encoder and print out when changed.
void loop()
{
  encoder.tick();
  
  int newPos = encoder.getPosition();
  int newDir = (int)(encoder.getDirection()) * -1;

  currentNumber += newDir;

  if (currentNumber > ROTARYMAX) {
    currentNumber = ROTARYMIN;
  } else if (currentNumber < ROTARYMIN) {
    currentNumber = ROTARYMAX;
  }

  turnOffAllLights();
  turnOnNumber(currentNumber);

  if (DEBUG && pos != newPos) {
    Serial.print("pos:");
    Serial.print(newPos);
    Serial.print(" dir:");
    Serial.println(newDir);
    pos = newPos;
  }
} 
