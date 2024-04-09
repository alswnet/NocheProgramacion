void setup() {
  Serial.begin(9600);

  boolean estado = true;
  String Mensaje = "";

  Serial.print("Estado: ");

  // if (estado) {
  //   Mensaje = "Encendido";
  // } else {
  //   Mensaje = "Apagado";
  // }

  Mensaje = estado ? "Encendido" : "Apagado";

  Serial.println(Mensaje);
}

void loop() {
}
