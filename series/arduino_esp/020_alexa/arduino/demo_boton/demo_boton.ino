#define ESPALEXA_DEBUG

#if defined(ESP32)
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <Espalexa.h>

const char* ssid = "ALSW_ESTUDIO";
const char* password = "Fullpower7##";

Espalexa miAlexa;

int pinBoton = 15;
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

void setup() {
  Serial.begin(115200);
  pinMode(pinLed, OUTPUT);
  pinMode(pinBoton, INPUT);
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

  miAlexa.addDevice("pollo", cambiarLampara);
  miAlexa.begin();

}

void loop() {
  // Alexa, busca dispositivos
  miAlexa.loop();
  delay(1);

  if (digitalRead(pinBoton)) {

    EspalexaDevice* foco = miAlexa.getDevice(0);
    int Nivel = foco->getValue();
    Serial.print("Nivel: ");
    Serial.println(Nivel);
    if (Nivel > 0) {
      Nivel = 0;
      digitalWrite(pinLed, LOW);
    } else {
      Nivel = 255;
      digitalWrite(pinLed, HIGH);
    }
    foco->setPercent(Nivel);
    delay(300);

  }
}
