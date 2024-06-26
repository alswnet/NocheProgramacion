#include <Arduino.h>
#include <KeyboardDevice.h>
#include <BleCompositeHID.h>

BleCompositeHID dispositivoBLE("ESP32 Teclado", "chepecarlos", 100);  //Nombre, Fabricante, Bateria
KeyboardDevice* teclado;
int boton = 15;

void setup() {
  Serial.begin(115200);
  pinMode(boton, INPUT);

  teclado = new KeyboardDevice();
  dispositivoBLE.addDevice(teclado);
  dispositivoBLE.begin();

  Serial.println("Conectate con el dispositivo");
  delay(3000);
}

void loop() {
  if (dispositivoBLE.isConnected()) {
    bool estado = digitalRead(boton);
    if (estado) {
      teclado->keyPress(KEY_A);
      delay(10);
      teclado->keyRelease(KEY_A);
      delay(500);
    }
  }
}
