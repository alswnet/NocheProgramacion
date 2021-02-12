#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define LED_PIN    6

#define LED_COUNT 124

int CantidadMatris = 0;
int CantidadMatrisMaxima = 124;
uint32_t MatrisColores[124];

Adafruit_NeoPixel TiraNeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  Serial.begin(9600);
  TiraNeoPixel.begin();
  TiraNeoPixel.show();
  TiraNeoPixel.setBrightness(100);
  uint32_t ColorFull = QueColorEs("blanco");
  FullColor(ColorFull, 3);
  ColorFull = QueColorEs("azul");
  FullColor(ColorFull, 5);
}

void loop() {
  if (Serial.available()) {
    DecodificarSerial();
  }
}


void DecodificarSerial() {
  String Mensaje = Serial.readStringUntil('*');
  int PosicionPleca = Mensaje.indexOf('/');
  int PosicionSaltoLinea = Mensaje.length();
  String Dato = Mensaje.substring(0, PosicionPleca);
  String Valor = Mensaje.substring(PosicionPleca + 1, PosicionSaltoLinea);

  //  Serial.print("Dato:");
  //  Serial.print(Dato);
  //  Serial.print(" Valor:");
  //  Serial.print(Valor);
  //  Serial.println("*");

  if (Dato.equals("color")) {
    uint32_t ColorFull = QueColorEs(Valor);
    FullColor(ColorFull, 10);
    Serial.print("Cambian a color: ");
    Serial.println(Valor);
  } else if (Dato.equals("filtro")) {
    if (Valor.equals("arcoiris")) {
      FiltroArcoiris(50);
      Serial.println("Filtro Arcoiris");
    }
  } else if (Dato.equals("matris")) {
    if (Valor.equals("reiniciar")) {
      Serial.println("Reiniciando Matris");
      CantidadMatris = 0;
    }
    else if (Valor.equals("activar")) {
      Serial.println("Dibujando Matris");
      for (int i = 0; i < CantidadMatris; i++) {
        Serial.print(MatrisColores[i]);
        Serial.print("/");
      }
      Serial.println();
      MatrisColor();
    }
    else  if (CantidadMatris < CantidadMatrisMaxima) {
      Serial.print("Agregando ");
      Serial.print(CantidadMatris);
      Serial.print(" ");
      Serial.println(Valor);
      uint32_t ColorFull = QueColorEs(Valor);
      MatrisColores[CantidadMatris] = ColorFull;
      CantidadMatris++;
    } else {
      Serial.println("Areglo lleno");
    }
  } else {
    Serial.println("No entiendo mensaje");
  }
}

uint32_t QueColorEs(String TextoColor) {
  if (TextoColor.equals("rojo")) {
    return TiraNeoPixel.Color(255,   0,   0);
  } else if (TextoColor.equals("azul")) {
    return TiraNeoPixel.Color(0,   0,   255);
  } else if (TextoColor.equals("verde")) {
    return TiraNeoPixel.Color(0,   255,  0);
  } else if (TextoColor.equals("blanco")) {
    return TiraNeoPixel.Color(200,   200,  200);
  } else if (TextoColor.equals("nada")) {
    return TiraNeoPixel.Color(0,   0,  0);
  } else {
    Serial.println("No color");
  }
}

void MatrisColor() {
  int color = 0;
  TiraNeoPixel.clear();
  for (int i = 0; i < TiraNeoPixel.numPixels(); i++) {
    if (MatrisColores[color] != TiraNeoPixel.Color(0,   0,  0)) {
      TiraNeoPixel.setPixelColor(i, MatrisColores[color]);
    }
    color++;
    if (color >= CantidadMatris) {
      color = 0;
    }
  }
  TiraNeoPixel.show();
}

void FullColor(uint32_t color, int wait) {
  if (color == TiraNeoPixel.Color(0,   0,  0)) {
    TiraNeoPixel.clear();
    TiraNeoPixel.show();
  } else {
    for (int i = 0; i < TiraNeoPixel.numPixels(); i++) {
      TiraNeoPixel.setPixelColor(i, color);
      TiraNeoPixel.show();
      delay(wait);
    }
  }
}

void FiltroArcoiris(int wait) {
  for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256) {
    for (int i = 0; i < TiraNeoPixel.numPixels(); i++) {
      int pixelHue = firstPixelHue + (i * 65536L / TiraNeoPixel.numPixels());
      TiraNeoPixel.setPixelColor(i, TiraNeoPixel.gamma32(TiraNeoPixel.ColorHSV(pixelHue)));
    }
    TiraNeoPixel.show();
    delay(wait);
  }
}
