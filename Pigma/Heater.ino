#define HEATER_PIN 9

void initHeater() {
  pinMode(HEATER_PIN, OUTPUT);
  stopHeater();
}

void startHeater() {
  digitalWrite(HEATER_PIN, LOW);
}

void stopHeater() {
  digitalWrite(HEATER_PIN, HIGH);
}
