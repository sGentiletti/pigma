int BUTTON = 2;
int CW = 3;
int CCW = 4;

void initEncoder() {
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(CW, INPUT);
  pinMode(CCW, INPUT);
}

boolean getButtonStatus() {
  return digitalRead(BUTTON) == LOW;
}

void enableEncoderInterruption() {
  attachInterrupt(digitalPinToInterrupt(CW), encoder, LOW);
}

void disableEncoderInterruption() {
  detachInterrupt(digitalPinToInterrupt(CW));
}

void encoder() {
  static unsigned long lastInterruption = 0;  // Esta variable se instancia una unica vez
  unsigned long interruptionTime = millis();

  if (interruptionTime - lastInterruption > 5) {  // Previene lecturas erroneas del encoder
    if (digitalRead(CCW) == HIGH) {
      actualPosition++;
    } else {
      actualPosition--;
    }
    actualPosition = min(3, max(1, actualPosition));
    lastInterruption = interruptionTime;
  }
}