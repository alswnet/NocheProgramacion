// Creado ChepeCarlos de ALSW
// Tutorial Completo en https://nocheprogramacion.com
// Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

#include <Wire.h>
#include "RTClib.h"
int Led = 13;

int HoraInicio = 6;
int HoraFin = 18;
int Periodo = 15;
int PinRele = 2;
int HoraAnteriorInicio = 0;
int HoraAnteriorFin = 0;
int PinBoton = 3;
boolean Rele = false;

RTC_DS1307 rtc;

void setup() {
  pinMode(PinBoton, INPUT);
  pinMode(Led, OUTPUT);
  digitalWrite(Led, 1);
  pinMode(PinRele, OUTPUT);
  digitalWrite(PinRele, 1);
  Serial.begin (9600);
  Wire.begin();
  if (!rtc.begin()) {
    Serial.println("RTC no funciona!");
    ErrorLed();
  }
}

void loop() {

  DateTime ahora = rtc.now();
  int Hora = ahora.hour();
  int Minuto = ahora.minute();
  // Serial.print(ahora.year(), DEC);
  // Serial.print('/');
  // Serial.print(ahora.month(), DEC);
  // Serial.print('/');
  // Serial.print(ahora.day(), DEC);
  // Serial.print('/');
  // Serial.print(ahora.hour(), DEC);
  // Serial.print('/');
  // Serial.print(ahora.minute(), DEC);
  // Serial.print('/');
  // Serial.print(ahora.second(), DEC);
  // Serial.println();
  // Serial.println();
  // delay(1000);

  FuncionRiego(Hora, Minuto);
  FuncionBoton();

  if (Rele) {
    digitalWrite(PinRele, 1);
  }
  else {
    digitalWrite(PinRele, 0);
  }

}

void FuncionRiego(int Hora, int Minuto) {
  if (Hora >= HoraInicio && Hora <= HoraFin ) {
    if (Minuto <= Periodo && Hora != HoraAnteriorInicio) {
      Serial.println("Encendiendo Rele");
      Rele = true;
      HoraAnteriorInicio = Hora;
    }
    else if (Minuto > Periodo && Hora != HoraAnteriorFin) {
      Serial.println("Apagando Rele");
      Rele = false;
      HoraAnteriorFin = Hora;
    }
  }
}

void FuncionBoton() {
  if (digitalRead(PinBoton) == 1) {
    Serial.println("Cambiando estado de la Rele");
    Rele = !Rele;
    delay(300);
  }
}

void ErrorLed() {
  for (;;) {
    digitalWrite(Led, 0);
    delay(500);
    digitalWrite(Led, 1);
    delay(500);
  }
}
