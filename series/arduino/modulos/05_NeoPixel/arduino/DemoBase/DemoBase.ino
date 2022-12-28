#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
#include <avr/power.h>
#endif

#define Pin 4
#define CantidadLed 24

// Driver
// WS2812 - NEO_KHZ800
// WS2811 - NEO_KHZ400
// LED
// GRB - NEO_GRB
// RGB - NEO_RGB
// RGBW - NEO_RGBW

Adafruit_NeoPixel tira = Adafruit_NeoPixel(CantidadLed, Pin, NEO_GRB + NEO_KHZ800);

void setup() {

#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif

  tira.begin();
  tira.setBrightness(100);
  tira.show();
}

void loop() {
  uint32_t ColorActual = tira.Color(255, 0 , 0);
  uint32_t ColorApagado = tira.Color(0, 0, 0);

  for (int i = 0; i < tira.numPixels(); i++) {
    tira.setPixelColor(i, ColorActual);
    tira.show();
    delay(100);
  }

  for (int i = 0; i < tira.numPixels(); i++) {
    tira.setPixelColor(i, ColorApagado);
    tira.show();
    delay(100);
  }
}
