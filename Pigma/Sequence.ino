#define MAX_TEMPERATURE 79
#define MIN_TEMPERATURE 35

#define WAIT_FOR_HEAT_TIME 10  // In seconds
#define PRE_HEAT_TIME 60       // In seconds
#define HEAT_TIME 900          // In seconds
#define WAIT_FOR_BLOW_TIME 15  // In seconds
#define COLD_SYSTEM_TIME 120   // In seconds
#define SEQUENCE_TIME WAIT_FOR_HEAT_TIME + PRE_HEAT_TIME + HEAT_TIME + WAIT_FOR_BLOW_TIME + COLD_SYSTEM_TIME

int temperature = getTemperature();
boolean senseMaxTemp = false;
boolean senseMinTemp = false;

void sequence() {
  preHeatText();
  startBlower();
  updateDisplay(WAIT_FOR_HEAT_TIME);  // Wait until start heating
  startHeater();
  senseMaxTemp = true;
  updateDisplay(PRE_HEAT_TIME);  // Pre-heating time
  dissectText();
  senseMinTemp = true;
  enableAbortInterruption();
  updateDisplay(HEAT_TIME);  // Heating time
  stopHeater();
  delay(500);
  disableAbortInterruption();
  senseMinTemp = false;
  senseMaxTemp = false;
  coldSystemText();
  updateDisplay(WAIT_FOR_BLOW_TIME);  // Wait until stop blown
  stopBlower();
  delay(500);
  updateDisplay(COLD_SYSTEM_TIME);  // Wait for cold the system
}

void (*resetSoftware)(void) = 0;

int getSequenceTime() {
  return SEQUENCE_TIME;
}

void abortSequence() {
  stopBlower();
  stopHeater();
  delay(500);
  resetSoftware();
}

void abortSequenceDueToOverheating() {
  EEPROM.write(MEMORY_ADRESS, 1);
  abortSequence();
}

void abortSequenceDueToResistanceIssue() {
  EEPROM.write(MEMORY_ADRESS, 2);
  abortSequence();
}

void updateDisplay(int time) {
  for (int i = 0; i < time; i++) {

    if (i % 2 == 0) {
      temperature = getTemperature();

      if (temperature <= 15 || isnan(temperature)) {
        resetTemperature();
      }

      temperatureText(temperature);

      if (senseMaxTemp && temperature >= MAX_TEMPERATURE) {  // Sensar max temp
        abortSequenceDueToOverheating();
      }

      if (senseMinTemp && temperature < MIN_TEMPERATURE) {  // Sensar min temp
        abortSequenceDueToResistanceIssue();
      }
    }

    timeText(totalSequencesTime);

    delay(1000);

    totalSequencesTime--;
  }
}
