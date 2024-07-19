#include <Arduino.h>

#include <BleCompositeHID.h>
#include <MouseDevice.h>

MouseDevice* raton;
BleCompositeHID dispositivoBLE("ESP32 Raton", "chepecarlos", 100);  //Nombre, Fabricante, Bateria

int botonDerecha = 22;
int botonIzquierda = 23;
int botonArriba = 19;
int botonAbajo = 21;

void setup() {
  Serial.begin(115200);

  pinMode(botonDerecha, INPUT);
  pinMode(botonIzquierda, INPUT);
  pinMode(botonArriba, INPUT);
  pinMode(botonAbajo, INPUT);

  raton = new MouseDevice();
  dispositivoBLE.addDevice(raton);
  dispositivoBLE.begin();

  Serial.println("Conéctate con el dispositivo");
  delay(3000);
}

void loop() {
  if (dispositivoBLE.isConnected()) {
    int x = 0;
    int y = 0;
    if (digitalRead(botonDerecha)) {
      x = 20;
    } else if (digitalRead(botonIzquierda)) {
      x = -20;
    }
    if (digitalRead(botonArriba)) {
      y = 20;
    } else if (digitalRead(botonAbajo)) {
      y = -20;
    }
    Serial.print("Valor: ");
    Serial.print(x);
    Serial.print(" ");
    Serial.println(y);
    raton->mouseMove(x, y);
    raton->sendMouseReport();
    delay(100);
  }
}
