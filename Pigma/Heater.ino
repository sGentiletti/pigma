int HEATER = 9;

void initHeater() {
  pinMode(HEATER, OUTPUT);
  stopHeater();
}

void startHeater() {
  digitalWrite(HEATER, LOW);
}

void stopHeater() {
  digitalWrite(HEATER, HIGH);
}
