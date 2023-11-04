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
  totalTime = WAIT_FOR_HEAT_TIME + PRE_HEAT_TIME + HEAT_TIME + WAIT_FOR_BLOW_TIME + COLD_SYSTEM_TIME;
}

void sequence() {
  preHeatText();
  startBlower();
  for (int i = 0; i < WAIT_FOR_HEAT_TIME; i++) {  // Wait until start heating
    updateDisplay();
  }
  startHeater();
  dissectText();
  for (int i = 0; i < PRE_HEAT_TIME; i++) {  // Pre-heating time
    updateDisplay();
  }
  isHeatingOn = true;
  for (int i = 0; i < HEAT_TIME; i++) {  // Heating time
    updateDisplay();
  }
  stopHeater();
  isHeatingOn = false;
  coldSystemText();
  for (int i = 0; i < WAIT_FOR_BLOW_TIME; i++) {  // Wait until stop blown
    updateDisplay();
  }
  stopBlower();
  for (int i = 0; i < COLD_SYSTEM_TIME; i++) {  // Wait for cold the system
    updateDisplay();
  }
}

void (*resetSoftware)(void) = 0;

void updateDisplay() {
  timeText(totalTime);
  temperatureText(getTemperature());
  delay(1000);
  totalTime--;
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
