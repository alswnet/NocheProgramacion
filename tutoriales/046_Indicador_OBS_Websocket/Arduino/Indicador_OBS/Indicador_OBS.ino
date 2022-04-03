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

#define Grabacion 0 //Arallido Foco
#define Striming 1 //Rojo Foco
#define FPS 2 // Rojo Led
#define KBS 3 // Azul Led
#define Conectado 4 // Verde Led

#define Indicadores 5

#define Desactivo 0
#define Activo 1

int Led[Indicadores] = {16, 12, 13, 4, 5};
int Estado[Indicadores] = {0, 0, 0, 0, 0};
int EstadoAnterior[Indicadores] = {0, 0, 0, 0, 0};

const char ssid1[] = "ALSW";
const char pass1[] = "25264897";
const char ssid2[] = "ALSW2";
const char pass2[] = "7210-3607";
const char ssid3[] = "ssid";
const char pass3[] = "pass";

WiFiClient net;
MQTTClient client;

unsigned long lastMillis = 0;

void Conectar() {
  Serial.print("Conectando a Wifi...");
  while (wifiMulti.run() != WL_CONNECTED) {
    for (int i = 2; i < Indicadores; i++) {
      digitalWrite(Led[i], 1);
    }
    delay(1000);
    for (int i = 2; i < Indicadores; i++) {
      digitalWrite(Led[i], 0);
    }
    delay(1000);
    Serial.print(".");
  }
  Serial.print("\nConectado a MQTT...");

  while (!client.connect("IndicadorOBS", "chepecarlos", "secretoespecial")) {
    digitalWrite(Led[FPS], 1);
    digitalWrite(Led[KBS], 0);
    delay(500);
    digitalWrite(Led[FPS], 0);
    digitalWrite(Led[KBS], 1);
    delay(500);
    Serial.print("*");
  }
  digitalWrite(Led[FPS], 0);
  digitalWrite(Led[KBS], 0);
  Serial.println("\nConectado MQTT!");
  client.subscribe("/ALSW/OBS/#");
}

void RecibirMQTT(String &topic, String &payload) {
  Serial.println("Recivio: " + topic + " - " + payload);

  if (topic == "/ALSW/OBS/Streaming") {
    if (payload == "true") {
      Estado[Striming] = 1;
    }
    else if (payload == "false") {
      Estado[Striming] = 0;
    }
  }
  else if (topic == "/ALSW/OBS/Grabacion") {
    if (payload == "true") {
      Serial.print("grabando");
      Estado[Grabacion] = 1;
    }
    else if (payload == "false") {
      Estado[Grabacion] = 0;
    }
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  for (int i = 0; i < Indicadores; i++) {
    pinMode(Led[i], OUTPUT);
  }

  for (int i = 0; i < Indicadores; i++) {
    Serial.print("indicador ");
    Serial.println(i);
    digitalWrite(Led[i], 1);
    delay(1500);
    digitalWrite(Led[i], 0);
    delay(1500);
  }
  delay(1000);
  //pinMode(LedIndicador, OUTPUT);
  //digitalWrite(LedIndicador, 1);
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

  ActualizarLed();
}

void ActualizarLed() {
  for (int i = 0; i < Indicadores; i++) {
    if (EstadoAnterior[i] != Estado[i] ) {
      EstadoAnterior[i] = Estado[i];
      digitalWrite(Led[i], Estado[i]);
    }
  }
}
