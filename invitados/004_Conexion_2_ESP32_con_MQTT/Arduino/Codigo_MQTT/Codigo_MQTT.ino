// Tutorial: https://nocheprogramacion.com/invitados/004_Conexion_2_ESP32_con_MQTT.html
// Video: https://www.youtube.com/watch?v=anISHJ6aiiM

#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#error "No es ni ESP32 o ES8266, que es?"
#endif

#include <MQTT.h>

const char ssid[] = "ALSW_ESTUDIO";
const char pass[] = "Fullpower7##";

WiFiClient net;
MQTTClient client;

unsigned long lastMillis = 0;

void connect() {
  Serial.print("Conencando a wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nConectando a mqtt ***");
  while (!client.connect("Arduino_ESP")) {
    Serial.print("*");
    delay(1000);
  }

  Serial.println("\nConectado a MQTT!");

  client.subscribe("/ALSW/#");
  // client.unsubscribe("/ALSW/#");
}

void MensajeMQTT(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  
  client.begin("test.mosquitto.org", net);
  client.onMessage(MensajeMQTT);

  connect();
}

void loop() {
  client.loop();
  delay(10); 
  
  if (!client.connected()) {
    connect();
  }

  if (millis() - lastMillis > 1000) {
    lastMillis = millis();
    client.publish("/ALSW/demo", "world");
  }
}
