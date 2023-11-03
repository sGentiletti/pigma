int BLOWER = 8;

void initBlower() {
  pinMode(BLOWER, OUTPUT);
  stopBlower();
}

void startBlower() {
  digitalWrite(BLOWER, LOW);
}

void stopBlower() {
  digitalWrite(BLOWER, HIGH);
}
