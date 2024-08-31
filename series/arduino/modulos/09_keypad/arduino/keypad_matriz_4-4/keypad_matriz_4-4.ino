#include <Keypad.h>
const byte filas = 4; 
const byte columnas = 4;
byte pinesColumnas[]  = {9,8,7,6};
byte pinesFilas[] = {5,4,3,2};
char teclas[4][4] = {{'1','2','3','A'},
                     {'4','5','6','B'},
                     {'7','8','9','C'},
                     {'*','0','#','D'}};
Keypad teclado1 = Keypad( makeKeymap(teclas), pinesFilas, pinesColumnas, filas, columnas);  
void setup() {
  Serial.begin(9600);
  Serial.println("Teclado 4x4 con Libreria Keypad");
  Serial.println();
}
void loop() {
  //Verifica si alguna tecla fue presionada
  char tecla_presionada = teclado1.getKey();
  
  //Monitor Serial
  if (tecla_presionada)
  {
    Serial.print("Tecla: ");
    Serial.println(tecla_presionada);
  } 
}
