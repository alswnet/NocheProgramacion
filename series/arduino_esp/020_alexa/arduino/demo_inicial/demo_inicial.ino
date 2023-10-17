
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

  miAlexa.addDevice("foco", cambiarLampara);
  miAlexa.begin();

}

void loop() {
  // Alexa, busca dispositivos
  miAlexa.loop();
  delay(1);
}
