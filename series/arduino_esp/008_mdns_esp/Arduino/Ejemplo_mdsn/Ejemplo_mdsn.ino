#if defined(ESP32)
//Librerias para ESP32
#include <WiFi.h>
#include <WiFiMulti.h>
#include <ESPmDNS.h>
WiFiMulti wifiMulti;

#elif defined(ESP8266)
//Librerias para ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266mDNS.h>
ESP8266WiFiMulti wifiMulti;
#endif

#include "data.h"

int pinLed = 2;
boolean Estado = false;
const uint32_t TiempoEsperaWifi = 5000;
const uint32_t TiempoEsperaCliente = 5000;

unsigned long TiempoActual = 0;
unsigned long TiempoAnterior = 0;
const long TiempoCancelacion = 500;
WiFiServer servidor(80);

void setup() {
  Serial.begin(115200);

  Serial.println("\nIniciando Server Web");

  pinMode(pinLed, OUTPUT);
  digitalWrite(pinLed, 1);

  wifiMulti.addAP(ssid_1, password_1);
  wifiMulti.addAP(ssid_2, password_2);

  WiFi.mode(WIFI_STA);
  Serial.print("Conectando a Wifi ..");
  while (wifiMulti.run(TiempoEsperaWifi) != WL_CONNECTED) {
    Serial.print(".");
  }
  Serial.println(".. Conectado");
  Serial.print("SSID: ");
  Serial.print(WiFi.SSID());
  Serial.print(" ID: ");
  Serial.println(WiFi.localIP());

  if (!MDNS.begin("elesp")) {
    Serial.println("Erro configurando mDNS!");
    while (1) {
      delay(1000);
    }
  }
  Serial.println("mDNS configurado");

  servidor.begin();

  MDNS.addService("http", "tcp", 80);
}

void loop() {
#if defined(ESP8266)
  MDNS.update();
#endif

  WiFiClient cliente = servidor.available();

  if (cliente) {
    Serial.println("Nuevo Cliente");
    TiempoActual = millis();
    TiempoAnterior = TiempoActual;
    String LineaActual = "";

    while (cliente.connected() && TiempoActual - TiempoAnterior <= TiempoCancelacion) {
      if (cliente.available()) {
        TiempoActual = millis();
        char Letra = cliente.read();
        if (Letra == '\n') {
          if (LineaActual.length() == 0) {
            digitalWrite(pinLed, Estado ? 1 : 0);
            ResponderCliente(cliente);
            break;
          } else {
            Serial.println(LineaActual);
            VerificarMensaje(LineaActual);
            LineaActual = "";
          }
        }
        else if (Letra != '\r') {
          LineaActual += Letra;
        }
      }
    }
    cliente.stop();
    Serial.println("Client Disconnected.");
    Serial.println();
  }
}

void ResponderCliente(WiFiClient& Cliente) {
  Cliente.print(Pagina);
  Cliente.print("Hola ");
  Cliente.print(Cliente.remoteIP());
  Cliente.print("<br>Estado del led: ");
  Cliente.print(Estado ? "Encendida" : "Apagada");
  Cliente.print("<br>Cambia el Led: ");
  Cliente.print("<a href = '/");
  Cliente.print(Estado ? "apagar" : "encender");
  Cliente.print("'>Cambiar </a><br>");
  Cliente.print("</html>");
}

void VerificarMensaje(String Mensaje) {
  if (Mensaje.indexOf("GET /encender") >= 0) {
    Estado = true;
  } else if (Mensaje.indexOf("GET /apagar") >= 0) {
    Estado = false;
  }
}

void ActualizarWifi() {
  if (wifiMulti.run() != WL_CONNECTED) {
    Serial.print("No conectado a Wifi!");
    while (wifiMulti.run(TiempoEsperaWifi) != WL_CONNECTED) {
      delay(1000);
      Serial.print(".");
    }
    Serial.println(" Conectado");
  }
}
