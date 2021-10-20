int Boton1 = 2;
int Boton2 = 3;
int Boton3 = 4;

void setup() {
  Serial.begin(9600);
  pinMode(Boton1, INPUT);
  pinMode(Boton2, INPUT);
  pinMode(Boton3, INPUT);
}

void loop() {
  int Estado1 = digitalRead(Boton1) * 3;
  int Estado2 = digitalRead(Boton2) * 4;
  int Estado3 = digitalRead(Boton3) * 5;

  Serial.print(Estado1);
  Serial.print(",");
  Serial.print(Estado2);
  Serial.print(",");
  Serial.print(Estado3);
  Serial.println();
  delay(100);
}
