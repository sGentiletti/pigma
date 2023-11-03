#include <Wire.h>               // libreria de comunicacion por I2C
#include <LCD.h>                // libreria para funciones de LCD
#include <LiquidCrystal_I2C.h>  // libreria para LCD por I2C

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7);  // DIR, E, RW, RS, D4, D5, D6, D7

int LCD = 3;

byte corazon[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};

void initDisplay() {
  lcd.setBacklightPin(LCD, POSITIVE);  // puerto P3 de PCF8574 como positivo
  lcd.setBacklight(HIGH);                  // habilita iluminacion posterior de LCD
  lcd.begin(16, 2);                        // 16 columnas por 2 lineas para LCD 1602A
  lcd.createChar(0, corazon);
  lcd.clear();
}

void pigmaText() {
  String pigma = "";
  pigma += (char)0;
  pigma += " PIGMA ";
  pigma += (char)0;

  lcd.setCursor(2, 0);
  lcd.print(pigma);
  lcd.setCursor(5, 1);
  lcd.print(pigma);
}

void encoderText() {
  lcd.clear();
  lcd.print("Gira y seleciona la cantidad de ciclos");
  lcd.setCursor(0, 1);
  lcd.print("un ciclo");
}

void oneCycleText() {
  lcd.clear();
  lcd.print("Ciclo 1");
}

void twoCycleText() {
  lcd.clear();
  lcd.print("Ciclo 2");
}

void threeCycleText() {
  lcd.clear();
  lcd.print("Ciclo 3");
}

void finishText() {
  lcd.clear();
  lcd.print("Proceso finalizado");
}
