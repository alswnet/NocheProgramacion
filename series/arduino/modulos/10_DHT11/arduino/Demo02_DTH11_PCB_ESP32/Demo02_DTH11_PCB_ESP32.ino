#include "DHT.h"
#define PinSensor 4
#define Tipo DHT11  // Tipo de sensor Opciones DHT11, DHT22, DHT21
// DHT11 - Temperatura 0 a 50 c +- 2c      Humedad  20 a 90% +- 4%
// DTH22 - Temperatura -40 a 80 c +- 0.5c  Humedad  0 a 100% +- 2%

DHT dht(PinSensor, Tipo);

void setup() {
  Serial.begin(115200);
  dht.begin();
}

void loop() {
  delay(5000);  // Mínimo 2000
  float humedad = dht.readHumidity();
  float temperatura = dht.readTemperature();
  Serial.print("Humedad: ");
  Serial.print(humedad);
  Serial.println(" %");
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" *C");
}