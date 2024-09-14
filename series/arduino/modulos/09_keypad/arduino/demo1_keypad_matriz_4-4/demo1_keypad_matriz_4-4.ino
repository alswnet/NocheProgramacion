#include <Keypad.h>

#define filas 4
#define columnas 4

byte pinesFilas[filas] = { 9, 8, 7, 6 };
byte pinesColumnas[columnas] = { 5, 4, 3, 2 };

char signos[filas][columnas] = {
  { '1', '4', '7', '*' },
  { '2', '5', '8', '0' },
  { '3', '6', '9', '#' },
  { 'A', 'B', 'C', 'D' }
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
