#define cantidadLed 5

struct led {
  int pin;
  bool estado;
  long tiempo;
  long ultimo;
};

led leds[cantidadLed] = {
  { 2, false, 300 },
  { 3, false, 1000 },
  { 4, false, 400 },
  { 5, false, 1500 },
  { 6, false, 1200 }
};


void setup() {
  Serial.begin(9600);
  for (int i = 0; i < cantidadLed; i++) {
    pinMode(leds[i].pin, OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < cantidadLed; i++) {
    actualizarLed(leds[i]);
  }
}


void actualizarLed(led &ledActual) {
  float tiempoActual = millis();

  if (tiempoActual - ledActual.ultimo > ledActual.tiempo) {
    ledActual.ultimo = tiempoActual;
    ledActual.estado = !ledActual.estado;
    ;
    if (ledActual.estado) {
      digitalWrite(ledActual.pin, HIGH);
    } else {
      digitalWrite(ledActual.pin, LOW);
    }
  }
}
