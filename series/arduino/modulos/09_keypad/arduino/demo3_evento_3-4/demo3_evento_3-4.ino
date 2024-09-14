
#include <Keypad.h>

#define filas 4
#define columnas 3

byte pinesFilas[filas] = { 9, 8, 7, 6 };
byte pinesColumnas[columnas] = { 5, 4, 3 };

char signos[filas][columnas] = {
  { '1', '2', '3' },
  { '4', '5', '6' },
  { '7', '8', '9' },
  { '*', '0', '#' }
};

Keypad teclado = Keypad(makeKeymap(signos), pinesFilas, pinesColumnas, filas, columnas);

int pinLed = 13;

boolean estado = true;
boolean estadoLed = false;

void setup() {
  Serial.begin(9600);
  pinMode(pinLed, OUTPUT);
  digitalWrite(pinLed, HIGH);
  teclado.begin(makeKeymap(signos));
  teclado.addEventListener(eventoTeclado);
  char tecla = teclado.getKey();
}

void loop() {
  char tecla = teclado.getKey();
  if (estado) {
    digitalWrite(pinLed, !estadoLed);
    estadoLed = !estadoLed;
    delay(250);
  }
}

void eventoTeclado(KeypadEvent tecla) {
  Serial.print("Tecla: ");
  Serial.println(tecla);

  if (teclado.getState() == PRESSED) {
    if (tecla == '#') {
      estado = true;
    } else if (tecla == '*') {
      estado = false;
    }
  }
}
