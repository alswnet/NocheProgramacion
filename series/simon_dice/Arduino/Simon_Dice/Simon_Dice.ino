
#define Iniciando 0
#define Animacion 1
#define Esperando 2
#define Calcular 3
#define SiquienteRonda 3
#define Perder 4
#define Ganar 5

int Led[] = {2, 4, 6, 8};
int Boton[] = {3, 5, 7, 9};
int Tonos[] = {262, 330, 392, 494};
int Cantidad = 4;

int Buzzer = 10;
int Estado = Iniciando;

int PinVelocidad = A0;
int VelocidadMinima = 100;
int VelocidadMaxima = 2000;

int Espera = 400;

#define RondaGanar 3
int Secuencias[RondaGanar];
int Ronda = 0;
int I_Ronda = 0;
int I_Animacion = 0;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < Cantidad; i++) {
    pinMode(Boton[i], INPUT_PULLUP);
    pinMode(Led[i], OUTPUT);
  }
  pinMode(Buzzer, OUTPUT);
  pinMode(PinVelocidad, INPUT);
}

void loop() {
  int Boton_ID = LeerBotones();
  int Espera = LeerVelocidad();
  switch (Estado) {
    case Iniciando:
      GenerarSecuencia(Espera);
      Ronda = 0;
      I_Ronda = 0;
      Estado = Animacion;
      I_Animacion = 0;
      delay(300);
      break;
    case Animacion:
      {
        delay(Espera / 2);
        EncenderLed(Secuencias[I_Animacion]);
        delay(Espera);
        ApagarLed(Secuencias[I_Animacion]);
        Serial.print("R");
        Serial.print(I_Animacion);
        Serial.print(" - ");
        Serial.println(Secuencias[I_Animacion]);
        I_Animacion++;
        if ( I_Animacion > Ronda) {
          Estado = Esperando;
          I_Animacion = 0;
        }
      }
      break;
    case Esperando:
      Estado_Esperando(Boton_ID, Espera);
      break;
    case SiquienteRonda:
      Ronda++;
      I_Ronda = 0;
      Serial.print("Ronda:");
      Serial.println(Ronda + 1);

      if (Ronda >= RondaGanar) {

        Estado = Ganar;
        return;
      }
      Estado = Animacion;
      break;
    case Perder:
      Serial.print("Perdio en ");
      Serial.println(Ronda);
      SecuenciaPerder(Espera);
      SecuenciaPerder(Espera);
      Estado = Iniciando;
      break;
    case Ganar:
      Serial.println("Ganaste :D");
      Estado = Iniciando;
      break;
    default:
      Estado = Iniciando;
      break;
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

int LeerVelocidad() {
  int Valor = analogRead(PinVelocidad);
  Valor = map(Valor, 0, 1023, VelocidadMinima, VelocidadMaxima);
  Valor = constrain(Valor, VelocidadMinima, VelocidadMaxima);
  return Valor;
}

void EncenderLed(int ID_Led) {
  digitalWrite(Led[ID_Led], HIGH);
  tone(Buzzer, Tonos[ID_Led]);
}

void ApagarLed(int ID_Led) {
  digitalWrite(Led[ID_Led], LOW);
  noTone(Buzzer);
}

void GenerarSecuencia(int Velocidad) {
  randomSeed(analogRead(A1));

  for (int i = 0; i < RondaGanar; i++) {
    Secuencias[i] = round(random(0, Cantidad));
  }

  SecuenciaLed(Velocidad);
}

void SecuenciaLed(int Velocidad) {
  for (int i = 0; i < Cantidad; i++) {
    EncenderLed(i);
    delay(Velocidad);
    ApagarLed(i);
    noTone(Buzzer);
  }

  for (int i = Cantidad - 1; i >= 0; i--) {
    EncenderLed(i);
    delay(Velocidad);
    ApagarLed(i);
    noTone(Buzzer);
  }
}

void SecuenciaPerder(int Velocidad) {
  for (int i = 0; i < Cantidad; i++) {
    EncenderLed(i);
  }
  delay(Velocidad);
  for (int i = 0; i < Cantidad; i++) {
    ApagarLed(i);
    noTone(Buzzer);
  }
}

void Estado_Esperando(int Boton_ID, int Espera) {
  if (Boton_ID < 0) return;
  EncenderLed(Boton_ID);
  delay(Espera);
  while (Boton_ID == LeerBotones()) {
    Serial.print(".");
    delay(25);
  }
  ApagarLed(Boton_ID);
  Serial.print("I:");
  Serial.print(I_Ronda);
  Serial.print(" S:");
  Serial.print(Secuencias[I_Ronda]);
  Serial.print(" B:");
  Serial.print(Boton_ID);
  Serial.print(" R:");
  Serial.println(Ronda);
  if ( Secuencias[I_Ronda] == Boton_ID ) {
    if (I_Ronda >= Ronda) {
      Estado = SiquienteRonda;
    }
    else {
      Estado = Esperando;
      I_Ronda++;
    }

  } else {
    Estado = Perder;
  }
}
