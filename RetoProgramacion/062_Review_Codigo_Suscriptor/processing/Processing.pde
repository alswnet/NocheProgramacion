// Creado ChepeCarlos de ALSW
// Tutorial Completo en https://nocheprogramacion.com
// Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

import processing.serial.*;

boolean[] EstadoBoton = {false, false, false, false};
Serial MiSerial;
color ColorApagado = color(200, 0, 0);
color ColorEncendido = color(0, 200, 0);
int RadioBoton = 40;

void setup() {

  size(800, 400);
  String NombrePuerto ="/dev/ttyUSB0";
  MiSerial = new Serial(this, NombrePuerto, 9600);
}

void draw() {
  background(255);
  DibujarBoton(50, 50, EstadoBoton[0]);
  DibujarBoton(200, 50, EstadoBoton[1]);
  DibujarBoton(50, 200, EstadoBoton[2]);
  DibujarBoton(200, 200, EstadoBoton[3]);
}

void mouseClicked() {
  PrecionarBoton(50, 50, 0, 'a');
  PrecionarBoton(200, 50, 1, 'b');
  PrecionarBoton(50, 200, 2, 'c');
  PrecionarBoton(200, 200, 3, 'e');
}

void DibujarBoton(int x, int y, boolean Estado) {
  if (Estado) {
    fill(ColorEncendido);
  } else {
    fill(ColorApagado);
  }
  ellipse(x, y, RadioBoton*2, RadioBoton*2);
}
void PrecionarBoton(int x, int y, int Indice, char Letra) {
  float d = dist(x, y, mouseX, mouseY);
  if (d < RadioBoton) {
    EstadoBoton[Indice] = !EstadoBoton[Indice];
    MiSerial.write(Letra);
  }
}
