#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define Ancho_Pantalla 128
#define Alto_Pantalla 64
#define Direccion_Pantalla 0x3C
#define Reset_Pantalla -1

Adafruit_SSD1306 pantalla(Ancho_Pantalla, Alto_Pantalla, &Wire, Reset_Pantalla);

void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando la pantalla");

  if (!pantalla.begin(SSD1306_SWITCHCAPVCC, Direccion_Pantalla)) {
    Serial.println(F("Error en pantalla OLED"));
    for (;;);
  }


}

void loop() {

  pantalla.setTextColor(WHITE);
  //
  //  pantalla.clearDisplay();
  //  pantalla.setTextSize(1);
  //  pantalla.setCursor(0, 0);
  //  pantalla.println("Subcribete ChepeCarlos");
  //  pantalla.display();
  //  delay(2000);
  //
  //  pantalla.clearDisplay();
  //  pantalla.setTextSize(2);
  //  pantalla.setCursor(0, 0);
  //  pantalla.println("Subcribete ChepeCarlos");
  //  pantalla.display();
  //  delay(2000);
  //

//  pantalla.clearDisplay();
//  pantalla.setTextSize(1);
//  pantalla.setCursor(0, 0);
//  pantalla.print("Jos");
//  pantalla.write(130);
//  pantalla.print(" llega ma");
//  pantalla.write(164);
//  pantalla.print("ana");
//  pantalla.display();
//  delay(2000);

//    pantalla.clearDisplay();
//    pantalla.setTextSize(3);
//    pantalla.setCursor(0, 0);
//    pantalla.write(173);
//    pantalla.print("YA! ");
//    pantalla.write(3);
//    pantalla.display();
//    delay(2000);
  
    pantalla.clearDisplay();
  
    pantalla.setTextSize(1);
    pantalla.setTextColor(SSD1306_WHITE);
    pantalla.setCursor(0, 0);
    pantalla.cp437(true);
  
    for (int16_t i = 0; i < 256; i++) {
      if (i == '\n') pantalla.write(' ');
      else          pantalla.write(i);
    }
  
    pantalla.display();
    delay(2000);

}
