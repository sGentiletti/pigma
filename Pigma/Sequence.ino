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
  timeText(totalTime);
  temperatureText(getTemperature());
  startBlower();
  for (int i = 0; i < WAIT_FOR_HEAT_TIME; i++) {  // Wait until start heating
    delay(1000);
    totalTime--;
    timeText(totalTime);
    temperatureText(getTemperature());
  }
  startHeater();
  dissectText();
  for (int i = 0; i < PRE_HEAT_TIME; i++) {  // Pre-heating time
    delay(1000);
    timeText(totalTime);
    totalTime--;
    temperatureText(getTemperature());
  }
  isHeatingOn = true;
  for (int i = 0; i < HEAT_TIME; i++) {  // Heating time
    delay(1000);
    totalTime--;
    timeText(totalTime);
    temperatureText(getTemperature());
  }
  stopHeater();
  isHeatingOn = false;
  coldSystemText();
  for (int i = 0; i < WAIT_FOR_BLOW_TIME; i++) {  // Wait until stop blown
    delay(1000);
    totalTime--;
    timeText(totalTime);
    temperatureText(getTemperature());
  }
  stopBlower();
  for (int i = 0; i < COLD_SYSTEM_TIME; i++) {  // Wait for cold the system
    delay(1000);
    totalTime--;
    timeText(totalTime);
    temperatureText(getTemperature());
  }
}

void (*resetSoftware)(void) = 0;

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
