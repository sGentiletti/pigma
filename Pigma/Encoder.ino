#define BUTTON_PIN 2
#define CW_PIN 3
#define CCW_PIN 4

void initEncoder() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(CW_PIN, INPUT);
  pinMode(CCW_PIN, INPUT);
}

boolean getButtonStatus() {
  return digitalRead(BUTTON_PIN) == LOW;
}

void enableEncoderInterruption() {
  attachInterrupt(digitalPinToInterrupt(CW_PIN), encoder, LOW);
}

void disableEncoderInterruption() {
  detachInterrupt(digitalPinToInterrupt(CW_PIN));
}

void enableAbortInterruption() {
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), abort, LOW);
}

void disableAbortInterruption() {
  detachInterrupt(digitalPinToInterrupt(BUTTON_PIN));
}

void encoder() {
  static unsigned long lastInterruption = 0;  // Esta variable se instancia una unica vez
  unsigned long interruptionTime = millis();

  if (interruptionTime - lastInterruption > 10) {  // Previene lecturas erroneas del encoder
    if (digitalRead(CCW_PIN) == HIGH) {
      actualPosition++;
    } else {
      actualPosition--;
    }
    actualPosition = min(3, max(1, actualPosition));
    lastInterruption = interruptionTime;
  }
}

void abort() {
  abortSequence();
}
