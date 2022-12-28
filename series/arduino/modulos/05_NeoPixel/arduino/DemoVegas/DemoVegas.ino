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


// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {

#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif

  tira.begin();
  tira.setBrightness(100);
  tira.show();
}

void loop() {
  colorBarrido(tira.Color(255, 0 , 0), 75);
  colorBarrido(tira.Color(0, 255 , 0), 75);
  colorBarrido(tira.Color(0, 0 , 255), 75);
  colorBarrido(tira.Color(200, 0, 200), 75);
  colorBarrido(tira.Color(200, 200, 0), 75);
  colorBarrido(tira.Color(0, 200, 200), 75);
}

void colorBarrido(uint32_t ColorActual, int Espera) {
  for (int r = 0; r < 9; r++) {
    tira.clear();
    for (int i = 0; i < tira.numPixels(); i++) {
      if (( r + i ) % 3 == 0) {
        tira.setPixelColor(i, ColorActual);
      }
    }
    tira.show();
    delay(Espera);
  }
}
