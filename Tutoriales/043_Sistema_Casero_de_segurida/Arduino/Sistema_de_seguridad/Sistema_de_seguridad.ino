#include <ESP8266WiFi.h>
#include <PubSubClient.h>

int Led[2] = {0, 4};
int TrigerPin = 12;
int EchoPin = 13;

const char* ssid = "ALSW2";
const char* password = "7210-3607";
const char* mqtt_server = "broker.mqtt-dashboard.com";

WiFiClient espClient;
PubSubClient client(espClient);
char msg[50];

void setup() {
  for (int i = 0; i < 2; i++) {
    pinMode(Led[i], OUTPUT);
  }
  pinMode(TrigerPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}


void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    for (int i = 0; i < 2; i++) {
      digitalWrite(Led[i], 1);
    }
    delay(500);
    for (int i = 0; i < 2; i++) {
      digitalWrite(Led[i], 0);
    }
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is acive low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  int D = Distancia();
  Serial.print("Distancia ");
  Serial.print(D);
  Serial.println("cm");

  if (D < 50) {
    for (int i = 0; i < 2; i++) {
      digitalWrite(Led[i], 1);
    }
    Serial.println("Enviando Mqtt");
    snprintf (msg, 75, "Alquien a %dcm", D);
    client.publish("ALSWcalabasa", msg);
    delay(10000);
     for (int i = 0; i < 2; i++) {
      digitalWrite(Led[i], 0);
    }
  }
}

long Distancia() {

  digitalWrite(TrigerPin, 0);
  delayMicroseconds(2);
  digitalWrite(TrigerPin, 1);
  delayMicroseconds(10);
  digitalWrite(TrigerPin, 0);

  long tiempo = pulseIn(EchoPin, HIGH);

  return tiempo / 29  / 2 ;

}


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ALSWCalabaza")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 2 seconds");
      // Wait 5 seconds before retrying
      delay(1000);
      for (int i = 0; i < 2; i++) {
        digitalWrite(Led[i], 1);
      }
      delay(1000);
      for (int i = 0; i < 2; i++) {
        digitalWrite(Led[i], 0);
      }
    }
  }
}
