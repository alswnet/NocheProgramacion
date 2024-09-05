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

// #define ESPALEXA_DEBUG
#include "token.h"
#include "CTBot.h"
#include "Utilities.h"
#include <Espalexa.h>
#include <MQTT.h>

struct estado {
  bool actual;
  bool anterior;
};

estado estadoWifi = { false, false };
estado estadoBot = { false, false };
estado estadoMQTT = { false, false };
estado estadoAlexa = { false, false };

void setup() {
  Serial.begin(115200);

  Serial.println();
  Serial.println("Iniciando Coneccion TelegramBot y MQTT");
  Serial.println();

  xTaskCreatePinnedToCore(
    procesoWifi,   /* Nombre de la funcion */
    "procesoWifi", /* Nombre del proceso  */
    10000,         /* Tamano de palabra */
    NULL,          /* parametros de entrada */
    10,            /* Prioridas del proceso */
    NULL,          /* Manejo del proceso  */
    1);            /* Procesador a poner la operacion */
  delay(100);

  xTaskCreatePinnedToCore(
    procesoTelegram,   /* Nombre de la funcion */
    "procesoTelegram", /* Nombre del proceso  */
    10000,             /* Tamano de palabra */
    NULL,              /* parametros de entrada */
    7,                 /* Prioridas del proceso */
    NULL,              /* Manejo del proceso  */
    1);

  xTaskCreatePinnedToCore(
    procesoMQTT,   /* Nombre de la funcion */
    "procesoMQTT", /* Nombre del proceso  */
    10000,         /* Tamano de palabra */
    NULL,          /* parametros de entrada */
    8,             /* Prioridas del proceso */
    NULL,          /* Manejo del proceso  */
    1);

  xTaskCreatePinnedToCore(
    procesoAlexa,   /* Nombre de la funcion */
    "procesoAlexa", /* Nombre del proceso  */
    10000,          /* Tamano de palabra */
    NULL,           /* parametros de entrada */
    9,              /* Prioridas del proceso */
    NULL,           /* Manejo del proceso  */
    1);
}

void loop() {
  // put your main code here, to run repeatedly:
}
