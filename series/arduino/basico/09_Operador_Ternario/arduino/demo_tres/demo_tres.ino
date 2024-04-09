void setup() {
  Serial.begin(9600);
}

void loop() {
  boolean Encendido = true;

  String Mensaje;

  if (Encendido) {
    Mensaje = "Encendido";
  }
  else {
    Mensaje = "Apagado";
  }

  Mensaje = Encendido ? "Encendido" : "Apagado";
}
