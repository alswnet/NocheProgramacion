
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



void conectarWifi() {

  WiFi.mode(WIFI_STA);

  wifiMulti.addAP(ssid_1, password_1);
  wifiMulti.addAP(ssid_2, password_2);
  wifiMulti.addAP(ssid_3, password_3);

  Serial.println("Conectando con Wifi...");
  if (wifiMulti.run() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("WiFi Conectado");
    Serial.print("Mi IP es: ");
    Serial.println(WiFi.localIP());
    estado = noBot;
  }

  MDNS.begin(nombre);
  configurarOTA();
  configurarTelnet();
  configurarBot();
}


void actualizarWifi() {

  if (wifiMulti.run() != WL_CONNECTED) {
    Serial.println("Wifi No Conectada!");
    delay(500);
    estado = noWifi;
    return;
  } else if (estado == noWifi) {
    estado = noBot;
  } else if (estado != conectado) {
    if (miBot.testConnection()) {
      estado = conectado;
    } else {
      estado = noBot;
    }
  }


#if defined(ESP8266)
  MDNS.update();
#endif
  ArduinoOTA.handle();
}

void configurarTelnet() {

  MDNS.addService("telnet", "tcp", 23);
  TelnetStream.begin();
}


void actualizarTelnet() {
  while (TelnetStream.available()) {
    char Letra = TelnetStream.read();
    mensajeSerial(Letra, TelnetStream);
  }
}
