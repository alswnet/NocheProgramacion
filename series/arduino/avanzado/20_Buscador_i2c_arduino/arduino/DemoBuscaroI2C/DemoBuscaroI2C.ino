
#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);
  while (!Serial);
  Serial.println("\nIniciando Escanar I2C");
}

void loop() {
  byte error, direccion;
  int cantidadDispotivos = 0;

  Serial.println("Empezar a buscar...");
  for (direccion = 1; direccion < 127; direccion++ ) {
    Wire.beginTransmission(direccion);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("Dispositivo en 0x");
      if (direccion < 16)
        Serial.print("0");
      Serial.println(direccion, HEX);
      cantidadDispotivos++;
    }
    else if (error == 4)    {
      Serial.print("Error en en direccion 0x");
      if (direccion < 16)
        Serial.print("0");
      Serial.println(direccion, HEX);
    }
  }

  if (cantidadDispotivos >> 0) {
    Serial.print("Se encontro ");
    Serial.print(cantidadDispotivos);
    Serial.print(" dispositov I2C\n");
  }
  else {
    Serial.println("No se encontro dispositivos I2C\n");
  }

  delay(5000);
}
