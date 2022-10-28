// Creado ChepeCarlos
// Tutorial Completo en https://nocheprogramacion.com
// Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

template<class T> inline Print &operator <<(Print &obj, T arg) {
  obj.print(arg);
  return obj;
}

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define Ancho_Pantalla 128
#define Alto_Pantalla 64
#define Direccion_Pantalla 0x3C
#define Reset_Pantalla -1

Adafruit_SSD1306 pantalla(Ancho_Pantalla, Alto_Pantalla, &Wire, Reset_Pantalla);

#define AltoMundo 4
#define AnchoMundo 8
int AltoCelda;
int AnchoCelda;

boolean Mundo[AnchoMundo][AltoMundo];
boolean MundoTmp[AnchoMundo][AltoMundo];
boolean MundoAnterior[AnchoMundo][AltoMundo];

void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando la pantalla");

  if (!pantalla.begin(SSD1306_SWITCHCAPVCC, Direccion_Pantalla)) {
    Serial.println(F("Error en pantalla OLED"));
    for (;;);
  }

  randomSeed(analogRead(0));
  AltoCelda = Alto_Pantalla / AltoMundo;
  AnchoCelda = Ancho_Pantalla / AnchoMundo;

  for (int y = 0;  y < AltoMundo; y ++) {
    for (int x = 0; x < AnchoMundo; x++) {
      Mundo[x][y] = random(2);
      MundoAnterior[x][y] = !Mundo[x][y];
    }
  }

  pantalla.display();

}

void loop() {
  ActualizarPantalla();
    delay(200);
  ActualizarMundo();

}

void ActualizarMundo() {
  for (int y = 0;  y < AltoMundo; y ++) {
    for (int x = 0; x < AnchoMundo; x++) {
      ActualizarCelda(x, y);
    }
  }

  for (int y = 0;  y < AltoMundo; y ++) {
    for (int x = 0; x < AnchoMundo; x++) {
      Mundo[x][y] = MundoTmp[x][y];
    }
  }
}

void ActualizarCelda(int x, int y) {
  int Vecinos = 0;
  int Xtmp = 0;
  int Ytmp = 0;
  for ( int i = -1; i <= 1 ; i++) {
    for (int j = -1; j <= 1; j++) {
      if (i == 0 &&  j == 0) continue;
      Xtmp = x + i;
      Ytmp = y + j;

      if (Xtmp < 0) {
        Xtmp = AnchoMundo - 1;
      } else if (Xtmp >= AnchoMundo) {
        Xtmp = 0;
      }

      if (Ytmp < 0) {
        Ytmp = AltoMundo - 1;
      } else if (Ytmp >= AltoMundo) {
        Ytmp = 0;
      }

      Vecinos += Mundo[Xtmp][Ytmp];
    }
  }

  if (!Mundo[x][y] && Vecinos == 3) {
    MundoTmp[x][y] = true;
  }
  else if (Mundo[x][y] && (Vecinos == 2 || Vecinos == 3)) {
    MundoTmp[x][y] = true;
  } else {
    MundoTmp[x][y] = false;
  }
}

void ActualizarPantalla() {
  boolean Dibujar = false;
  for (int y = 0;  y < AltoMundo; y ++) {
    for (int x = 0; x < AnchoMundo; x++) {
      if (Mundo[x][y] != MundoAnterior[x][y]) {
        MundoAnterior[x][y] = Mundo[x][y];
        Dibujar = true;
        //      Serial << Mundo[x][y] << " ";
        pantalla.fillRect(x * AnchoCelda , y * AltoCelda, AnchoCelda, AltoCelda, Mundo[x][y]);
      }
    }
    //    Serial << "\n";
  }
  if (Dibujar) {
    pantalla.display();
  }
}
