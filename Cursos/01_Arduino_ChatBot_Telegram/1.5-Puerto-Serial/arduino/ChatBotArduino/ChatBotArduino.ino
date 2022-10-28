// Creado ChepeCarlos de ALSW
// Tutorial Completo en https://nocheprogramacion.com
// Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

int Boton = 2;
int Led = 9;

void setup() {
  Serial.begin(9600);
  pinMode(Boton, INPUT_PULLUP);
  pinMode(Led, OUTPUT);
}

void loop() {
  if (digitalRead(Boton) == 0) {
    Serial.println("H");
    delay(500);
  }

  if (Serial.available()) {
    char Letra = Serial.read();
    if (Letra == 'H') {
      digitalWrite(Led, HIGH);
    }
    else if (Letra == 'L') {
      digitalWrite(Led, LOW);
    }
  }
}
