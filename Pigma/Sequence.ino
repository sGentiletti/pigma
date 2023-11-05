#include "Temperature.h"
#include "Blower.h"
#include "Heater.h"

#define WAIT_FOR_HEAT_TIME 15  // In seconds
#define PRE_HEAT_TIME 15       // In seconds
#define HEAT_TIME 1200         // In seconds
#define WAIT_FOR_BLOW_TIME 15  // In seconds
#define COLD_SYSTEM_TIME 120   // In seconds
#define SEQUENCE_TIME WAIT_FOR_HEAT_TIME + PRE_HEAT_TIME + HEAT_TIME + WAIT_FOR_BLOW_TIME + COLD_SYSTEM_TIME

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

void updateDisplay(int time) {
  for (int i = 0; i < time; i++) {
    timeText(totalSequencesTime);
    temperatureText(getTemperature());
    delay(1000);
    totalSequencesTime--;
  }
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
