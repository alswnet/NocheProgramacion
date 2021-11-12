// Creado ChepeCarlos de ALSW
// Tutorial Completo en https://nocheprogramacion.com
// Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

#if defined(ESP32)
//Librerias para ESP32
#include <WiFi.h>
#include <WiFiMulti.h>
WiFiMulti wifiMulti;

#elif defined(ESP8266)
//Librerias para ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti wifiMulti;

#endif

#include "data.h"
#include <MQTT.h>

const char* BrokerMQTT = "192.168.50.36";

WiFiClient net;
MQTTClient client;

const uint32_t TiempoEsperaWifi = 3000;

// ESP32
// Led1 > 2
// Led2 > 15
// Boton > 16

// ESP8266
// Led1 > D4
// Led2 > D8
// Boton > D0

int led1 = 2;
int led2 = 15;
int Boton = 16;
boolean Estado = false;

void setup() {
  Serial.begin(115200);
  Serial.println("\nIniciando Arduino MQTT");
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(Boton, INPUT);

  digitalWrite(led1, Estado);

  client.begin(BrokerMQTT, net);
  client.onMessage(MensajeMQTT);

  ConfigurarWifi();
}

void loop() {
  client.loop();
  delay(10);

  if (!client.connected()) {
    Reconectar();
  }

  EnviarMQTT();
}

void EnviarMQTT() {
  if (digitalRead(Boton)) {
    client.publish("ALSW/led", Estado ? "apagar" : "encender");
    Serial.print("Enviando:");
    Serial.println(Estado ? "apagar" : "encender");
    while (digitalRead(Boton)) {
      delay(100);
    }
  }
}


void MensajeMQTT(String topic, String payload) {
  Serial.println("Recivido: " + topic + " - " + payload);
  if (topic.indexOf("ALSW/led") >= 0) {
    if (payload.indexOf("encender") >= 0) {
      Serial.println("Encender led");
      Estado = true;
    } else {
      Serial.println("Apagar led");
      Estado = false;
    }
    digitalWrite(led1, Estado);
  }
}

void ConfigurarWifi() {

  wifiMulti.addAP(ssid_1, password_1);
  wifiMulti.addAP(ssid_2, password_2);

  WiFi.mode(WIFI_STA);

  Serial.print("Conectando a Wifi...");
  while (wifiMulti.run(TiempoEsperaWifi) != WL_CONNECTED) {
    Serial.print(".");
  }
  Serial.println(".. Conectado");
  Serial.print("SSID:");
  Serial.print(WiFi.SSID());
  Serial.print(" ID:");
  Serial.println(WiFi.localIP());
}

void Reconectar() {
  Serial.print("Conectando a Wifi ..");
  while (wifiMulti.run(TiempoEsperaWifi) != WL_CONNECTED) {
    Serial.print(".");
  }
  Serial.println("..Conectado");

  Serial.print("Conectado a MQTT***");
  //  while (!client.connect("arduino", "public", "public")) {/
  while (!client.connect("esp")) {
    Serial.print("*");
    delay(1000);
  }
  Serial.println("Conectado");

  client.subscribe("ALSW/#");
}
