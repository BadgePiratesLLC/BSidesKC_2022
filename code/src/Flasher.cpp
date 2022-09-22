#include <Flasher.hpp>


void Flasher::Update(unsigned long currentMillis){

    switch (selectedBling)
    {
    case 0:
      // check to see if it's time to change the state of the LED
      ledPin = pattern[index][0];
      ledState = pattern[index][1];

      if ((currentMillis - previousMillis >= OffTime))
      {
        digitalWrite(ledPin, ledState); // Update the actual LED
        previousMillis = currentMillis; // Remember the time
        index += 1;                     // update the
        if (index >= PATTERN_1_INDEX_MAX)
        { // reset index after the end of the array
          index = 0;
        }
      }
      break;
    case 1:
      // check to see if it's time to change the state of the LED
      ledPin = inputPattern[index][0];
      ledState = inputPattern[index][1];

      if ((currentMillis - previousMillis >= OffTime))
      {
        digitalWrite(ledPin, ledState); // Update the actual LED
        previousMillis = currentMillis; // Remember the time
        index += 1;                     // update the
        if (index >= PATTERN_2_INDEX_MAX)
        { // reset index after the end of the array
          index = 0;
        }
      }
    }
  }


void Flasher::handleBlingChange()
{
  if (selectedBling >= NUM_BLING - 1)
  {
    selectedBling = 0;
  }
  else
  {
    selectedBling++;
  }
}