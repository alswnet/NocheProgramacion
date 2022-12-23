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

#include "data.h"
const uint32_t TiempoEsperaWifi = 5000;

#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
#include <avr/power.h>
#endif

#define Pin 4
#define CantidadLed 24

Adafruit_NeoPixel tira = Adafruit_NeoPixel(CantidadLed, Pin, NEO_GRB + NEO_KHZ800);



String Valor = "";
boolean Estado = true;
int Nivel = 50;
int Rojo = 255;
int Verde = 0;
int Azul = 0;
boolean Arcoiris = false;
long NivelHue = 0;

void funcionEncendido() {
  Serial.println("Encendiendo");
  Estado = true;
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "Encender Led");

}

void funcionApagado() {
  Serial.println("Apagando");
  Estado = false;
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "Apagar Led");
}

void funcionNivel() {
  if (server.hasArg("valor")) {
    Valor = server.arg("valor");
    Nivel = atoi(Valor.c_str());
  }

  Serial << "Cambiando nivel " << Nivel << "\n";
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "Cambian Nivel");
  tira.setBrightness(Nivel);
}

void funcionColor() {
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
  server.send(200, "text/plain", "Cambian Color");
}

void funcionArcoiris() {
  if (server.hasArg("estado")) {
    Valor = server.arg("estado");
    if (Valor == "vivo") {
      Arcoiris = true;
    } else {
      Arcoiris = false;
    }
  }

  Serial << "Arcoiris " << Arcoiris << "\n";
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "Cambiando Arcoiris");
}

void mensajeBase() {
  server.send(200, "text/html", Pagina);
}

void mensajeError() {
  String mensaje = "<h1>404</h1>";
  mensaje += "Pagina No encontrada</br>";
  mensaje += "Intenta otra pagina</br>";
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(404, "text/html", mensaje);
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

  if (!MDNS.begin("elesp")) {
    Serial.println("Erro configurando mDNS!");
    while (1) {
      delay(1000);
    }
  }

  server.on("/", mensajeBase);

  server.on("/vivo", funcionEncendido);
  server.on("/muerto", funcionApagado);

  server.on("/nivel", funcionNivel);
  server.on("/color", funcionColor);
  server.on("/arcoiris", funcionArcoiris);

  server.onNotFound(mensajeError);

  server.begin();
  Serial.println("Servidor HTTP iniciado");

#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif

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
      ColorSimple(tira.Color(Rojo, Verde, Azul));
    }
  } else {
    tira.clear();
    tira.show();
  }
  delay(10);

}

void ColorArcoiris() {
  tira.rainbow(NivelHue);
  NivelHue += 256;
  if (NivelHue > 65536) {
    NivelHue = 0;
  }
  tira.show();
}

void ColorSimple(uint32_t ColorActual) {
  for (int i = 0; i < tira.numPixels(); i++) {
    tira.setPixelColor(i, ColorActual);
  }
  tira.show();
}
