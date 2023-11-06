#include <EEPROM.h>
#include "Display.h"
#include "Encoder.h"
#include "Sequence.h"

#define MEMORY_ADRESS 0  // EEPROM Address

volatile int actualPosition;

int error;
int previousPosition;
int selectPosition;
int totalSequencesTime;
boolean next;

void setup() {
  initDisplay();
  initEncoder();
  initSequence();

  error = EEPROM.read(MEMORY_ADRESS);
  actualPosition = 0;
  previousPosition = 0;
  selectPosition = 0;
  next = false;
}

void loop() {
  delay(500);  // Smooth init

  if (error != 0) {
    switch (error) {
      case 1:
        overheatingText();
        break;
      case 2:
        resistanceIssueText();
        break;
      default:
        errorGenericText();
    }

    while (error != 0) {
      if (getButtonStatus()) {
        restartText();
        EEPROM.write(MEMORY_ADRESS, 0);
        error = 0;
        delay(3000);
      }
    }
  }

  pigmaText();

  while (!next) {
    if (getButtonStatus()) {
      selectPosition = actualPosition;
      next = true;
    }
  }

  next = false;

  encoderText();

  while (!next) {
    enableEncoderInterruption();

    if (actualPosition != previousPosition) {
      previousPosition = actualPosition;
      switch (actualPosition) {
        case 1:
          oneCycleText();
          break;
        case 2:
          twoCycleText();
          break;
        case 3:
          threeCycleText();
          break;
        default:
          encoderText();
      }
    }

    if (actualPosition != 0 && getButtonStatus()) {
      disableEncoderInterruption();
      selectPosition = actualPosition;
      next = true;
    }
  }

  totalSequencesTime = getSequenceTime() * selectPosition;

  for (int i = 0; selectPosition > i; i++) {
    sequence();
  }

  updateDisplay(1);

  finishText();

  delay(3000);

  next = false;
  actualPosition = 0;
  previousPosition = 0;
}
