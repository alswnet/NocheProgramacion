// Creado ChepeCarlos de ALSW
// Tutorial Completo en https://nocheprogramacion.com
// Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

void Estado = true;

void setup() {
  Serial.begin(9600);
  Serial.println("Inciando programa:");
}

void loop() {
  Estado = !Estado;

  Serial.println(Estado ? "Encender": "Apagado");
}
