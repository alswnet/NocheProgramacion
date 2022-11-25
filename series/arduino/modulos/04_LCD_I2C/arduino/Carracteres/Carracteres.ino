#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);


#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif

uint8_t corazon[8] = {
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
  lcd.init();
  lcd.backlight();
  lcd.createChar(13, corazon);

  lcd.setCursor(3, 0);
  lcd.print("YO ");
  lcd.printByte(13);
  lcd.print(" Lila!");
  lcd.blink();

}

void loop() {

}
