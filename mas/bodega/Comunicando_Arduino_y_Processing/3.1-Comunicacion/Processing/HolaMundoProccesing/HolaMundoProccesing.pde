// Creado ChepeCarlos de ALSW
// Tutorial Completo en https://nocheprogramacion.com
// Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

import processing.serial.*;

boolean EstadoBoton = false;
Serial MiSerial;
color ColorApagado = color(200, 0, 0);
color ColorEncendido = color(0, 200, 0);
void setup() {
  size(400, 600);
  String NombrePuerto ="/dev/ttyUSB0";
  MiSerial = new Serial(this, NombrePuerto, 9600);
}

void draw() {
  background(255);
  if (EstadoBoton) {
    fill(ColorEncendido);
  } else {
    fill(ColorApagado);
  }
  ellipse(200, 200, 350, 350);
}

void mouseClicked() {
  float distancia = dist(200, 200, mouseX, mouseY);
  if (distancia < 175) {
    EstadoBoton = !EstadoBoton;
    MiSerial.write('a');
  }
}