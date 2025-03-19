int led1 = 13;
int led2 = 12;
int boton = 2;

bool estadoLed1 = false;
bool estadoLed2 = false;
long inicioTiempo = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Iniciando Sistema");
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(boton, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(boton) == 0) {
    Serial.print("Precionando Boton");
    inicioTiempo = millis();
    delay(100);
    while (digitalRead(boton) == 0) {
      delay(100);
      Serial.print(".");
    }
    Serial.println();

    if (millis() - inicioTiempo > 3000) {
      estadoLed2 = !estadoLed2;
    } else if (millis() - inicioTiempo < 500) {
      estadoLed1 = !estadoLed1;
    }

    float Precionando = float(millis() - inicioTiempo) / 1000;


    Serial.print("Estado:");
    Serial.print(estadoLed1);
    Serial.print(" - ");
    Serial.println(estadoLed2);
    Serial.print("Precionado: ");
    Serial.print(Precionando);
    Serial.println(" s");
  }

  digitalWrite(led1, estadoLed1);
  digitalWrite(led2, estadoLed2);
}
