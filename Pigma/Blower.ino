int BLOWER_PIN = 8;

void initBlower() {
  pinMode(BLOWER_PIN, OUTPUT);
  stopBlower();
}

void startBlower() {
  digitalWrite(BLOWER_PIN, LOW);
}

void stopBlower() {
  digitalWrite(BLOWER_PIN, HIGH);
}
