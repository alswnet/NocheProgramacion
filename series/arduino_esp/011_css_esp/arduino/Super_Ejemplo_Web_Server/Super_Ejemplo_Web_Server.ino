// Creado ChepeCarlos de ALSW
// Tutorial Completo en https://nocheprogramacion.com
// Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

#if defined(ESP32)
//Librerias para ESP32
#define EEPROM_SIZE 64
#include <WiFi.h>
#include <WiFiMulti.h>
#include <ESPmDNS.h>
WiFiMulti wifiMulti;

#elif defined(ESP8266)
//Librerias para ESP8266
#define EEPROM_SIZE 12
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266mDNS.h>
ESP8266WiFiMulti wifiMulti;
#endif

#include <EEPROM.h>
#include "data.h"

const uint32_t TiempoEsperaWifi = 5000;
const uint32_t TiempoEsperaCliente = 5000;

#define CantidadBotones 5
int Pin[CantidadBotones] = {5, 4, 22, 2, 23};
boolean Estado[CantidadBotones] = {false, false, false, false, false};
boolean EstadoAnterior[CantidadBotones] = {false, false, false, false, false};

unsigned long TiempoActual = 0;
unsigned long TiempoAnterior = 0;
const long TiempoCancelacion = 500;
WiFiServer servidor(80);

void setup() {
  Serial.begin(115200);
  Serial.println("\nIniciando Server Web");

  EEPROM.begin(EEPROM_SIZE);
  Serial.println("EEPROM Configurada");

  Serial.println("Iniciando Sistema");
  for (int i = 0; i < CantidadBotones; i++) {
    Estado[i] = EEPROM.read(i);
    EstadoAnterior[i] = Estado[i];
    pinMode(Pin[i], OUTPUT);
    digitalWrite(Pin[i], Estado[i]);
    Serial.print("Boton[");
    Serial.print(i + 1);
    Serial.print("] ");
    Serial.println(Estado[i] ? "Encendido" : "Apagado");
  }

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
            ActualizarBotones();
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
  Cliente.print("HTTP/1.1 200 OK\n");
  Cliente.print("Content-Type: text/html\n\n");
  Cliente.print(Pagina);
  Cliente.print("Hola ");
  Cliente.print(Cliente.remoteIP());
  for (int i = 1; i <= CantidadBotones; i++) {
    ImprimirBoton(Cliente, i, Estado[i - 1]);
  }

  Cliente.print("</center></body></html>");
}

void VerificarMensaje(String Mensaje) {
  if (Mensaje.indexOf("GET") >= 0) {
    for (int i = 1; i <= CantidadBotones; i++) {
      if (Mensaje.indexOf("/on" +  String(i)) >= 0) {
        Estado[i - 1] = true;
      } else if (Mensaje.indexOf("/off" +  String(i)) >= 0) {
        Estado[i - 1] = false;
      }
    }
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

void ActualizarBotones() {
  boolean Actualizado = false;
  for (int i = 0; i < CantidadBotones; i++) {
    if (Estado[i] != EstadoAnterior[i]) {
      Actualizado = true;
      EstadoAnterior[i] = Estado[i];
      digitalWrite(Pin[i], Estado[i]);
      EEPROM.put(i, Estado[i]);
      Serial.print("Boton[");
      Serial.print(i);
      Serial.print("] ");
      Serial.println(Estado[i] ? "Encendido" : "Apagado");
    }
  }
  if (Actualizado) {
    EEPROM.commit();
  }
}

void ImprimirBoton(WiFiClient& Cliente, int i, boolean Estado) {
  Cliente.print("<br>Boton ");
  Cliente.print(i);
  Cliente.print(":<br> <a href='/");
  Cliente.print(Estado ? "off" : "on");
  Cliente.print(i);
  Cliente.print("'> <div class='");
  Cliente.print(Estado ? "vivo" : "muerto");
  Cliente.print("'<br>");
  Cliente.print("<span class='pollo'>");
  Cliente.print("<span class='huevo'></span>");
  Cliente.print("</span></div></a>");
}
