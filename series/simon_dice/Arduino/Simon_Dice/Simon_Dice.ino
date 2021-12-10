
#define Iniciando 0
#define Esperando 1
#define pollo 2

int Led[] = {2, 4, 6, 8};
int Boton[] = {3, 5, 7, 9};
int Tonos[] = {262, 330, 392, 494};
int Cantidad = 4;

int Buzzer = 10;
int Estado = Iniciando;

#define RondaGanar 10
int Ronda = 0;
int Secuencias[RondaGanar];

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < Cantidad; i++) {
    pinMode(Boton[i], INPUT_PULLUP);
    pinMode(Led[i], OUTPUT);
  }
  pinMode(Buzzer, OUTPUT);
}

void loop() {

  switch (Estado) {
    case Iniciando:
      GenerarSecuencia();
      Ronda = 0;
      Estado = Esperando;
      break;
    case Esperando:
      int Boton = LeerBotones();
      Serial.print("B:");
      Serial.println(Boton);

      if (Boton < 0) {
        return;
      }
      Serial.println(Boton);
      EncenderLed(Boton);
      delay(200);
      while (Boton == LeerBotones()) {
        Serial.print(".");
        delay(50);
      }
      ApagarLed(Boton);
      Estado = pollo;
      Serial.print(Estado);
      Serial.println(" a calcular");
      break;
    case pollo:
      Ronda++;
      Serial.print("R:");
      Serial.println(Ronda);
      if (Ronda >= RondaGanar) {
        Serial.println("Ganaste :D");
        Estado = Iniciando;
        return;
      }
      Estado = Esperando;
      break;
    default:
      Estado = Iniciando;
      break;
  }

  Serial.println(Estado);
  if (Estado == pollo) {
    Serial.println("Cancular");
  }

}


int LeerBotones() {
  for (int i = 0; i < Cantidad; i++) {
    if (!digitalRead(Boton[i])) {
      return i;
    }
  }
  return -1;
}

void EncenderLed(int ID_Led) {
  digitalWrite(Led[ID_Led], HIGH);
  tone(Buzzer, Tonos[ID_Led]);
}

void ApagarLed(int ID_Led) {
  digitalWrite(Led[ID_Led], LOW);
  noTone(Buzzer);
}

void GenerarSecuencia() {
  randomSeed(analogRead(A1));

  for (int i = 0; i < RondaGanar; i++) {
    Secuencias[i] = round(random(0, Cantidad));
    //    Serial.print(i);
    //    Serial.print(" ");
    //    Serial.println(Secuencias[i]);
  }

  SecuenciaLed();
  //  SecuenciaLed();
}

void SecuenciaLed() {
  for (int i = 0; i < Cantidad; i++) {
    tone(Buzzer, Tonos[i], 200);
    digitalWrite(Led[i], HIGH);
    delay(200);
    digitalWrite(Led[i], LOW);
    noTone(Buzzer);
  }

  for (int i = Cantidad - 1; i >= 0; i--) {
    tone(Buzzer, Tonos[i], 200);
    digitalWrite(Led[i], HIGH);
    delay(200);
    digitalWrite(Led[i], LOW);
    noTone(Buzzer);
  }
}
