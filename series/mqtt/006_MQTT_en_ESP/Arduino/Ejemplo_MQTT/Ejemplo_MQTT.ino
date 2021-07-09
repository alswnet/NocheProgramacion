// Creado ChepeCarlos de ALSW
// Tutorial Completo en https://nocheprogramacion.com
// Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

#if defined(ESP32)
//Librerias para ESP32
#include <WiFi.h>
#include <WiFiMulti.h>
WiFiMulti wifiMulti;
#define Encendido 1

#elif defined(ESP8266)
//Librerias para ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti wifiMulti;
#define Encendido 0

#endif

#include <MQTT.h>

WiFiClient net;
MQTTClient ClienteMQTT;

const uint32_t TiempoEsperaWifi = 5000;

int PinLed = LED_BUILTIN;
boolean EstadoLed = false;

void setup() {
  Serial.begin(115200);
  Serial.println("\nIniciando Arduino MQTT");

  wifiMulti.addAP("Tu_Red_wifi_1", "tu_pass_01");
  wifiMulti.addAP("Tu_Red_wifi_2", "tu_pass_02");
  wifiMulti.addAP("Tu_Red_wifi_3", "tu_pass_03");

  WiFi.mode(WIFI_STA);

  ClienteMQTT.begin("test.mosquitto.org", net);
  ClienteMQTT.onMessage(MensajeMQTT);

  pinMode(PinLed, OUTPUT);
  digitalWrite(PinLed, 0);
}

void loop() {
  ClienteMQTT.loop();
  delay(10);

  if (!ClienteMQTT.connected()) {
    ActualizarWifi();
  }
}


void MensajeMQTT(String &topic, String &payload) {
  if (topic.equals("/ALSW/led")) {
    if (payload.equals("encender")) {
      Serial.println("Encender led");
    } else {
      Serial.println("Apagar led");
    }
  } else {
    Serial.println("Mensaje: " + topic + " - " + payload);
  }
}

void ActualizarWifi() {
  Serial.print("Conectando a Wifi...");
  while (wifiMulti.run(TiempoEsperaWifi) != WL_CONNECTED) {
    EstadoLed = !EstadoLed;
    digitalWrite(PinLed, EstadoLed ? 0 : 1);
    Serial.print(".");
  }

  Serial.print("\nConectando a mqtt***");
  while (!ClienteMQTT.connect("arduino")) {
    EstadoLed = !EstadoLed;
    digitalWrite(PinLed, EstadoLed ? 0 : 1);
    delay(100);
    Serial.print("*");
  }

  digitalWrite(PinLed, Encendido);
  Serial.println("\nConectado a MQTT!");
  Serial.print("SSID:");
  Serial.print(WiFi.SSID());
  Serial.print(" ID:");
  Serial.println(WiFi.localIP());

  ClienteMQTT.subscribe("/ALSW/#");
  // ClienteMQTT.unsubscribe("/ALSW/#");
}
