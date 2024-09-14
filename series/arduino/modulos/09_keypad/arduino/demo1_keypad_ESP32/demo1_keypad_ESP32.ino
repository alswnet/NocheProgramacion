#include <Keypad.h>

#define filas 4
#define columnas 4

byte pinesFilas[filas] = { 16, 4, 2, 15 };
byte pinesColumnas[columnas] = { 19, 18, 5, 17 };

char signos[filas][columnas] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

Keypad teclado = Keypad(makeKeymap(signos), pinesFilas, pinesColumnas, filas, columnas);

void setup() {
  Serial.begin(115200);
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