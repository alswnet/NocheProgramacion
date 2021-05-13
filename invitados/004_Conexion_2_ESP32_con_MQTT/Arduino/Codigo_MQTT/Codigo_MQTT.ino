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

const char ssid[] = "chepecarlos";
const char pass[] = "alswnet07";

WiFiClient net;
MQTTClient client;

int Led = 4;
int Boton = 15;
boolean Estado = false;

void connect() {
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
  // client.unsubscribe("/ALSW/#");
}

void MensajeMQTT(String &topic, String &payload) {
  Serial.println("Mensaje: " + topic + " - " + payload);
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
  Serial.println();
  WiFi.persistent(false);
  WiFi.disconnect();
  WiFi.mode(WIFI_OFF);
  WiFi.mode(WIFI_STA);
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
