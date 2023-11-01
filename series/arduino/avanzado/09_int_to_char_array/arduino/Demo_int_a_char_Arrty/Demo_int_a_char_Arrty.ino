#define tamannoMaximo 5

void setup() {
  Serial.begin(9600);

  int numeroEntero = 1234;
  char textoChar[tamannoMaximo];

  String textoString = String(numeroEntero);
  textoString.toCharArray(textoChar, tamannoMaximo);

  Serial.println();
  Serial.println(textoChar);

}

void loop() {
 
}
