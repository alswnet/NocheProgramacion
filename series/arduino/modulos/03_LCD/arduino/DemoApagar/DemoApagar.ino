#include <LiquidCrystal.h>

const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(16, 2);
  lcd.print("Dale, Like!");
}

void loop() {
  lcd.noDisplay();
  delay(1000);
  lcd.display();
  delay(1000);
}
