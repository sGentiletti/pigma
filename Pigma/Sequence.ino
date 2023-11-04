#include "Temperature.h"
#include "Blower.h"
#include "Heater.h"

volatile boolean isHeatingOn = false;

int WAIT_FOR_HEAT_TIME = 5;  // In seconds
int PRE_HEAT_TIME = 5;       // In seconds
int HEAT_TIME = 15;          // In seconds
int WAIT_FOR_BLOW_TIME = 5;  // In seconds
int COLD_SYSTEM_TIME = 5;    // In seconds

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
  dissectText();
  updateDisplay(PRE_HEAT_TIME);  // Pre-heating time
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

void initTotalTime() {
  totalTime = WAIT_FOR_HEAT_TIME + PRE_HEAT_TIME + HEAT_TIME + WAIT_FOR_BLOW_TIME + COLD_SYSTEM_TIME;
}

void updateDisplay(int time) {
  for (int i = 0; i < time; i++) {
    timeText(totalTime);
    temperatureText(getTemperature());
    delay(1000);
    totalTime--;
  }
}

void abortSequence() {
  stopBlower();
  stopHeater();
}

void abortSequenceDueToOverheating() {
  abortSequence();
  EEPROM.write(addressMemory, 1);
  resetSoftware();
}

void abortSequenceDueToResistanceIssue() {
  abortSequence();
  EEPROM.write(addressMemory, 2);
  resetSoftware();
}
