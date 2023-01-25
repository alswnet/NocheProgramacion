// Creado ChepeCarlos de ALSW
// Tutorial Completo en https://nocheprogramacion.com
// Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

#if defined(ESP32)

#include <WiFi.h>
#include <ESPmDNS.h>

#elif defined(ESP8266)

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

#endif

#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#include "data.h"

void setup() {
  Serial.begin(115200);
  Serial.println("Cargando sistema...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Error con Wifi, reiniciando...");
    delay(5000);
    ESP.restart();
  }

  // Puerto de programacion, defecto 3232
  // ArduinoOTA.setPort(3232);

  // Nombre en Red, defecto esp3232-[MAC]
  // ArduinoOTA.setHostname("subcribete");

  // Controaseña, defecto no contraseña
  // ArduinoOTA.setPassword("dalelike");
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else {  // U_FS
      type = "filesystem";
    }

    Serial.println("Iniciando Programación " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nTerminando");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progreso: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });

  ArduinoOTA.begin();

  Serial.println("Listo");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  ArduinoOTA.handle();

}
