#include <Wire.h>//Include the Wire library to talk I2C

#define MCP4725_ADDR 0x60

float x = 0.0;
float y = 0.0;

boolean pendiente = true;

int salida = 0;

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop () {
  if (pendiente) {
    y++;
    if (y >= 200) {
      pendiente = false;
    }
  }
  else {
    y--;
    if (y <= 0) {
      pendiente = true;
    }
  }
  Salida = y;
  Wire.beginTransmission(MCP4725_ADDR);
  Wire.write(64);                     // cmd to update the DAC
  Wire.write(salida >> 4);        // the 8 most significant bits...
  Wire.write((salida & 15) << 4); // the 4 least significant bits...
  Wire.endTransmission();
  delay(1 * int(analogRead(A2)));
  Serial.println(salida);
}

