#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif

#include <PubSubClient.h>

#define NoWifi 0
#define Wifi 1
#define MqttWifi 2

int Foco[] = {0, 4, 13};
int Boton[] = {2, 14, 12};
boolean EstadoFoco[] = {false, false, false};
boolean EstadoAnterior[] = {true, true, true};
long IntervaloLed = 0;
long TiempoFoco = 0;
long TiempoMqttReconectar = 0;
long TiempoMensaje = 0;
boolean EstadoLed = false;
boolean ConectarMqtt = false;
boolean ConectarWifi = false;
int EstadoWifi = NoWifi;

const char* TopicoFoco[4] = {"ALSW/foco1", "ALSW/foco2", "ALSW/foco3"};
const char* TopicoFocoEstado[4] = {"ALSW/foco1estado", "ALSW/foco2estado", "ALSW/foco3estado"};
const char* TopicoMensaje = "ALSW/mensaje";

const char* ssid = "ALSW";
const char* password = "2526-4897";
const char* mqtt_server = "broker.mqtt-dashboard.com";
char msg[50];

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(Foco[i], OUTPUT);
    pinMode(Boton[i], INPUT);
  }
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  Serial.println("Iniciando :) ");
}

void loop() {
  ActualizarFoco();
  ActualizarBotones();
  ActualizarWifi();
  ActualizarLed();
}

void ActualizarLed() {
  switch (EstadoWifi) {
    case NoWifi:
      IntervaloLed = 1000;
      break;
    case Wifi:
      IntervaloLed = 500;
      break;
    case MqttWifi:
      IntervaloLed = 50;
      break;
  }
  if (TiempoFoco + IntervaloLed < millis()) {
    TiempoFoco = millis();
    EstadoLed  = !EstadoLed;
    if (EstadoLed) {
      digitalWrite(LED_BUILTIN, 1);
    } else  {
      digitalWrite(LED_BUILTIN, 0);
    }
  }
}

void ActualizarWifi() {
  if (!ConectarWifi) {
    ConectarWifi = true;
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
  }

  if (WiFi.status() != WL_CONNECTED) {
    EstadoWifi = NoWifi;
    Serial.println("No Wifi");
    return;
  }
  else {
    EstadoWifi = Wifi;
  }

  if (!ConectarMqtt) {
    client.setServer(mqtt_server, 1883);
    client.setCallback(PreguntarMqtt);
    ConectarMqtt = true;
  }


  if (!client.loop() && TiempoMqttReconectar + 500 <  millis()) {
    TiempoMqttReconectar =  millis();
    Serial.print("Activando mqtt");
    if (client.connect("ALSWFoco")) {//Cambiar por un nombre unico para no tener poblemas
      Serial.println("... Conectado");
      for (int i = 0; i < 3; i++) {
        client.subscribe(TopicoFoco[i]);
      }
    } else {
      Serial.print(" error, rc=");
      Serial.println(client.state());
    }
  }
  else {
    EstadoWifi = MqttWifi;
  }

  if (TiempoMensaje + 3000 < millis()) {
    TiempoMensaje = millis();
    //snprintf (msg, 75, "%l", EstadoFoco);
    Serial.print("Estado");
    for (int i = 0; i < 3; i++) {
      if (EstadoFoco[i]) {
        msg[0] = '1';
      }
      else {
        msg[0] = '0';
      }
      Serial.print(" F");
      Serial.print(i + 1);
      Serial.print("-");
      Serial.print(msg);
      client.publish(TopicoFocoEstado[i], msg);
    }
    Serial.println();
  }

}

void ActualizarBotones() {
  for (int i = 0; i < 3; i++) {
    if (digitalRead(Boton[i]) == 0) {
      EstadoFoco[i] = !EstadoFoco[i];
      while (digitalRead(Boton[i]) == 0) {
        delay(300);
      }
      delay(300);
    }
  }
}

void PreguntarMqtt(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensaje recivido [");
  Serial.print(topic);
  Serial.print("] ");

  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }

  Serial.println();

  int FocoMensaje = -1;
  for (int i = 0; i < 3; i++) {
    if (strcmp(topic, TopicoFoco[i]) == 0) {
      Serial.print("Topico Foco");
      Serial.println(i + 1);
      FocoMensaje = i;
    }
  }


  if (FocoMensaje > -1 ) {
    if ((char)payload[0] == '1') {
      EstadoFoco[FocoMensaje] = true;
    } else {
      EstadoFoco[FocoMensaje]  = false;
    }
  } else {
    Serial.println("No Topico Conocido");
  }
}

void ActualizarFoco() {
  for (int i = 0; i < 3; i++) {
    if (EstadoFoco[i]) {
      digitalWrite(Foco[i], 1);
    }
    else {
      digitalWrite(Foco[i], 0);
    }
  }
}
