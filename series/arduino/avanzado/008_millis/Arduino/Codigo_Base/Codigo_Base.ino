#define Derecha 1
#define Izquierda -1

int CanitdadLed = 10;
int LedInicial = 3;

int LedActual = LedInicial;
int Direcion = Derecha;

int Esperar = 100;
int Boton = 2;
boolean Estado = true;

float TiempoAnterior = 0;

void setup() {
  Serial.begin(9600);
  pinMode(Boton, INPUT);
  for (int i = LedInicial ; i < CanitdadLed + LedInicial ; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  ActualizarBoton();
  ActualizarLed();
}

void ActualizarBoton() {
  if (digitalRead(Boton)) {
    Estado = !Estado;
    Serial.print("Cambiando estado ");
    Serial.println(Estado);
    delay(400);
  }
}

void ActualizarLed() {
  if (Estado) {
    float TiempoActual = millis();
    if (TiempoActual - TiempoAnterior > Esperar) {
      TiempoAnterior = TiempoActual;
      digitalWrite(LedActual, LOW);
      LedActual += Direcion;
      if (LedActual >= LedInicial + CanitdadLed) {
        Direcion = Izquierda;
      } else if (LedActual <= LedInicial) {
        Direcion = Derecha;
      }
      digitalWrite(LedActual, HIGH);
    }
  }
}
