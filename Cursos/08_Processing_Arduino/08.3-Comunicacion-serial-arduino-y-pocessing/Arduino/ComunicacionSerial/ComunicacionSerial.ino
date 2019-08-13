int Led = 13;
int Boton = 8;
boolean EstadoBoton = false;

void setup() {
  Serial.begin(9600);
  pinMode(Led, OUTPUT);
  pinMode(Boton, INPUT);
}

void loop() {
  if (Serial.available()) {
    char Letra = Serial.read();
    if (Letra == 'H') {
      digitalWrite(Led, 1);
    }
    else if (Letra == 'L') {
      digitalWrite(Led, 0);
    }
  }

  if (digitalRead(Boton) == 1 && EstadoBoton == false) {
    Serial.println('H');
    EstadoBoton = true;
  }
  else if (digitalRead(Boton) == 0 && EstadoBoton == true) {
    Serial.println('L');
    EstadoBoton = false;
  }
  delay(100);
}
