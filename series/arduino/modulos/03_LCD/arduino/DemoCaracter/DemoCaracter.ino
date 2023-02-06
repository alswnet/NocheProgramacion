#include <LiquidCrystal.h>

const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

byte corazon[8] = {
  B00000,
  B01010,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000,
  B00000
};

void setup() {
  lcd.begin(20, 4);

  lcd.createChar(0, corazon);

  lcd.setCursor(0, 0);
  lcd.print("Yo ");
  lcd.write(byte(0));
  lcd.print(" Arduino!");

}

void loop() {

}
