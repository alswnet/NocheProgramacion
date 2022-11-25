#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif

LiquidCrystal_I2C lcd(0x27, 16, 2);
uint8_t i = 0;

void setup() {
  lcd.init();
  lcd.backlight();
}


void loop() {
  lcd.clear();
  lcd.print("Codigo 0x"); lcd.print(i, HEX);
  lcd.print("-0x"); lcd.print(i + 16, HEX);
  lcd.setCursor(0, 1);
  for (int j = 0; j < 16; j++) {
    lcd.printByte(i + j);
  }
  i += 16;

  delay(4000);
}
