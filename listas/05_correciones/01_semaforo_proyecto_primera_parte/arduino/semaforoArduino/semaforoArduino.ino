#include <EEPROM.h>

#define CantidadLed 3
int Led[CantidadLed] = {5, 4, 13};
int Espera[CantidadLed] = {10, 8, 2};
String ColorSemaforo[CantidadLed] = {"Rojo", "Verde", "Amarillo"};

#define Rojo 0
#define Verde 1
#define Amarillo 2

int Estado;
float TiempoPasado = 0;
float TiempoEspera;
boolean Pausado = false;

boolean Intermitente = false;
boolean LedIntermitente = false;


void setup() {
  Serial.begin(9600);
  for (int i = 0; i < CantidadLed; i++) {
    pinMode(Led[i], OUTPUT);
  }
  Estado = Rojo;
  TiempoEspera = Espera[Estado];

  Serial.println("Cargando tiempo de espera");
  for (int i = 0 ; i < CantidadLed ; i++) {
    Espera[i] = EEPROM.read(i);
    Serial.print(ColorSemaforo[i]);
    Serial.print(" - ");
    Serial.println(Espera[i]);
  }
}

void loop() {
  if (Serial.available()) {
    DecodificarSerial();
  }

  if (Intermitente) {
    SemaforoIntermitente();
    return;
  }

  if (!Pausado) {
    ActualizarTiempo();
  }
  ActualizarSemaforo();
}

void ActualizarTiempo() {
  if (millis() - TiempoPasado > TiempoEspera * 1000) {
    TiempoPasado = millis();
    Estado++;
    if (Estado >  Amarillo) {
      Estado = Rojo;
    }
    TiempoEspera = Espera[Estado];
    Serial.print("Cambiando a ");
    Serial.print(ColorSemaforo[Estado]);
    Serial.print(" ");
    Serial.print(TiempoEspera);
    Serial.println("s");
  }
}

void ActualizarSemaforo() {
  for (int i = 0; i < CantidadLed; i++) {
    if (i == Estado) {
      digitalWrite(Led[i], HIGH);
    } else {
      digitalWrite(Led[i], LOW);
    }
  }
}

void SemaforoIntermitente() {
  for (int i = 0; i < CantidadLed; i++) {
    if (i != Amarillo) {
      digitalWrite(Led[i], LOW);
    }
  }

  if (millis() - TiempoPasado > 500) {
    TiempoPasado = millis();
    LedIntermitente = !LedIntermitente;
    if (LedIntermitente) {
      digitalWrite(Led[Amarillo], HIGH);
    } else {
      digitalWrite(Led[Amarillo], LOW);
    }
  }
}

void DecodificarSerial() {
  // e/[0-2]\n
  // e - estado
  // numero es el estao actual

  // i/ 
  // cambiar intermitente

  // p/
  // cambiar pausar

  // r/[0-2]/t
  // cambia tiempo de retraso en segundos
  // t es segundos

  String Mensaje = Serial.readStringUntil('\n');
  Serial.print("Mensaje : ");
  Serial.println(Mensaje);
  int PosicionPleca = Mensaje.indexOf('/');
  int PosicionSaltoLinea = Mensaje.length();

  String TipoMensaje = Mensaje.substring(0, PosicionPleca);

  if (TipoMensaje.equals("e") or TipoMensaje.equals("E")) {
    Estado = Mensaje.substring(PosicionPleca + 1, PosicionSaltoLinea).toInt();
    Serial.print("Estado a ");
    Serial.println(ColorSemaforo[Estado]);
  } else if (TipoMensaje.equals("r") or TipoMensaje.equals("R")) {
    int PosicionPleca2 = Mensaje.indexOf('/', PosicionPleca + 1);
    int cambio = Mensaje.substring(PosicionPleca + 1, PosicionPleca2).toInt();
    int tiempo = Mensaje.substring(PosicionPleca2 + 1, PosicionSaltoLinea).toInt();
    if (cambio >= CantidadLed)
      return;
    Espera[cambio] = tiempo;
    Serial.print("Cambiando retrado ");
    Serial.print(ColorSemaforo[cambio]);
    Serial.print(" - ");
    Serial.print(Espera[cambio]);
    Serial.println("s");
    EEPROM.write(cambio, tiempo);
  } else if (TipoMensaje.equals("p") or TipoMensaje.equals("P")) {
    Pausado = !Pausado;
    Serial.print("Pausado sistema ");
    Serial.println(Pausado);
  } else if (TipoMensaje.equals("i") or TipoMensaje.equals("I")) {
    Intermitente = !Intermitente;
    Serial.print("Intermitente ");
    Serial.println(Intermitente);
  }
}