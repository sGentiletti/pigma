#include <EEPROM.h>

#include "Display.h"
#include "Encoder.h"
#include "Sequence.h"

volatile int actualPosition = 0;
int previousPosition = 0;
int selectPosition = 0;

volatile int addressMemory = 0;  // Address EEPROM
volatile int error;

boolean next = false;


void setup() {
  Serial.begin(9600);
  initDisplay();
  initEncoder();
  error = EEPROM.read(addressMemory);
  initSequence();
}

void loop() {
  delay(500);  // Smooth init

  if (error != 0) {
    switch (error) {
      case 1:
        Serial.println("Error 1");
        break;
      case 2:
        Serial.println("Error 2");
        break;
      case 3:
        Serial.println("Error 3");
        break;
      default:
        Serial.println("Error Desconocido");
    }

    while (error != 0) {
      if (getButtonStatus()) {
        Serial.println("Reiniciando...");
        EEPROM.write(addressMemory, 0);
        error = EEPROM.read(addressMemory);
        delay(5000);
      }
    }
  }

  pigmaText();

  while (!next) {
    if (getButtonStatus()) {
      delay(500);  // Previene lecturas erroneas
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
      delay(500);  // Previene lecturas erroneas
      selectPosition = actualPosition;
      next = true;
    }
  }

  for (int i = 1; selectPosition >= i; i++) {
    sequence();
  }

  finishText();
  delay(5000);

  next = false;
  actualPosition = 0;
  previousPosition = 0;
}
