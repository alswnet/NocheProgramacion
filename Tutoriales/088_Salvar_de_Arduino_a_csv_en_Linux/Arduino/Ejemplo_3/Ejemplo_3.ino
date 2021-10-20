int Boton = 2;
float PosicionActual = 0;
float PosicionDeseada = 0;

void setup() {
  Serial.begin(9600);
  pinMode(Boton, INPUT);
}

void loop() {
  int PosicionDeseada = digitalRead(Boton) * 180;
  PosicionActual = (0.05 * PosicionDeseada) + (0.95 * PosicionActual);

  Serial.print(millis());
  Serial.print(",");
  Serial.print(PosicionActual);
  Serial.print(",");
  Serial.print(PosicionDeseada);
  Serial.println();
  delay(100);
}
