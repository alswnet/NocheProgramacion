#include <Espalexa.h>

#if defined(ESP32)
#include <WiFi.h>
#include <WebServer.h>
WebServer miServer(80);
#else
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
ESP8266WebServer miServer(80);
#endif

const char* ssid = "ALSW_ESTUDIO";
const char* password = "Fullpower7##";

Espalexa miAlexa;
int pinLed = 4;

void cambiarLampara(uint8_t brillo) {
  Serial.print("Cambiando Lampara a: ");

  if (brillo) {
    Serial.print("Encendido, brillo ");
    Serial.println(brillo);
    digitalWrite(pinLed, HIGH);
  }
  else  {
    Serial.println("Apagado");
    digitalWrite(pinLed, LOW);
  }
}

void serverBase() {
  String mensaje = "<h1>Alexa Lampara</h1>";
  mensaje += "<a href='/encender'>Encender</a> ";
  mensaje += "<a href='/apagar'>Apagar</a>";
  miServer.send(200, "text/html", mensaje);
}

void serverEncender() {
  String mensaje = "<h1>Alexa Lampara</h1>";
  mensaje += "<a href='/encender'>Encender</a> ";
  mensaje += "<a href='/apagar'>Apagar</a>";
  mensaje += "<br><h3>Encendido</h3>";
  miServer.send(200, "text/html", mensaje);

  EspalexaDevice* foco = miAlexa.getDevice(0);
  foco->setPercent(255);
  digitalWrite(pinLed, HIGH);
}

void serverApagar() {
  String mensaje = "<h1>Alexa Lampara</h1>";
  mensaje += "<a href='/encender'>Encender</a> ";
  mensaje += "<a href='/apagar'>Apagar</a>";
  mensaje += "<br><h3>Apagado</h3>";
  miServer.send(200, "text/html", mensaje);

  EspalexaDevice* foco = miAlexa.getDevice(0);
  foco->setPercent(0);
  digitalWrite(pinLed, LOW);
}

void server404() {
  if (!miAlexa.handleAlexaApiCall(miServer.uri(), miServer.arg(0)))
  {
    miServer.send(404, "text/plain", "404 no encontrado :(");
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(pinLed, OUTPUT);
  digitalWrite(pinLed, LOW);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Iniciar sistema");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Conectado a ");
  Serial.println(ssid);
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  miServer.on("/", HTTP_GET, serverBase);
  miServer.on("/encender", HTTP_GET, serverEncender);
  miServer.on("/apagar", HTTP_GET, serverApagar);
  miServer.onNotFound(server404);

  miAlexa.addDevice("lila", cambiarLampara);
  miAlexa.begin(&miServer);

}

void loop() {
  // Alexa, busca dispositivos
  miAlexa.loop();
  delay(1);
}
