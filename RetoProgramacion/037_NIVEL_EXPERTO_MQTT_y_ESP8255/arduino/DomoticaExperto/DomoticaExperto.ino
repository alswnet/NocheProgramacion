// Creado ChepeCarlos de ALSW
// Tutorial Completo en https://nocheprogramacion.com
// Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define NoWifi 0
#define Wifi 1
#define MqttWifi 2

int Foco = 0;
int Boton = 4 ;
long IntervaloLed = 0;
long TiempoFoco = 0;
long TiempoMqttReconectar = 0;
long TiempoMensaje = 0;
boolean EstadoLed = false;
boolean EstadoFoco = false;
boolean ConectarMqtt = false;
boolean ConectarWifi = false;
int EstadoWifi = NoWifi;

const char* TopicoFoco4 = "ALSW/foco4";
const char* TopicoFoco4Estado = "ALSW/foco4estado";
const char* TopicoMensaje = "ALSW/mensaje";

const char* ssid = "ALSW";
const char* password = "2526-4897";
const char* mqtt_server = "broker.mqtt-dashboard.com";
char msg[50];

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  pinMode(Boton, INPUT);
  pinMode(Foco, OUTPUT);
  pinMode(BUILTIN_LED, OUTPUT);
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
  /* Serial.print(TiempoFoco);
    Serial.print(" ");
    Serial.print(IntervaloLed);
    Serial.print(" ");
    Serial.println(millis());
  */
  if (TiempoFoco + IntervaloLed < millis()) {
    TiempoFoco = millis();
    EstadoLed  = !EstadoLed;
    if (EstadoLed) {
      digitalWrite(BUILTIN_LED, 1);
    } else  {
      digitalWrite(BUILTIN_LED, 0);
    }
  }
}

void ActualizarWifi() {
  if (!ConectarWifi) {
    ConectarWifi = true;
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
    if (client.connect("ALSWFoco4")) {//Cambiar por un nombre unico para no tener poblemas
      Serial.println(".. Conectado");
      client.subscribe(TopicoFoco4);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
    }
  }
  else {
    EstadoWifi = MqttWifi;
  }
  //Serial.print("Loop ?? ");
  //Serial.println(client.loop());

  if (TiempoMensaje + 3000 < millis()) {
    TiempoMensaje = millis();
    //snprintf (msg, 75, "%l", EstadoFoco);
    if (EstadoFoco) {
      msg[0] = '1';
    }
    else {
      msg[0] = '0';
    }
    Serial.print("Estado F4 - #");
    Serial.println(msg);
    client.publish(TopicoFoco4Estado, msg);
  }
}

void ActualizarBotones() {
  if (digitalRead(Boton) == 1) {
    Serial.println("Boton precionado");
    EstadoFoco = ! EstadoFoco;
    delay(25);
    while (digitalRead(Boton) == 1) {

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

  if (strcmp(topic, TopicoFoco4) == 0) {
    Serial.println("Topico Foco4");
    if ((char)payload[0] == '1') {
      EstadoFoco = true;
    } else {
      EstadoFoco  = false;
    }
  } else {
    Serial.println("No Topico Conocido");
  }
}

void ActualizarFoco() {
  if (EstadoFoco) {
    digitalWrite(Foco, 1);
  }
  else {
    digitalWrite(Foco, 0);
  }
}
