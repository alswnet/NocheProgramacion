#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
#include <avr/power.h>
#endif

#define Pin 4
#define CantidadLed 300

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
  for (long nivelHue = 0; nivelHue < 65536; nivelHue += 256) {
    uint32_t colorActual = tira.ColorHSV(nivelHue);
    for (int i = 0; i < tira.numPixels(); i++) {
      tira.setPixelColor(i, colorActual);
    }
    tira.show();
    delay(10);
  }
}
