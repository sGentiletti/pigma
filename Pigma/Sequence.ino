#include "Temperature.h"
#include "Blower.h"
#include "Heater.h"

#define MAX_TEMPERATURE 80
#define MIN_TEMPERATURE 20

#define WAIT_FOR_HEAT_TIME 5  // In seconds
#define PRE_HEAT_TIME 5       // In seconds
#define HEAT_TIME 15          // In seconds
#define WAIT_FOR_BLOW_TIME 5  // In seconds
#define COLD_SYSTEM_TIME 5    // In seconds
#define SEQUENCE_TIME WAIT_FOR_HEAT_TIME + PRE_HEAT_TIME + HEAT_TIME + WAIT_FOR_BLOW_TIME + COLD_SYSTEM_TIME

int temperature;
boolean isHeatingOn = false;

void initSequence() {
  initTemperature();
  initBlower();
  initHeater();
}

void sequence() {
  preHeatText();
  startBlower();
  updateDisplay(WAIT_FOR_HEAT_TIME);  // Wait until start heating
  startHeater();
  updateDisplay(PRE_HEAT_TIME);  // Pre-heating time
  dissectText();
  isHeatingOn = true;
  updateDisplay(HEAT_TIME);  // Heating time
  stopHeater();
  isHeatingOn = false;
  coldSystemText();
  updateDisplay(WAIT_FOR_BLOW_TIME);  // Wait until stop blown
  stopBlower();
  updateDisplay(COLD_SYSTEM_TIME);  // Wait for cold the system
}

void (*resetSoftware)(void) = 0;

int getSequenceTime() {
  return SEQUENCE_TIME;
}

void abortSequence() {
  stopBlower();
  stopHeater();
}

void abortSequenceDueToOverheating() {
  abortSequence();
  EEPROM.write(memoryAddress, 1);
  resetSoftware();
}

void abortSequenceDueToResistanceIssue() {
  abortSequence();
  EEPROM.write(memoryAddress, 2);
  resetSoftware();
}

void updateDisplay(int time) {
  for (int i = 0; i < time; i++) {
    temperature = getTemperature();

    timeText(totalSequencesTime);
    temperatureText(temperature);

    if (isHeatingOn) {          // Resistencia prendida
      if (getButtonStatus()) {  // Cancelar proceso al tocar el pulsador
        abortSequence();
        resetSoftware();
      }
      if (temperature >= MAX_TEMPERATURE) {
        abortSequenceDueToOverheating();
      }
      if (temperature < MIN_TEMPERATURE) {
        abortSequenceDueToResistanceIssue();
      }
    }

    delay(1000);

    totalSequencesTime--;
  }
}
