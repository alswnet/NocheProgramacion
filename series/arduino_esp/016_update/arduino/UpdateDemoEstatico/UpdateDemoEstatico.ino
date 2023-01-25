// Creado ChepeCarlos de ALSW
// Tutorial Completo en https://nocheprogramacion.com
// Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

#if defined(ESP32)

#include <WiFi.h>
#include <WebServer.h>
#include <Update.h>

WebServer server(80);

#elif defined(ESP8266)

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

#endif

IPAddress ip_local(192, 168, 50, 69);
IPAddress gateway(192, 168, 50, 1);
IPAddress subnet(255, 255, 255, 0);

#include "data.h"

void PaginaSimple() {
  server.sendHeader("Connection", "close");
  server.send(200, "text/html", Pagina);
}

void ActualizarPaso1() {
  server.sendHeader("Connection", "close");
  server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
  ESP.restart();
}

void ActualizarPaso2() {
  HTTPUpload& upload = server.upload();
  if (upload.status == UPLOAD_FILE_START) {
    Serial.setDebugOutput(true);
    Serial.printf("Actualizanddo: %s\n", upload.filename.c_str());
    uint32_t maxSketchSpace = (ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000;
    if (!Update.begin(maxSketchSpace)) {
      Update.printError(Serial);
    }
  } else if (upload.status == UPLOAD_FILE_WRITE) {
    if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
      Update.printError(Serial);
    }
  } else if (upload.status == UPLOAD_FILE_END) {
    if (Update.end(true)) {
      Serial.printf("Actualizacion Exitosa: %u\nReiniciando...\n", upload.totalSize);
    } else {
      Update.printError(Serial);
    }
    Serial.setDebugOutput(false);
  } else {
    Serial.printf("Problema con la Actualizacion (Talves problema con la coneccion); Estado=%d\n", upload.status);
  }
  yield();
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Iniciando Servidor...");

  if (!WiFi.config(ip_local, gateway, subnet)) {
    Serial.println("Error en configuracion");
  }

  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() == WL_CONNECTED) {
    server.on("/", HTTP_GET, PaginaSimple);
    server.on("/actualizar", HTTP_POST, ActualizarPaso1, ActualizarPaso2);
    server.begin();
    Serial.print("o en la IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("Eror en Wifi");
  }
}

void loop() {
  server.handleClient();
  delay(2);
}
