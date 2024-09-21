#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define PinSensor 2
#define Tipo DHT11  // Tipo de sensor Opciones DHT11, DHT22, DHT21
// DHT11 - Temperatura 0 a 50 c +- 2c      Humedad  20 a 90% +- 4%
// DTH22 - Temperatura -40 a 80 c +- 0.5c  Humedad  0 a 100% +- 2%

DHT_Unified dht(PinSensor, Tipo);

void setup() {
  Serial.begin(9600);
  dht.begin();

  Serial.println(F("Informacion del sensor DHTxx "));

  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.println("Sensor Temperatura");
  Serial.print("Tipo Sensor:  ");
  Serial.println(sensor.name);
  Serial.print("Vercion:      ");
  Serial.println(sensor.version);
  Serial.print("ID :          ");
  Serial.println(sensor.sensor_id);
  Serial.print("Valor Maximo: ");
  Serial.print(sensor.max_value);
  Serial.println("°C");
  Serial.print("Valor Minimo: ");
  Serial.print(sensor.min_value);
  Serial.println("°C");
  Serial.print("Resolucion:   ");
  Serial.print(sensor.resolution);
  Serial.println("°C");
  Serial.println("------------------------------------");
  dht.humidity().getSensor(&sensor);
  Serial.println("Sensor Humdad;");
  Serial.print("Tipo Sensor:  ");
  Serial.println(sensor.name);
  Serial.print("Vercion:      ");
  Serial.println(sensor.version);
  Serial.print("ID :          ");
  Serial.println(sensor.sensor_id);
  Serial.print("Valor Maximo: ");
  Serial.print(sensor.max_value);
  Serial.println(F("%"));
  Serial.print("Valor Minimo: ");
  Serial.print(sensor.min_value);
  Serial.println(F("%"));
  Serial.print("Resolucion:   ");
  Serial.print(sensor.resolution);
  Serial.println(F("%"));
  Serial.println(F("------------------------------------"));
}

void loop() {
  delay(5000);
}