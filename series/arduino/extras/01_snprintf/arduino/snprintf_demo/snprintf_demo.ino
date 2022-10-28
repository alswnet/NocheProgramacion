// Creado ChepeCarlos
// Tutorial Completo en https://nocheprogramacion.com
// Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

void setup() {
  Serial.begin(115200);
  Serial.println();

  char mensaje[100];

  int entero = 7;
  float decimal = 456.123;
  String nombre = "Aura";
  int edad = 33;
  
  snprintf(mensaje, 100, "Entero: %d Decimal: %f", entero, decimal);
  Serial.println(mensaje);

  snprintf(mensaje, sizeof(mensaje), "Formato decimal f: %f: .2f: %.2f e: %e", decimal, decimal, decimal );
  Serial.println(mensaje);

  int Longitud;
  Longitud = snprintf( mensaje, sizeof(mensaje), "Formato decimal f: %f: .2f: %.2f e: %e", decimal, decimal, decimal );
  Serial.println(Longitud);

  snprintf(mensaje, 100, "Amo a %s texto", nombre);
  Serial.println(mensaje);

  // {"nombre": "Aura", "edad": 33}
  snprintf(mensaje, 100, "{\"nombre\":\"%s\", \"edad\":%d}", nombre, entero);
  Serial.println(mensaje);

  delay(100);
  char mensaje2[15];
  snprintf(mensaje2, 15, "Mensaje secreto, Dale like al video");
  Serial.println(mensaje2);


}

void loop() {

}
