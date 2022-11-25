#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.backlight();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Tiempo");
  lcd.setCursor(0, 1);
  lcd.print("Encendido:");
}

void loop() {

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Tiempo");
  lcd.setCursor(0, 1);
  lcd.print("Encendido:");
  lcd.setCursor(11, 1);
  lcd.print(millis() / 1000);
  lcd.print("s");
  delay(20);
}
