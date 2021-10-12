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

unsigned long TiempoActual = 0;
unsigned long TiempoAnterior = 0;
const long TiempoCancelacion = 500;

WiFiServer servidor(80);

void setup() {
  Serial.begin(115200);
  Serial.println("\nIniciando multi Wifi");

  pinMode(pinLed, OUTPUT);
  digitalWrite(pinLed, 0);

  wifiMulti.addAP(ssid_1, password_1);
  wifiMulti.addAP(ssid_2, password_2);

  WiFi.mode(WIFI_STA);
  Serial.print("Conectando a Wifi ..");
  while (wifiMulti.run(TiempoEsperaWifi) != WL_CONNECTED) {
    Serial.print(".");
  }
  Serial.println(".. Conectado");
  Serial.print("SSID:");
  Serial.print(WiFi.SSID());
  Serial.print(" ID:");
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
            digitalWrite(pinLed, Estado);
            ResponderCliente(cliente);
            break;
          } else {
            Serial.println(LineaActual);
            VerificarMensaje(LineaActual);
            LineaActual = "";
          }
        }  else if (Letra != '\r') {
          LineaActual += Letra;
        }
      }
    }

    cliente.stop();
    Serial.println("Cliente Desconectado");
    Serial.println();
  }
}

void VerificarMensaje(String Mensaje) {
  if (Mensaje.indexOf("GET /encender") >= 0) {
    Serial.println("Encender Led");
    Estado = true;
  } else if (Mensaje.indexOf("GET /apagar") >= 0) {
    Serial.println("Apagar Led");
    Estado = false;
  }
}

void ResponderCliente(WiFiClient& cliente) {
  cliente.print(Pagina);
  cliente.print("Hola ");
  cliente.print(cliente.remoteIP());
  cliente.print("<br>Estado del led: ");
  cliente.print(Estado ? "Encendida" : "Apagada");
  cliente.print("<br>Cambia el Led: ");
  cliente.print("<a href = 'http://");
  cliente.print(WiFi.localIP());
  cliente.print("/");
  cliente.print(Estado ? "apagar" : "encender");
  cliente.print("'>Cambiar </a><br>");
  cliente.print("</html>");
}
