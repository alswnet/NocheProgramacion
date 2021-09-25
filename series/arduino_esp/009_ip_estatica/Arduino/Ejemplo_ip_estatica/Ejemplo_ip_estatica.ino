#if defined(ESP32)
//Librerias para ESP32
#include <WiFi.h>

#elif defined(ESP8266)
//Librerias para ESP8266
#include <ESP8266WiFi.h>
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

IPAddress ip_local(192, 168, 50, 69);
IPAddress gateway(192, 168, 50, 1);
IPAddress subnet(255, 255, 0, 0);

void setup() {
  Serial.begin(115200);

  Serial.println("\nIniciando Server Web");

  pinMode(pinLed, OUTPUT);
  digitalWrite(pinLed, 0);

  if (!WiFi.config(ip_local, gateway, subnet)) {
    Serial.println("Error en configuracion");
  }

  WiFi.mode(WIFI_STA);
  Serial.print("Conectando a Wifi ..");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }

  Serial.println(".. Conectado");
  Serial.print("SSID: ");
  Serial.print(WiFi.SSID());
  Serial.print(" ID: ");
  Serial.println(WiFi.localIP());
  Serial.print("ESP Mac Address: ");
  Serial.println(WiFi.macAddress());
  Serial.print("Subnet Mask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway IP: ");
  Serial.println(WiFi.gatewayIP());
  Serial.print("DNS: ");
  Serial.println(WiFi.dnsIP());

  servidor.begin();
}

void loop() {

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
