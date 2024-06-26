#include <Arduino.h>
#include <KeyboardDevice.h>
#include <BleCompositeHID.h>

BleCompositeHID dispositivoBLE("ESP32 Teclado", "chepecarlos", 100);  //Nombre, Fabricante, Bateria
KeyboardDevice* teclado;
int boton = 15;

void setup() {
  Serial.begin(115200);
  pinMode(boton, INPUT);

  KeyboardConfiguration configuracion;
  configuracion.setUseMediaKeys(true);

  teclado = new KeyboardDevice(configuracion);
  dispositivoBLE.addDevice(teclado);
  dispositivoBLE.begin();

  Serial.println("Conectate con el dispositivo");
  delay(3000);
}

void loop() {
  if (dispositivoBLE.isConnected()) {
    bool estado = digitalRead(boton);
    if (estado) {
      Serial.println("Precionando la tecla");
      teclado->mediaKeyPress(KEY_MEDIA_PLAYPAUSE);
      delay(50);
      teclado->mediaKeyRelease(KEY_MEDIA_PLAYPAUSE);
      delay(1000);
    }
  }
}
