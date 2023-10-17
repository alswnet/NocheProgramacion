
//#define ESPALEXA_DEBUG            //Activa depuraccion

#if defined(ESP32)
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <Espalexa.h>

const char* ssid = "ALSW_ESTUDIO";
const char* password = "Fullpower7##";

Espalexa miAlexa;
EspalexaDevice* objetoAlexa;


int pinIzquierdo = 15;
int pinCentro = 5;
int pinDerecho = 4;

void lamparaIzquierda(uint8_t brillo) {
  Serial.print("Cambiando Lampara Izquierda: ");

  if (brillo) {
    Serial.print("Encendido, brillo ");
    Serial.println(brillo);
    digitalWrite(pinIzquierdo, HIGH);
  }
  else  {
    Serial.println("Apagado");
    digitalWrite(pinIzquierdo, LOW);
  }
}


void lamparaDerecho(uint8_t brillo) {
  Serial.print("Cambiando Lampara Derecho: ");

  if (brillo) {
    Serial.print("Encendido, brillo ");
    Serial.println(brillo);
    digitalWrite(pinDerecho, HIGH);
  }
  else  {
    Serial.println("Apagado");
    digitalWrite(pinDerecho, LOW);
  }
}

void lamparaCentro(uint8_t brillo) {
  Serial.print("Cambiando Lampara Centro: ");

  if (brillo) {
    Serial.print("Encendido, brillo ");
    Serial.println(brillo);
    digitalWrite(pinCentro, HIGH);
  }
  else  {
    Serial.println("Apagado");
    digitalWrite(pinCentro, LOW);
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(pinIzquierdo, OUTPUT);
  pinMode(pinCentro, OUTPUT);
  pinMode(pinDerecho, OUTPUT);
  digitalWrite(pinIzquierdo, LOW);
  digitalWrite(pinCentro, LOW);
  digitalWrite(pinDerecho, LOW);

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

  miAlexa.addDevice("lampara izquierda", lamparaIzquierda);
  miAlexa.addDevice("lampara derecha", lamparaDerecho, 255);

  objetoAlexa = new EspalexaDevice("lampara centro", lamparaCentro);
  miAlexa.addDevice(objetoAlexa);
  objetoAlexa->setValue(255);

  miAlexa.begin();

}

void loop() {
  // Alexa, busca dispositivos
  miAlexa.loop();
  delay(1);
}
