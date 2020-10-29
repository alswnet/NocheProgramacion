
#include "DHT.h"

#define DHTPIN 2

#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

#define Temperatura 0
#define Humedad 1
#define Calor 2

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("Empezando el sistema");

  dht.begin();
}

void loop() {
  if (Serial.available()) {
    char Mensaje = Serial.read();
    if (Mensaje == 't' || Mensaje == 'T') {
      float t =  CalculoAmbiente(Temperatura);
      Serial.print("T;");
      Serial.println(t);
    } else  if (Mensaje == 'h' || Mensaje == 'H') {
      float h =  CalculoAmbiente(Humedad);
      Serial.print("H;");
      Serial.println(h);
    } else  if (Mensaje == 'c' || Mensaje == 'C') {
      float c =  CalculoAmbiente(Calor);
      Serial.print("C;");
      Serial.println(c);
    }
  }

}

float CalculoAmbiente(int opcion) {

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Error Sensor Temperatura");
    return -1;
  }

  if (opcion == Temperatura) {
    return t;
  } else if (opcion == Humedad) {
    return h;
  } else if (opcion == Calor) {
    float hic = dht.computeHeatIndex(t, h, false);
    return hic;
  }
  return -1;
}
