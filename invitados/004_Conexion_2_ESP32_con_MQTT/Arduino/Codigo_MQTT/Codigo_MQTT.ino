// Creado ChepeCarlos de ALSW
// Tutorial Completo en https://nocheprogramacion.com
// Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#error "No es ni ESP32 o ES8266, que es?"
#endif

#include <MQTT.h>

const char ssid[] = "";
const char pass[] = "";

WiFiClient net;
MQTTClient client;

int Led = 5;
int Boton = 4;
boolean Estado = false;

void conectarMQTT() {

  Serial.print("Conencando a wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nConectando a mqtt ***");
  while (!client.connect("Arduino_ESP" + random(0, 100))) {
    Serial.print("*");
    delay(1000);
  }

  Serial.println("\nConectado a MQTT!");
  client.subscribe("/ALSW/#");

}

void MensajeMQTT(String &topic, String &payload) {
  Serial.print("Topico");
  Serial.print(topic);
  Serial.print(" - ");
  Serial.println( payload);

  if (topic == "/ALSW/Led") {
    if (payload == "encender") {
      digitalWrite(Led, 1);
      Serial.println("Encender Led");
    }
    else {
      digitalWrite(Led, 0);
      Serial.println("Apagar Led");
    }
  }

}

void setup() {

  pinMode(Led, OUTPUT);
  pinMode(Boton, INPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, pass);

  client.begin("test.mosquitto.org", net);
  client.onMessage(MensajeMQTT);

  conectarMQTT();

}

void loop() {
  client.loop();
  delay(10);

  if (!client.connected()) {
    conectarMQTT();
  }

  if (digitalRead(Boton)) {
    Estado = !Estado;
    Serial.print("Cambiando estado ");
    Serial.println(Estado);
    if (Estado) {
      client.publish("/ALSW/Led", "encender");
    }
    else {
      client.publish("/ALSW/Led", "apagar");
    }

    do {
      delay(50);
    } while (digitalRead(Boton));
    delay(100);
  }
}
