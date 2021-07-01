// Creado ChepeCarlos de ALSW
// Tutorial Completo en https://nocheprogramacion.com
// Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

import processing.serial.*;

Serial MiPuerto;
float D1, D2;

void setup() {
  //printArray(Serial.list());
  MiPuerto = new Serial(this, "/dev/ttyUSB0", 9600);
  MiPuerto.bufferUntil('\n');
  size(400, 600);
  ellipseMode(CENTER);
}

void draw() {
}

void serialEvent(Serial p) {
  String Mensaje = MiPuerto.readString();
  String[] PaqueteMensaje =  splitTokens(Mensaje, "/\n\r");
  if (PaqueteMensaje[0].equals("D1")) {
    println("La distancia 1 es : "+ int(PaqueteMensaje[1]));
    D1  = int(PaqueteMensaje[1]);
  } else if (PaqueteMensaje[0].equals("D2")) {
    println("La distancia 2 es : "+ int(PaqueteMensaje[1]));
    D2  = int(PaqueteMensaje[1]);
  }
  //printArray(PaqueteMensaje);
}
