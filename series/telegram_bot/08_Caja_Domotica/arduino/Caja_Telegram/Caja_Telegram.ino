// Creado ChepeCarlos
// Tutorial Completo en https://nocheprogramacion.com
// Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

template<class T> inline Print &operator<<(Print &obj, T arg) {
  obj.print(arg);
  return obj;
}

#include <TelnetStream.h>

#include "data.h"

#define noWifi 0
#define noBot 1
#define conectado 2

int estado = noWifi;
int estadoAnterior = -1;

struct Rele {
  String nombre;
  int pin;
  boolean Estado;
  boolean Estado_Anterior;
  boolean Invertido;
};

#define CantidadAparatos 3

Rele Aparatos[CantidadAparatos] = {
  { "Ventilador", 4, true, false, false },
  { "Lampara", 5, true, false, false },
  { "cafetera", 15, true, false, false }
};

int pinLed = 2;

void setup() {
  Serial.begin(115200);
  Serial << "Iniciando Sistema: " << nombre << "\n";
  configurarLed();
  configurarReles();
  conectarWifi();
}

void loop() {
  actualizarWifi();
  actualizarRele();
  actualizarBot();
  actualizarSerial();
  actualizarTelnet();
  actualizarLed();
  delay(10);
}

void actualizarSerial() {
  while (Serial.available()) {
    char Letra = Serial.read();
    mensajeSerial(Letra, Serial);
  }
}

void mensajeSerial(char mensaje, Stream &miSerial) {
  switch (mensaje) {
    case 'e':
    case 'E':
      estadoRele(miSerial);
      break;
    case 'f':
    case 'F':
      formatiarMemoria(miSerial);
      break;
  }
}
