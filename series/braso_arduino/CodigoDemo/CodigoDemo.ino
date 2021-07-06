#include <Servo.h>
#include <EEPROM.h>

struct SuperServo {
  unsigned int Pin;
  unsigned int PosicionDeseada;
  unsigned int PosicionActual;
  unsigned int PosicionDescanso;
  unsigned int PosicionMaxima;
  unsigned int PosicionMinima;
  unsigned int PulsoMaximo;
  unsigned int PulsoMinimo;
  unsigned int EEPRON_Descanso;
  Servo Motor;
};

int CantidadMotores = 6;
SuperServo Motores[6] = {
  {2, 0, 0, 0, 170, 10, 2400, 544, 1},//Motor 0
  {3, 0, 0, 0, 170, 10, 2400, 544, 2},
  {4, 0, 0, 0, 170, 10, 2400, 544, 3},
  {5, 0, 0, 0, 170, 10, 2400, 544, 4},
  {6, 0, 0, 0, 170, 10, 2400, 544, 5},
  {7, 0, 0, 0, 170, 10, 2400, 544, 6}
};

float Esperar = 100;
int DirecionEspera = 0;
float TiempoAnterior = 0;

void setup() {
  Serial.begin(9600);

  Esperar = 10 * EEPROM.read(DirecionEspera);

  for (int i = 0; i < CantidadMotores; i++) {
    Motores[i].Motor.attach(Motores[i].Pin, Motores[i].PulsoMinimo, Motores[i].PulsoMaximo);
    Motores[i].PosicionDescanso = EEPROM.read(Motores[i].EEPRON_Descanso);
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

  boolean Salir = MensajeConfiguracion(Mensaje);
  if (Salir) return;

  int PosicionPleca = Mensaje.indexOf('/');
  int PosicionSaltoLinea = Mensaje.length();

  if (PosicionPleca < 0) return;

  String Tipo = Mensaje.substring(0, PosicionPleca);
  int Valor = Mensaje.substring(PosicionPleca + 1, PosicionSaltoLinea).toInt();

  if (Tipo.equals("v")) {
    Esperar = Valor * 10;
    EEPROM.write(DirecionEspera, Valor);
    Serial.print("v/");
    Serial.println(Valor);
    return;
  }


  int IDMotor = Tipo.toInt();

  int Posicion = constrain(Valor, 0, 180);

  if (IDMotor >= CantidadMotores) return;

  Motores[IDMotor].PosicionDeseada = constrain(Posicion, Motores[IDMotor].PosicionMinima, Motores[IDMotor].PosicionMaxima);

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

        Serial.print(i);
        Serial.print("/");
        Serial.println(Motores[i].PosicionActual);

        Motores[i].Motor.write(Motores[i].PosicionActual);
      }
    }
  }
}

void ReutinaDescanso() {
  for (int i = 0; i < CantidadMotores; i++) {
    Motores[i].PosicionDeseada = Motores[i].PosicionDescanso;
  }
}

boolean MensajeConfiguracion(String Mensaje) {
  if (Mensaje.equals("d")) {
    ReutinaDescanso();
  } else if (Mensaje.equals("v")) {
    Serial.print("v/");
    Serial.println(Esperar);
  } else if (Mensaje.equals("e")) {
    for (int i = 0; i < CantidadMotores; i++) {
      Serial.print(i);
      Serial.print("/");
      Serial.println( Motores[i].PosicionActual);
    }
  } else if (Mensaje.equals("s")) {
    for (int i = 0; i < CantidadMotores; i++) {
      Motores[i].PosicionDescanso = Motores[i].PosicionActual;d
      EEPROM.write(Motores[i].EEPRON_Descanso, Motores[i].PosicionDescanso);
    }
  }  else {
    return false;
  }
  return true;
}
