// Creado ChepeCarlos de ALSW
// Tutorial Completo en https://nocheprogramacion.com
// Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

template<class T> inline Print &operator <<(Print &obj, T arg) {
  obj.print(arg);
  return obj;
}

#if defined(ESP32)
//Librerias para ESP32
#include <WiFi.h>
#include <WiFiMulti.h>
WiFiMulti wifiMulti;
#elif defined(ESP8266)
//Librerias para ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti wifiMulti;
#endif

#include "token.h"
#include <MQTT.h>

#define Apagado 0
#define Encendido 1

#define wifi 0
#define conectado 1
#define grabar 2
#define envivo 3

float WifiTiempo = 0;
float WifiEspera = 500;
const uint32_t TiempoEsperaWifi = 3000;

struct Indicador {
  String Nombre;
  int Led;
  int Estado;
  int Estado_Anterior;
};

#define cantidadLed 4
Indicador Indicadores[cantidadLed] = {
  {"Wifi", 2, Apagado, Encendido},  // D4 - Wifi
  {"OBS", 0, Apagado, Encendido},  // D3 - OBS
  {"Grabando", 14, Apagado, Encendido}, // D5 - Rojo
  {"EnVivo", 16, Apagado, Encendido}  // D8 - Verde
};

#define Rojo 0
#define Verde 1

#define cantidadBotones 2
const int Boton[2] = {
  13, // D7 -  Rojo
  12 // D6 - Verde
};

WiFiClient net;
MQTTClient client;

void setup() {
  Serial.begin(115200);
  Serial.println("\nIniciando El Monitor de OBS");
  Serial.println();

  for (int i = 0; i < cantidadLed; i++) {
    pinMode(Indicadores[i].Led, OUTPUT);
  }

  for (int i = 0; i < cantidadBotones; i++) {
    pinMode(Boton[i], INPUT);
  }

  client.begin(BrokerMQTT, PuertoMQTT, net);
  client.onMessage(MensajeMQTT);

  ActualizarIndocadores();

  ConfigurarWifi();
}

void loop() {
  client.loop();
  delay(10);

  if (!client.connected()) {
    Reconectar();
  }

  ActualizarIndocadores();

  if (Indicadores[conectado].Estado) {
    ActualizarBotones();
  } else {
    ErrorBotones();
  }
}

void ActualizarBotones() {
  int BotonGrabar = digitalRead(Boton[Rojo]);
  int BotonEnvivo = digitalRead(Boton[Verde]);

  if (millis() - WifiTiempo > WifiEspera) {
    if (BotonGrabar) {
      Serial.println("Cambiando Grabacion");
      client.publish(TopicSolisitud, MensajeGrabacion);
      while (BotonGrabar) {
        Serial.print("-");
        BotonGrabar = digitalRead(Boton[Rojo]);
        ActualizarIndocadores();
        delay(250);
      }
    }
    if (BotonEnvivo) {
      Serial.println("Cambiando Envivo");
      client.publish(TopicSolisitud, MensajeEnvivo);
      while (BotonEnvivo) {
        Serial.print("-");
        BotonEnvivo = digitalRead(Boton[Verde]);
        ActualizarIndocadores();
        delay(250);
      }
    }
    WifiTiempo = millis();
  }
}

void ErrorBotones() {
  int BotonGrabar = digitalRead(Boton[Rojo]);
  int BotonEnvivo = digitalRead(Boton[Verde]);

  if (BotonGrabar) {
    for (int i = 0; i < 6; i++) {
      Indicadores[grabar].Estado = Encendido;
      ActualizarIndocadores();
      delay(200);
      Indicadores[grabar].Estado = Apagado;
      ActualizarIndocadores();
      delay(200);
    }
  }
  if (BotonEnvivo) {
    for (int i = 0; i < 6; i++) {
      Indicadores[envivo].Estado = Encendido;
      ActualizarIndocadores();
      delay(200);
      Indicadores[envivo].Estado = Apagado;
      ActualizarIndocadores();
      delay(200);
    }
  }
}

void ConfigurarWifi() {

  wifiMulti.addAP(ssid_1, password_1);
  //  wifiMulti.addAP(ssid_2, password_2);

  WiFi.mode(WIFI_STA);

  Serial.print("\nConectando a Wifi...");

  int contador = 0;
  while (wifiMulti.run(TiempoEsperaWifi) != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
    contador++;
    if (contador > 10) {
      Indicadores[wifi].Estado = Apagado;
      return;
    }
  }
  Indicadores[wifi].Estado = Encendido;
  Serial.println(".. Conectado");
  Serial.print("SSID:");
  Serial.print(WiFi.SSID());
  Serial.print(" ID:");
  Serial.println(WiFi.localIP());
}

void MensajeMQTT(String topic, String payload) {
  payload.toLowerCase();
  Serial << "MQTT[" << topic << "] " << payload << "\n";

  if (payload.equals("obs-conectado") || payload.equals("obs-ya-conectado")) {
    Indicadores[conectado].Estado = Encendido;
  } else  if (payload.equals("obs-no-conectado") || payload.equals("obs-no-encontrado") ) {
    Indicadores[conectado].Estado = Apagado;
    Indicadores[grabar].Estado = Apagado;
    Indicadores[envivo].Estado = Apagado;
  }  else if (payload.equals("obs-grabando")) {
    Indicadores[grabar].Estado = Encendido;
  }  else if (payload.equals("obs-no-grabando")) {
    Indicadores[grabar].Estado = Apagado;
  } else if (payload.equals("obs-envivo")) {
    Indicadores[envivo].Estado = Encendido;
  } else if (payload.equals("obs-no-envivo")) {
    Indicadores[envivo].Estado = Apagado;
  } else {
    Serial.println("[Error] No comando");
  }
  ActualizarIndocadores();
}

void ActualizarIndocadores() {
  boolean Cambio = false;
  for (int i = 0; i < cantidadLed; i++) {
    if (Indicadores[i].Estado != Indicadores[i].Estado_Anterior) {
      Serial << Indicadores[i].Nombre << "[" << (Indicadores[i].Estado ? "Encendido" : "Apagado") << "] " ;
      Indicadores[i].Estado_Anterior = Indicadores[i].Estado;
      if (i < 2) {
        digitalWrite(Indicadores[i].Led, Indicadores[i].Estado);
      } else {
        digitalWrite(Indicadores[i].Led, !Indicadores[i].Estado);
      }
      Cambio = true;
    }
  }
  if (Cambio) {
    Serial.println();
  }

}

void Reconectar() {
  Serial.print("\nConectando a Wifi ..");
  int contador = 0;
  Indicadores[conectado].Estado = Apagado;
  Indicadores[wifi].Estado = Apagado;
  while (wifiMulti.run(TiempoEsperaWifi) != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
    contador++;
    if (contador > 10) {
      return;
    }
  }
  Serial.println("..Conectado");

  Serial.print("Conectado a MQTT***");
  contador = 0;
  while (!client.connect(NombreESP, usuario, pass)) {
    //  while (!client.connect(NombreESP)) {
    Serial.print("*");
    delay(500);
    contador++;
    if (contador > 10) {
      return;
    }
  }
  Serial.println("**Conectado");
  Indicadores[wifi].Estado = Encendido;
  client.subscribe(Topic);

  SolisitarEstado();
  ActualizarIndocadores();
}

void SolisitarEstado() {
  client.publish(TopicSolisitud, MensajeEstado);
}
