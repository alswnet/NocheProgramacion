#include <Servo.h>

struct SuperServo {
  unsigned int Pin;
  unsigned int PosicionDeseada;
  unsigned int PosicionActual;
  unsigned int PosicionDescanso;
  unsigned int PosicionMaxima;
  unsigned int PosicionMinima;
  unsigned int PulsoMaximo;
  unsigned int PulsoMinimo;
  Servo Motor;
};

int CantidadMotores = 6;
SuperServo Motores[6] = {
  {2, 0, 0, 90, 170, 10, 2400, 544},//Motor 0
  {3, 0, 0, 90, 170, 10, 2400, 544},
  {4, 0, 0, 90, 170, 10, 2400, 544},
  {5, 0, 0, 90, 170, 10, 2400, 544},
  {6, 0, 0, 90, 170, 10, 2400, 544},
  {7, 0, 0, 90, 170, 10, 2400, 544}
};
float Esperar = 100;
float TiempoAnterior = 0;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < CantidadMotores; i++) {
    Motores[i].Motor.attach(Motores[i].Pin, Motores[i].PulsoMinimo, Motores[i].PulsoMaximo);
    Motores[i].PosicionDeseada = Motores[i].PosicionDescanso;
    Motores[i].PosicionActual = Motores[i].PosicionDescanso;
    Motores[i].Motor.write(Motores[i].PosicionActual);
    Serial.print(i);
    Serial.print("/");
    Serial.println(Motores[i].PosicionActual);
  }
}

void loop() {
  if (Serial.available()) {
    DecodificarSerial();
  }

  ActualizarServos();
}

void DecodificarSerial() {
  // 1/90\n
  // 1 es motor 1Servo
  // 90 es la posicion

  String Mensaje = Serial.readStringUntil('\n');

  //  Serial.print("Mensaje : ");
  //  Serial.println(Mensaje);

  if (Mensaje.equals("d")) {
    PosicionDescanso();
  }

  int PosicionPleca = Mensaje.indexOf('/');
  int PosicionSaltoLinea = Mensaje.length();

  if (PosicionPleca < 0) return;

  int IDMotor = Mensaje.substring(0, PosicionPleca).toInt();
  int Posicion = Mensaje.substring(PosicionPleca + 1, PosicionSaltoLinea).toInt();
  Posicion = constrain(Posicion, 0, 180);

  if (IDMotor >= CantidadMotores) return;

  Motores[IDMotor].PosicionDeseada = constrain(Posicion, Motores[IDMotor].PosicionMinima, Motores[IDMotor].PosicionMaxima);

  //  Serial.print("Motor : ");
  //  Serial.print(IDMotor);
  //  Serial.print(" Grados : ");
  //  Serial.println(Posicion);
}

void ActualizarServos() {
  float TiempoActual = millis();
  if (TiempoActual - TiempoAnterior > Esperar) {
    TiempoAnterior = TiempoActual;
    for (int i = 0; i < CantidadMotores; i++) {
      if (Motores[i].PosicionActual != Motores[i].PosicionDeseada) {

        if (Motores[i].PosicionActual > Motores[i].PosicionDeseada) {
          Motores[i].PosicionActual--;
        } else if (Motores[i].PosicionActual < Motores[i].PosicionDeseada) {
          Motores[i].PosicionActual++;
        }

        //        Serial.print("Moviendo el servo [");
        //        Serial.print(i);
        //        Serial.print("] ");
        //        Serial.print(Motores[i].PosicionActual);
        //        Serial.print(" a ");
        //        Serial.print(Motores[i].PosicionDeseada);
        //        Serial.println();

        Serial.print(i);
        Serial.print("/");
        Serial.println(Motores[i].PosicionActual);

        Motores[i].Motor.write(Motores[i].PosicionActual);
      }
    }
  }
}

void PosicionDescanso() {
  for (int i = 0; i < CantidadMotores; i++) {
    Motores[i].PosicionDeseada = Motores[i].PosicionDescanso;
  }
}
