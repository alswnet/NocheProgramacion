// Creado ChepeCarlos
// Tutorial Completo en https://nocheprogramacion.com
// Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

template<class T> inline Print &operator <<(Print &obj, T arg) {
  obj.print(arg);
  return obj;
}

#if defined(ESP32)

#include <WiFi.h>
#include <WiFiMulti.h>
#include <ESPmDNS.h>
#include <WebServer.h>

WiFiMulti wifiMulti;
WebServer server(80);

#elif defined(ESP8266)

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>

ESP8266WiFiMulti wifiMulti;
ESP8266WebServer server(80);

#endif

#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
#include <avr/power.h>
#endif

#include "data.h"

#define Pin 4
#define CantidadLed 50
Adafruit_NeoPixel tira = Adafruit_NeoPixel(CantidadLed, Pin, NEO_GRB + NEO_KHZ800);

const uint32_t TiempoEsperaWifi = 5000;
boolean Estado = true;
boolean Arcoiris = false;
int Nivel = 50;
int Rojo = 255;
int Verde = 0;
int Azul = 0;

long HueActual = 0;
String Valor = "";

void mensajeBase() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/html", Pagina);
}

void mensajeError() {
  String mensaje = "<h1>404</h1>";
  mensaje += "Pagina No encontrada</br>";
  mensaje += "Intenta otra pagina</br>";
  server.send(404, "text/html", mensaje);
}

void funcionEncender() {
  Estado = true;
  Serial.println("Encender LED");
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "Endendiendo LED");
}

void funcionApagar() {
  Estado = false;
  Serial.println("Apagar LED");
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "Apagando LED");
}

void funcionNivel() {

  if (server.hasArg("valor")) {
    Valor = server.arg("valor");
    Nivel = atoi(Valor.c_str());
    tira.setBrightness(Nivel);
    Serial << "Cambiando nivel " << Nivel << "\n";
  }
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "Nivel Cambiado");
}

void funcionColor() {
  Serial.println("Cambiando color");
  if (server.hasArg("r")) {
    Valor = server.arg("r");
    Rojo = atoi(Valor.c_str());
    Serial << "Rojo " << Rojo << "\n";
  }
  if (server.hasArg("g")) {
    Valor = server.arg("g");
    Verde = atoi(Valor.c_str());
    Serial << "Verde " << Verde << "\n";
  }
  if (server.hasArg("b")) {
    Valor = server.arg("b");
    Azul = atoi(Valor.c_str());
    Serial << "Azul " << Azul << "\n";
  }

  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "cambiando color");
}

void funcionArcoiris() {
  if (server.hasArg("estado")) {
    Valor = server.arg("estado");
    if (Valor == "vivo") {
      Arcoiris = true;
    } else {
      Arcoiris = false;
    }

    Serial << "Estado Arcoiris " << Arcoiris << "\n";
  }
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "cambiando Arcoiris");
}

void setup() {
  Serial.begin(115200);
  Serial.println("\nIniciando Server Web");

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

  if (!MDNS.begin("elarbol")) {
    Serial.println("Erro configurando mDNS!");
    while (1) {
      delay(1000);
    }
  }

#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif

  Serial.println("Inicial NeoPixel");

  server.on("/" , mensajeBase);

  server.on("/vivo", funcionEncender);
  server.on("/muerto", funcionApagar);

  server.on("/nivel", funcionNivel);
  server.on("/color", funcionColor);
  server.on("/arcoiris", funcionArcoiris);

  server.onNotFound(mensajeError);


  server.begin();
  Serial.println("Servidor HTTP iniciado");

  tira.begin();
  tira.setBrightness(Nivel);
  tira.show();

  Pagina.replace("%ip", WiFi.localIP().toString());
}

void loop() {
  server.handleClient();

#if defined(ESP8266)
  MDNS.update();
#endif

  if (Estado) {
    if (Arcoiris) {
      ColorArcoiris();
    } else {
      uint32_t ColorActual = tira.Color(Rojo, Verde, Azul);
      ColorSimple(ColorActual);
    }
  } else {
    tira.clear();
    tira.show();
  }
  delay(10);

}

void ColorArcoiris() {
  tira.rainbow(HueActual);
  HueActual += 256;
  if (HueActual > 65536) {
    HueActual = 0;
  }
  tira.show();
}

void ColorSimple(uint32_t ColorActual) {
  for (int i = 0; i < tira.numPixels(); i++) {
    tira.setPixelColor(i, ColorActual);
  }
  tira.show();
}
