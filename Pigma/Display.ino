#include <Wire.h>               // libreria de comunicacion por I2C
#include <LCD.h>                // libreria para funciones de LCD
#include <LiquidCrystal_I2C.h>  // libreria para LCD por I2C

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7);  // DIR, E, RW, RS, D4, D5, D6, D7

byte heart[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};

byte arrowUp[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00100,
  0b01110,
  0b11111,
  0b00000,
  0b00000
};

byte arrowRight[8] = {
  0b00000,
  0b00100,
  0b00110,
  0b00111,
  0b00110,
  0b00100,
  0b00000,
  0b00000
};

void initDisplay() {
  lcd.setBacklightPin(3, POSITIVE);  // puerto P3 de PCF8574 como positivo
  lcd.setBacklight(HIGH);            // habilita iluminacion posterior de LCD
  lcd.begin(16, 2);                  // 16 columnas por 2 lineas para LCD 1602A
  lcd.createChar(0, heart);
  lcd.createChar(1, arrowUp);
  lcd.createChar(2, arrowRight);
  lcd.clear();
}

void pigmaText() {
  String pigma = "";
  pigma += (char)0;
  pigma += " PIGMA ";
  pigma += (char)0;

  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print(pigma);
  lcd.setCursor(6, 1);
  lcd.print(pigma);
}

void grateText() {
  lcd.clear();
  lcd.print("Rallar material");
  lcd.setCursor(0, 1);
  lcd.print("y asegurar");
  lcd.setCursor(15, 1);
  String arrow = "";
  arrow += (char)2;
  lcd.print(arrow);
}

void encoderText() {
  lcd.clear();
  lcd.print("Selecciona cant.");
  lcd.setCursor(0, 1);
  lcd.print("de ciclos");
  lcd.setCursor(15, 1);
  String arrow = "";
  arrow += (char)2;
  lcd.print(arrow);
}

void oneCycleText() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  1    2    3");
  lcd.setCursor(2, 1);
  lcd.print((char)1);
}

void twoCycleText() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  1    2    3");
  lcd.setCursor(7, 1);
  lcd.print((char)1);
}

void threeCycleText() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  1    2    3");
  lcd.setCursor(12, 1);
  lcd.print((char)1);
}

void overheatingText() {
  lcd.clear();
  lcd.print("TEMPERATURA ALTA");
  lcd.setCursor(0, 1);
  lcd.print("Reiniciar");
  lcd.setCursor(15, 1);
  String arrow = "";
  arrow += (char)2;
  lcd.print(arrow);
}

void resistanceIssueText() {
  lcd.clear();
  lcd.print("TEMPERATURA BAJA");
  lcd.setCursor(0, 1);
  lcd.print("Reiniciar");
  lcd.setCursor(15, 1);
  String arrow = "";
  arrow += (char)2;
  lcd.print(arrow);
}

void errorGenericText() {
  lcd.clear();
  lcd.print("Error");
  lcd.setCursor(0, 1);
  lcd.print("desconocido");
}

void restartText() {
  lcd.clear();
  lcd.print("Reiniciando...");
}

void preHeatText() {
  lcd.clear();
  lcd.print("Calentando...");
}

void dissectText() {
  lcd.setCursor(0, 0);
  lcd.print("Secando...   ");
}

void coldSystemText() {
  lcd.setCursor(0, 0);
  lcd.print("Enfriando... ");
}

void finishText() {
  lcd.clear();
  lcd.print("Proceso");
  lcd.setCursor(0, 1);
  lcd.print("finalizado");
  lcd.setCursor(15, 1);
  String arrow = "";
  arrow += (char)2;
  lcd.print(arrow);
}

void temperatureText(int temp) {
  lcd.setCursor(0, 1);

  String text = "T: ";
  text += temp;

  lcd.print(text);
}

void timeText(int totalTime) {
  int hours = totalTime / 3600;
  int minutes = (totalTime % 3600) / 60;
  int seconds = totalTime % 60;

  char formattedTime[9];
  sprintf(formattedTime, "%02d:%02d:%02d", hours, minutes, seconds);

  lcd.setCursor(8, 1);
  lcd.print(formattedTime);
}
