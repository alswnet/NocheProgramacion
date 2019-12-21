#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#include <WiFiMulti.h>
WiFiMulti wifiMulti;
#else
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti wifiMulti;
#endif

#include <MQTT.h>

const char ssid1[] = "ALSW";
const char pass1[] = "25264897";
const char ssid2[] = "ALSW2";
const char pass2[] = "7210-3607";
const char ssid3[] = "ssid";
const char pass3[] = "pass";

WiFiClient net;
MQTTClient client;

int Led = 5;
int Foco = 14;

unsigned long lastMillis = 0;

void connect() {
  Serial.print("Conectando con Wifi...");
  while (wifiMulti.run() != WL_CONNECTED) {
    digitalWrite(Led, 0);
    delay(100);
    digitalWrite(Led, 1);
    delay(100);
    Serial.print(".");
  }

  Serial.print("\nConectando con MQTT...");
  while (!client.connect("NavidadLocal", "NavidadALSW2", "SubcribanseAALSWenYoutube")) {
    digitalWrite(Led, 0);
    delay(1000);
    digitalWrite(Led, 1);
    delay(1000);
    Serial.print("*");
  }

  Serial.println("\nConectado :D !");

  client.subscribe("/ALSW/foco/Navidad");
}

void RecibirMensaje(String &topic, String &payload) {
  Serial.println("Mensaje: " + topic + " - " + payload);
  if (payload == "1") {
    digitalWrite(Foco, 1);
    Serial.println("Navidad Activada");
  }
  else {
    digitalWrite(Foco, 0);
    Serial.println("Navidad Desactivada");
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(Led, OUTPUT);
  pinMode(Foco, OUTPUT);
  digitalWrite(Led, 0);
  digitalWrite(Foco, 0);

  Serial.println("Iniciando Wifi");
  WiFi.mode(WIFI_STA);//Cambiar modo del Wi-Fi
  delay(100);
  wifiMulti.addAP(ssid1, pass1);
  wifiMulti.addAP(ssid2, pass2);
  wifiMulti.addAP(ssid3, pass3);

  client.begin("broker.shiftr.io", net);
  client.onMessage(RecibirMensaje);

  connect();
}

void loop() {
  client.loop();
  delay(10);

  if (!client.connected()) {
    connect();
  }
}
