#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include "HX711.h"

#define calibration_factor 98230.0

#define DOUT  5
#define CLK  2

HX711 scale(DOUT, CLK);

const char* ssid = "TURBONETT_ALSW";
const char* password = "2526-4897";

WiFiServer server(80);
int estado = 0;

void setup() {
  Serial.begin(115200);
  scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.tare();
  Serial.println("La bascula a sido calibrada");
  Serial.println("");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("  ");
  Serial.print("Conectado a: ");
  Serial.print(ssid);
  Serial.println("");

  server.begin();
  Serial.print("IP: ");
  MDNS.addService("http", "tcp", 80);
}

void loop() {
  estado = int(scale.get_units()*453.592);
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  String peticion = client.readStringUntil('\r');
  Serial.println(peticion);
  client.flush();

  if (peticion.indexOf("/conteo") != -1)
  {
    String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n";
    s += "<center><h1>El peso de su objeto es: </h1></center>";
    s += "<center>";
    s += estado;
    s += "g</center>";
    s += "<center><a href=\"conteo\"> pesar nuevo objeto</a></center> </html> \n";
    client.print(s);
    delay(1);
    client.stop();
  }
}
