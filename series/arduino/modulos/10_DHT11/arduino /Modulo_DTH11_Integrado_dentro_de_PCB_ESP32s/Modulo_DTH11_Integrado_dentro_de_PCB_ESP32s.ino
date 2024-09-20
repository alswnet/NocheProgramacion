#include "DHT.h" //incluimos la librería DHT sensor library de Adafruit 
#define PinSensor 4   // Pin digital al que se conecta el sensor
#define Tipo DHT11    // Tipo de sensor
DHT dht(PinSensor, Tipo);

void setup() {
  Serial.begin(9600); 
  dht.begin();
}

void loop(){
  delay(5000);   //lectura cada 5 minutos 
  //funciones para leer humedad y temperatura 
  float humedad = dht.readHumidity();
  float temperatura = dht.readTemperature();
  //mostrar datos en monitor serial
  Serial.print("Humedad: "); 
  Serial.println(humedad);
  Serial.print("Temperatura:"); 
  Serial.println(temperatura);
}

//ESP32 Wrover Module 