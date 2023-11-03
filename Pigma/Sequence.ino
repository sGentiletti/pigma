#include "Temperature.h"
#include "Blower.h"
#include "Heater.h"

volatile boolean isHeatingOn = false;

int WAIT_FOR_HEAT_TIME = 2;  // In seconds
int PRE_HEAT_TIME = 2;       // In seconds
int HEAT_TIME = 10;          // In seconds
int WAIT_FOR_BLOW_TIME = 2;  // In seconds
int COLD_SYSTEM_TIME = 2;    // In seconds

void initSequence() {
  initTemperature();
  initBlower();
  initHeater();
}

void sequence() {
  startBlower();
  delay(WAIT_FOR_HEAT_TIME * 1000);  // Wait until start heating
  startHeater();
  Serial.println("Calentando...");
  delay(PRE_HEAT_TIME * 1000);  // Pre-heating time
  isHeatingOn = true;
  Serial.println("Disecando...");
  delay(HEAT_TIME * 1000);  // Heating time
  stopHeater();
  isHeatingOn = false;
  Serial.println("Enfriando...");
  delay(WAIT_FOR_BLOW_TIME * 1000);  // Wait until stop blown
  stopBlower();
  delay(COLD_SYSTEM_TIME * 1000);  // Wait for cold the system
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
