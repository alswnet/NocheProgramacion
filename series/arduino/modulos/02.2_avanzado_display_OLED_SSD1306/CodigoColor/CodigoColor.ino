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

  //Borrar Pantalla
  pantalla.clearDisplay();
  delay(2000);

  // Cuadrado Base
  pantalla.fillRect(20, 30, 100, 10, WHITE);
  pantalla.display();
  delay(2000);

  // Circulo Blanco
  pantalla.fillCircle(40, 30, 10, WHITE);
  pantalla.display();
  delay(2000);

  // Circulo Negro
  pantalla.fillCircle(70, 30, 10, BLACK);
  pantalla.display();
  delay(2000);

  // Circulo Invertido
  pantalla.fillCircle(100, 30, 10, INVERSE);
  pantalla.display();
  delay(2000);
}
