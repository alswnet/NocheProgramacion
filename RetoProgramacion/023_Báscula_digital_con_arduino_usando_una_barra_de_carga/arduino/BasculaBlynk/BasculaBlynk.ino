#define BLYNK_PRINT Serial //Para ver el depurador  - se puede quitar
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "HX711.h"

char auth[] = "1f91bc3fa72647818e51ff90e4bc2604";//Contraseña Blynk
char ssid[] = "TURBONETT_ALSW";//Nombre de red
char pass[] = "2526-4897";//Contraseña

#define calibration_factor 96690.0

#define DOUT  5
#define CLK  2

HX711 scale(DOUT, CLK);

int Peso = 0;
WidgetLCD lcd(V1);
void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  scale.set_scale(calibration_factor);
  scale.tare();
}

void loop() {
  Peso =  int(scale.get_units() * 453.592);
  lcd.print(0, 0, "Peso =");
  lcd.print(0, 7, Peso);
  Blynk.run();
}
