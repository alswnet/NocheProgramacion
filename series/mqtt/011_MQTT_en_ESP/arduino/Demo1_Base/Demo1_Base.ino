#if defined(ESP32)
#include <WiFi.h>
#include <WiFiMulti.h>
WiFiMulti wifiMulti;
#else
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti wifiMulti;
#endif

#include <MQTT.h>
#include "data.h"

WiFiClient net;
MQTTClient clienteMQTT;

unsigned long tiempoAnterior = 0;

void MensajeMQTT(String topic, String payload) {
  Serial.print("Topic: ");
  Serial.print(topic);
  Serial.print(" Mensaje: ");
  Serial.println(payload);
}

void conectar() {
  Serial.print("Conectando con Wifi...");
  while (wifiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("Se conecto a Wifi");
  Serial.print(WiFi.SSID());
  Serial.print(" -  ");
  Serial.println(WiFi.localIP());

  Serial.print("Conectar a MQTT***");
  // while (!client.connect(NombreESP, "public", "public")) {
  while (!clienteMQTT.connect(NombreESP)) {
    Serial.print("*");
    delay(1000);
  }
  Serial.println("Conectado a MQTT");
  clienteMQTT.subscribe("/suscribirse");
}

void setup() {
  Serial.begin(115200);

  wifiMulti.addAP(ssid_1, password_1);
  wifiMulti.addAP(ssid_2, password_2);

  WiFi.mode(WIFI_STA);

  clienteMQTT.begin(BrokerMQTT, net);
  clienteMQTT.onMessage(MensajeMQTT);

  conectar();
}

void loop() {
  clienteMQTT.loop();
  delay(10);

  if (!clienteMQTT.connected()) {
    conectar();
  }
  if (millis() - tiempoAnterior > 1000) {
    tiempoAnterior = millis();
    clienteMQTT.publish("/saludo", "hola");
  }
}
