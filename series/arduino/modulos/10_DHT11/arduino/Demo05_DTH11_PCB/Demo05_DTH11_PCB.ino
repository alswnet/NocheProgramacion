#include "DHT.h"
#define PinSensor 2
#define Tipo DHT11  // Tipo de sensor Opciones DHT11, DHT22, DHT21
// DHT11 - Temperatura 0 a 50 c +- 2c      Humedad  20 a 90% +- 4%
// DTH22 - Temperatura -40 a 80 c +- 0.5c  Humedad  0 a 100% +- 2%

DHT dht(PinSensor, Tipo);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  delay(5000);  // Mínimo 2000
  float humedad = dht.readHumidity();
  float temperatura = dht.readTemperature();

  if (isnan(temperatura) || isnan(humedad)) {
    Serial.println("Error leyendo el sensor DHT");
    return;
  }

  float sensacionTermica = dht.computeHeatIndex(temperatura, humedad, false);

  Serial.print("Humedad: ");
  Serial.print(humedad);
  Serial.println(" %");
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" *C");
  Serial.print("Sensacion Termica: ");
  Serial.print(sensacionTermica);
  Serial.println(" *C");
}