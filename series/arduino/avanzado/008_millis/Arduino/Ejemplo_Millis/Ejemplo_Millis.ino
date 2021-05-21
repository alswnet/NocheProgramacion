int Led = 3;
float Espera = 3000;
float TiempoAnterior = 0;
boolean EstadoLed = false;

void setup() {
  pinMode(Led, OUTPUT);
}

void loop() {
  float TiempoActual = millis();

  if (TiempoActual - TiempoAnterior > Espera) {
    TiempoAnterior = TiempoActual;
    EstadoLed = ! EstadoLed;
    if (EstadoLed) {
      digitalWrite(Led, 1);
    }
    else {
      digitalWrite(Led, 0);
    }
  }
}
