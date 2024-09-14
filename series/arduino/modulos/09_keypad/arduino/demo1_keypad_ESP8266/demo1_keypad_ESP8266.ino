#include <Keypad.h>

#define filas 4
#define columnas 4

byte pinesFilas[filas] = { D4, D5, D6, D7 };        //2, 14, 12, 13
byte pinesColumnas[columnas] = { D0, D1, D2, D3 };  // 16, 5, 4, 0

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