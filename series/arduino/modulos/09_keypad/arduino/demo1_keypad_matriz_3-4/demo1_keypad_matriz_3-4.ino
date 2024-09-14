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

void setup() {
  Serial.begin(9600);
  Serial.println("Iniciando Teclado 4x4 con Libreria Keypad");
  Serial.println();
}

void loop() {
  char tecla = teclado.getKey();

  if (tecla) {
    Serial.print("Tecla presionada : ");
    Serial.println(tecla);
  }
}
