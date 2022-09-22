#include "hardware.hpp"

void Hardware::turnOffAllLights()
{
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
  digitalWrite(LED_B, LOW);
  digitalWrite(LED_S1, LOW);
  digitalWrite(LED_I, LOW);
  digitalWrite(LED_D, LOW);
  digitalWrite(LED_E, LOW);
  digitalWrite(LED_S2, LOW);
}

// TODO make a lookup table for the numeral -> LED_X
void Hardware::turnOnNumber(int numeral)
{
  switch (numeral)
  {
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

void Hardware::turnOffNumber(int numeral)
{
  switch (numeral)
  {
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
void Hardware::pullDownAllPins()
{
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
void Hardware::readEncoder(RotaryEncoder encoder, int &currentNumber, int &lastNumber, int &pos)
{
  int newPos = encoder.getPosition();
  int newDir = (int)(encoder.getDirection());
  // my board (pecord) has the encoder wired backwards
  // instead of fixing the solder I "fixed" it in code
  // if its going backwards for you flip that flagoh
  if (INVERT_DIR)
  {
    newDir *= -1;
  }

  // save off the previous number
  lastNumber = currentNumber;
  // get the new number
  currentNumber += newDir;
  if (currentNumber > ROTARYMAX)
  {
    currentNumber = ROTARYMIN;
  }
  else if (currentNumber < ROTARYMIN)
  {
    currentNumber = ROTARYMAX;
  }

  if (pos != newPos)
  {
    pos = newPos;
  }

  if (DEBUG)
  {
    Serial.print("pos:");
    Serial.print(newPos);
    Serial.print(" dir:");
    Serial.println(newDir);
  }
}

void Hardware::updateNumber(int lastNumber, int currentNumber)
{
  turnOffNumber(lastNumber);
  turnOnNumber(currentNumber);
}