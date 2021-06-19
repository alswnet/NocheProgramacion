#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2, 3);

#define Apagado 0
#define Encendido 1
#define Interminente 2

struct SuperLed {
  String Nombre;
  int Pin;
  int Estado;
  boolean Activo;
  float Tiempo;
};

SuperLed Leds[3] = {
  {"rojo", 5, Apagado, false, 0},
  {"azul", 4, Apagado, false, 0},
  {"verde", 13, Apagado, false, 0}
};
int CantidadLed = 3;

float IntervaloLed = 500;

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
  for (int i = 0; i < CantidadLed; i++) {
    pinMode(Leds[i].Pin, OUTPUT);
  }
}

void loop() {
  if (BTSerial.available()) {
    DecodificarSerial();
  }
  for (int i = 0; i < CantidadLed; i++) {
    ActualizarLed(Leds[i]);
  }

}

void ActualizarLed(SuperLed &Led) {
  switch (Led.Estado) {
    case Apagado:
      digitalWrite(Led.Pin, 0);
      break;
    case Encendido:
      digitalWrite(Led.Pin, 1);
      break;
    case Interminente:
      float TiempoActual = millis();
      if (TiempoActual - Led.Tiempo > IntervaloLed) {
        Led.Tiempo = TiempoActual;
        Led.Activo = !Led.Activo;
        if (Led.Activo) {
          digitalWrite(Led.Pin, 1);
        } else {
          digitalWrite(Led.Pin, 0);
        }
      }
      break;
  }
}


void DecodificarSerial() {
  // rojo/a \n
  // rojo es led
  // a mensaje [a|e|i](Apagado, Encendido, Interminente)
  String Mensaje = BTSerial.readStringUntil('\n');
  Serial.print("Mensaje : ");
  Serial.println(Mensaje);
  int PosicionPleca = Mensaje.indexOf('/');
  int PosicionSaltoLinea = Mensaje.length();

  String Dato = Mensaje.substring(0, PosicionPleca);
  String Valor = Mensaje.substring(PosicionPleca + 1, PosicionSaltoLinea);
  int EstadoActualLed = ObtenerEstadoLed(Valor);

  for (int i = 0; i < CantidadLed; i++) {
    if (Dato.equals(Leds[i].Nombre)) {
      Leds[i].Estado = EstadoActualLed;

      Serial.print("Led : ");
      Serial.print(Dato);
      Serial.print(" Estado : ");
      Serial.println(EstadoActualLed);
      return;
    }
  }
  Serial.println("Error mensaje");
}

int ObtenerEstadoLed(String Valor) {
  if (Valor.equals("a")) {
    return Apagado;
  } else if (Valor.equals("e")) {
    return Encendido;
  } else if (Valor.equals("i")) {
    return Interminente;
  }
  return -1;
}
