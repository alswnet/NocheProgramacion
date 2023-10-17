//#define ESPALEXA_DEBUG

#if defined(ESP32)
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#include <Espalexa.h>

const char* ssid = "ALSW_ESTUDIO";
const char* password = "Fullpower7##";

Espalexa miAlexa;

int pinLED = 13;
int cantidadLED = 10;
uint32_t colorLed;

Adafruit_NeoPixel tiraLED(cantidadLED, pinLED, NEO_GRB + NEO_KHZ800);


void cambiarRGB(uint8_t brillo, uint32_t rgb) {
  Serial.print("Cambiando RGB a: ");

  if (brillo) {
    int Rojo = (rgb >> 16) & 0xFF;
    int Verde = (rgb >>  8) & 0xFF;
    int Azul = rgb & 0xFF;
    colorLed = tiraLED.Color(Rojo,   Verde,   Azul);
    Serial.print("Brillo: ");
    Serial.print(brillo);
    Serial.print(", Color: ");
    Serial.print(rgb);
    Serial.print(", Rojo: ");
    Serial.print(Rojo);
    Serial.print(", Verde: ");
    Serial.print(Verde);
    Serial.print(", Azul: ");
    Serial.println(Azul);
  }
  else  {
    Serial.println("Apagado");
    colorLed = tiraLED.Color(0,   0,   0);
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Iniciar sistema");

#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  tiraLED.begin();
  tiraLED.show();
  tiraLED.setBrightness(50);
  colorLed = tiraLED.Color(0,   0,   0);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Conectado a ");
  Serial.println(ssid);
  Serial.print("IP : ");
  Serial.println(WiFi.localIP());

  miAlexa.addDevice("paty", cambiarRGB);
  miAlexa.begin();

}

void loop() {
  miAlexa.loop();
//  colorTirra(25);
  delay(1);
}

void colorTirra(int espera) {
  tiraLED.clear();
  tiraLED.show();
  for (int i = 0; i < tiraLED.numPixels(); i++) {
    tiraLED.setPixelColor(i, colorLed);
    tiraLED.show();
    delay(espera);
  }
}
