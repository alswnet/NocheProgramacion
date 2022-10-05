
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

  pantalla.setTextColor(WHITE);
  pantalla.clearDisplay();
  pantalla.setTextSize(1);
  pantalla.setCursor(0, 0);
  pantalla.println("Subcribete ChepeCarlos, y comparte con tus amigos para hacer crecer el canal");
  pantalla.display();
  delay(2000);
}

void loop() {
  pantalla.startscrollright(0x00, 0x0F);
  delay(2000);
  pantalla.stopscroll();
  delay(1000);
  pantalla.startscrollleft(0x00, 0x0F);
  delay(2000);
  pantalla.stopscroll();
  delay(1000);
  pantalla.startscrolldiagright(0x00, 0x07);
  delay(2000);
  pantalla.startscrolldiagleft(0x00, 0x07);
  delay(2000);
  pantalla.stopscroll();
  delay(1000);

}
