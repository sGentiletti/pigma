#define RED_RED 10
#define GREEN_LED 11
#define BLUE_LED 12

void initLed() {
  pinMode(RED_RED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  ledOff();
}

void setColor(int red, int green, int blue) {
  analogWrite(RED_RED, red);
  analogWrite(GREEN_LED, green);
  analogWrite(BLUE_LED, blue);
}

void setLedToRed() {
  setColor(255, 0, 0);
}

void setLedToGreen() {
  setColor(0, 255, 0);
}

void ledOff() {
  setColor(0, 0, 0);
}