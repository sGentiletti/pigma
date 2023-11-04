#include <Wire.h>               // libreria de comunicacion por I2C
#include <LCD.h>                // libreria para funciones de LCD
#include <LiquidCrystal_I2C.h>  // libreria para LCD por I2C

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7);  // DIR, E, RW, RS, D4, D5, D6, D7

int LCD_PIN = 3;

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
  0b00100,
  0b01110,
  0b10101,
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b00000
};

void initDisplay() {
  lcd.setBacklightPin(LCD_PIN, POSITIVE);  // puerto P3 de PCF8574 como positivo
  lcd.setBacklight(HIGH);              // habilita iluminacion posterior de LCD
  lcd.begin(16, 2);                    // 16 columnas por 2 lineas para LCD 1602A
  lcd.createChar(0, heart);
  lcd.createChar(1, arrowUp);
  lcd.clear();
}

void pigmaText() {
  String pigma = "";
  pigma += (char)0;
  pigma += " PIGMA ";
  pigma += (char)0;

  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print(pigma);
  lcd.setCursor(5, 1);
  lcd.print(pigma);
}

void encoderText() {
  lcd.clear();
  lcd.print("Gira y seleciona");
  lcd.setCursor(0, 1);
  lcd.print("cant. de ciclos");
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
  lcd.print("Algo salio mal");
  lcd.setCursor(0, 1);
  lcd.print("excesp temp.  :(");
}

void resistanceIssueText() {
  lcd.clear();
  lcd.print("Temperatura baja");
  lcd.setCursor(0, 1);
  lcd.print("cambiar resist.");
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
  lcd.print("Calentando:");
}

void dissectText() {
  lcd.setCursor(0, 0);
  lcd.print("Disecando: ");
}

void coldSystemText() {
  lcd.setCursor(0, 0);
  lcd.print("Enfriando: ");
}

void finishText() {
  lcd.clear();
  lcd.print("Proceso");
  lcd.setCursor(0, 1);
  lcd.print("finalizado");
}

void temperatureText(int temp) {
  lcd.setCursor(0, 1);

  String text = "T: ";
  text += temp;

  lcd.print(text);
}

void timeText(int totalTime) {
  int minutes = totalTime / 60;
  int seconds = totalTime % 60;

  char formattedTime[6];
  sprintf(formattedTime, "%02d:%02d", minutes, seconds);

  lcd.setCursor(11, 1);
  lcd.print(formattedTime);
}