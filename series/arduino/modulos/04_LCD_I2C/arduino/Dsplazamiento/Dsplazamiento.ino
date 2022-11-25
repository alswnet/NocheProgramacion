#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("www.NocheProgramacion.com");
  lcd.setCursor(0, 1);
  lcd.print("Tutoriales, codigo, diagramas y muchos");
}

void loop() {
  lcd.scrollDisplayRight();
  //  lcd.scrollDisplayLeft();
  delay(500);
}
