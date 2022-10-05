// Creado ChepeCarlos de ALSW
// Tutorial Completo en https://nocheprogramacion.com
// Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

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
  // Punto
  pantalla.display();
  pantalla.clearDisplay();
  pantalla.drawPixel(Ancho_Pantalla / 2, Alto_Pantalla / 2, WHITE);
  pantalla.display();
  delay(1000);

  // Linea
  pantalla.clearDisplay();
  pantalla.drawLine(0, 0, pantalla.width() - 1, pantalla.height() - 1, WHITE);
  pantalla.display();
  delay(1000);

  // Cuadrado
  pantalla.clearDisplay();
  pantalla.drawRect(20, 20, 30, 30, WHITE);
  pantalla.display();
  delay(1000);

  // Cuadrado Relleno
  pantalla.clearDisplay();
  pantalla.fillRect(20, 20, 30, 30, WHITE);
  pantalla.display();
  delay(1000);

  // Cuadrado Redondeado
  pantalla.clearDisplay();
  pantalla.drawRoundRect(20, 20, 30, 30, 10, WHITE);
  pantalla.display();
  delay(1000);

  // Cuadrado Redondeado Relleno
  pantalla.clearDisplay();
  pantalla.fillRoundRect(20, 20, 30, 30, 10, WHITE);
  pantalla.display();
  delay(1000);

  // Circulo
  pantalla.clearDisplay();
  pantalla.drawCircle(20, 20, 10, WHITE);
  pantalla.display();
  delay(1000);

  // Circulo Relleno
  pantalla.clearDisplay();
  pantalla.fillCircle(20, 20, 10, WHITE);
  pantalla.display();
  delay(1000);

  // Triangulo
  pantalla.clearDisplay();
  pantalla.drawTriangle(20, 20, 20, 50, 50, 50, WHITE);
  pantalla.display();
  delay(1000);

  // Triangulo Relleno
  pantalla.clearDisplay();
  pantalla.fillTriangle(20, 20, 20, 50, 50, 50, WHITE);
  pantalla.display();
  delay(1000);
}

void loop() {

}
