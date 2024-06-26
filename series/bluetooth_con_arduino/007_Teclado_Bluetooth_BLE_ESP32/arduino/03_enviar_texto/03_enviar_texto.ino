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
      Serial.println("Subcribete a ChepeCarlos");
      enviarTecto("Subcribete a ChepeCarlos");
      precionarTecla(KEY_ENTER);
      delay(1000);
    }
  }
}

void enviarTecto(const char* texto) {
  int longitud = strlen(texto);
  for (int i = 0; i < longitud; i++) {
    uint8_t letra = (uint8_t)texto[i];
    bool mayuscula = false;
    
    if (letra == (uint8_t)' ') {
      letra = KEY_SPACE;
    } else if (letra >= (uint8_t)'A' and letra <= (uint8_t)'Z') {
      letra = letra - (uint8_t)'A' + KEY_A;
      mayuscula = true;
    } else if (letra >= (uint8_t)'a' and letra <= (uint8_t)'z') {
      letra = letra - (uint8_t)'a' + KEY_A;
    } else {
      continue;
    }

    if (mayuscula) {
      teclado->modifierKeyPress(KEY_MOD_LSHIFT);
    }
    teclado->keyPress(letra);
    delay(10);
    teclado->keyRelease(letra);
    delay(10);
    if (mayuscula) {
      teclado->modifierKeyRelease(KEY_MOD_LSHIFT);
    }
  }
}


void precionarTecla(uint32_t keyCode) {
  Serial.println("Presionando Tecla: " + String(keyCode));
  teclado->keyPress(keyCode);
  delay(10);
  teclado->keyRelease(keyCode);
  delay(10);
}