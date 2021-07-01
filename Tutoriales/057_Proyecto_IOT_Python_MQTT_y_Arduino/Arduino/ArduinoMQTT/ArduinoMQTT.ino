// Creado ChepeCarlos de ALSW
// Tutorial Completo en https://nocheprogramacion.com
// Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

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

const char ssid1[] = "SubALSW";
const char pass1[] = "SIyConLaCampanita";
const char ssid2[] = "ALSW2";
const char pass2[] = "7210-3607";
const char ssid3[] = "ALSW_ESTUDIO";
const char pass3[] = "Fullpower7##";

WiFiClient net;
MQTTClient client;

unsigned long lastMillis = 0;
int Led = 5;
int Boton = 0;
boolean Estado = false;
boolean EstadoAnterior = false;

void Conectar() {
  Serial.print("Conectando a Wifi...");
  while (wifiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.print("\nConectado a MQTT...");

  while (!client.connect("ArduinoESP32", "ALSWSexy", "SubcribanseAALSWenYoutube")) {
    Serial.print("*");
    delay(1000);
  }

  Serial.println("\nConectado MQTT!");

  client.subscribe("/LED");
}

void RecibirMQTT(String &topic, String &payload) {
  Serial.println("Recivio: " + topic + " - " + payload);
  if (payload == "Encender") {
    Serial.println("Encender Foco");
    digitalWrite(Led, 1);
  } else if (payload == "Apagar") {
    Serial.println("Apagar Foco");
    digitalWrite(Led, 0);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(Led, OUTPUT);
  digitalWrite(Led, 1);
  pinMode(Boton, INPUT);
  Serial.println("Iniciando Wifi");
  WiFi.mode(WIFI_STA);//Cambiar modo del Wi-Fi
  delay(100);
  wifiMulti.addAP(ssid1, pass1);
  wifiMulti.addAP(ssid2, pass2);
  wifiMulti.addAP(ssid3, pass3);

  client.begin("broker.shiftr.io", net);
  client.onMessage(RecibirMQTT);

  Conectar();
}

void loop() {
  client.loop();
  delay(10);

  if (!client.connected()) {
    Conectar();
  }

  EnviarMQTT();

}

void EnviarMQTT() {
  if (digitalRead(Boton) == 0) {
    Estado = !Estado;
  }
  if (Estado != EstadoAnterior) {
    EstadoAnterior = Estado;
    if (Estado) {
      client.publish("/Boton", "1");
      Serial.println("Enviando 1");
    }
    else {
      client.publish("/Boton", "0");
      Serial.println("Enviando 0");
    }
    delay(300);
  }
}
