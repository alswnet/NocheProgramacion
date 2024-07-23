#include <Arduino.h>
#include <BleCompositeHID.h>
#include <MouseDevice.h>

MouseDevice* raton;
BleCompositeHID dispositivoBLE("ESP32 Raton", "chepecarlos", 100);  //Nombre, Fabricante, Bateria

int botonDerecha = 22;
int botonIzquierda = 23;
int botonArriba = 19;
int botonAbajo = 21;

int botonPrincipal = 5;
int botonMedio = 17;
int botonSecundario = 16;

bool estadoBoton = false;
bool estadoBotonAnterior = false;

void setup() {
  Serial.begin(115200);

  pinMode(botonDerecha, INPUT);
  pinMode(botonIzquierda, INPUT);
  pinMode(botonArriba, INPUT);
  pinMode(botonAbajo, INPUT);

  pinMode(botonPrincipal, INPUT);
  pinMode(botonMedio, INPUT);
  pinMode(botonSecundario, INPUT);

  raton = new MouseDevice();
  dispositivoBLE.addDevice(raton);
  dispositivoBLE.begin();

  Serial.println("Conectate con el dispositivo");
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

    if (digitalRead(botonSecundario)) {
      raton->mousePress(MOUSE_LOGICAL_RIGHT_BUTTON);
      delay(200);
      raton->mouseRelease(MOUSE_LOGICAL_RIGHT_BUTTON);
    }

    if (digitalRead(botonMedio)) {
      raton->mousePress(MOUSE_LOGICAL_BUTTON_3);
      delay(200);
      raton->mouseRelease(MOUSE_LOGICAL_BUTTON_3);
    }

    if (digitalRead(botonPrincipal)) {
      estadoBoton = true;
    } else {
      estadoBoton = false;
    }

    if (estadoBoton != estadoBotonAnterior) {
      if (estadoBoton) {
        raton->mousePress(MOUSE_LOGICAL_LEFT_BUTTON);
      } else {
        raton->mouseRelease(MOUSE_LOGICAL_LEFT_BUTTON);
      }
      Serial.print("Boton 1:");
      Serial.println(estadoBoton);
      estadoBotonAnterior = estadoBoton;
    }

    raton->mouseMove(x, y);
    raton->sendMouseReport();
    delay(100);
  }
}
