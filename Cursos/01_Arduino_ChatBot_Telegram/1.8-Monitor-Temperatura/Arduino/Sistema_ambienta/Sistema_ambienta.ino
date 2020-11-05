#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT11

#define Temperatura 0
#define Humedad 1
#define Aparente 2

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  dht.begin();
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    char Letra = Serial.read();
    switch (Letra) {
      case 't':
      case 'T':
        Serial.print("T;");
        Serial.println(CalculoAmbiente(Temperatura));
        break;
      case 'h':
      case 'H':
        Serial.print("H;");
        Serial.println(CalculoAmbiente(Humedad));
        break;
      case 'a':
      case 'A':
        Serial.print("A;");
        Serial.println(CalculoAmbiente(Aparente));
        break;
    }
  }
}

float CalculoAmbiente(int Opcion) {
  float T = dht.readTemperature();
  float H = dht.readHumidity();
  switch (Opcion) {
    case Temperatura:
      return T;
      break;
    case  Humedad:
      return H;
      break;
    case Aparente:
      float A = dht.computeHeatIndex(T, H, false);
      return A;
      break;
    default:
      return -100;
      break;
  }
}
