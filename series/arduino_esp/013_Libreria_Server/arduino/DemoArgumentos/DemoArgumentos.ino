// Creado ChepeCarlos
// Tutorial Completo en https://nocheprogramacion.com
// Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

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

void mensajeArgumento() {
  String mensaje = "Valores Recividos\n\n";
  mensaje += "URI: ";
  mensaje += server.uri();
  mensaje += "\nMetodo: ";
  mensaje += (server.method() == HTTP_GET) ? "GET" : "POST";
  mensaje += "\nArgumentos: ";
  mensaje += server.args();
  mensaje += "\n";

  for (int i = 0; i < server.args() ; i++) {
    mensaje += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  mensaje += "\n";

  if (server.hasArg("pollo")) {
    mensaje += "El Pollo dice " + server.arg("pollo");
  } else {
    mensaje += "No hay pollo";
  }

  server.send(200, "text/plain", mensaje);
}

void mensajeBase() {
  server.send(200, "text/plain", "Hola desde el ESP");
}

void mensajeError() {
  String mensaje = "<h1>404</h1>";
  mensaje += "Pagina No encontrada</br>";
  mensaje += "Intenta otra pagina</br>";
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

  MDNS.addService("http", "tcp", 80);

  server.on("/", mensajeBase);

  server.on("/valor", mensajeArgumento);

  server.onNotFound(mensajeError);

  server.begin();
  Serial.println("Servidor HTTP iniciado");
}

void loop() {
  server.handleClient();

#if defined(ESP8266)
  MDNS.update();
#endif

}
