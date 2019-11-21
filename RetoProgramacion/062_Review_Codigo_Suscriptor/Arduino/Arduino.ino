//encerder 4 Leds

int Led[4] = {13, 12, 11, 10};
boolean EstadoLed[4] = {false, false, false, false};

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < 4; i++) {
    pinMode(Led[i], OUTPUT);
    digitalWrite(Led[i], EstadoLed[i]);
  }
}

void loop() {

  if (Serial.available()) {
    char Letra = Serial.read();
    int Indice = -1;
    // Indice = Letra - 'a';
    if (Letra == 'a') {
      Indice = 0;
    }
    else if (Letra == 'b') {
      Indice = 1;
    }
    else  if (Letra == 'c') {
      Indice = 2;
    }
    else if (Letra == 'd') {
      Indice = 3;
    }
    if (Indice > -1) {
      EstadoLed[Indice] = !EstadoLed[Indice];
      digitalWrite(Led[Indice], EstadoLed[Indice]);
    }
  }
}
