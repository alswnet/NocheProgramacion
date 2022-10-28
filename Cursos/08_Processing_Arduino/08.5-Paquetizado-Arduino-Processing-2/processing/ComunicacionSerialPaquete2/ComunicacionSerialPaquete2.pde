// Creado ChepeCarlos de ALSW
// Tutorial Completo en https://nocheprogramacion.com
// Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

import processing.serial.*;

Serial MiPuerto;
float D1, D2;
float M1, M2;

void setup() {
  //printArray(Serial.list());
  MiPuerto = new Serial(this, "/dev/ttyUSB0", 9600);
  MiPuerto.bufferUntil('\n');
  size(400, 600);
  ellipseMode(CENTER);
  M1 = 50;
  M2 = 50;
}

void draw() {
  background(0);
  fill(255, 255, 0);
  float PM1 = map(M1, 0, 100, 0, height);
  ellipse(width/4, PM1, width/4, width/4);
  float PM2 = map(M2, 0, 100, 0, height);
  ellipse((3*width)/4, PM2, width/4, width/4);
}

void mousePressed() {
  MoverCirculo();
}

void mouseDragged() {
  MoverCirculo();
}

void MoverCirculo() {
  if (mouseX<width/2) {
    M1 = map(mouseY, 0, height, 0, 100);
    MiPuerto.write("M1/"+M1+"\n");
  } else {
    M2 = map(mouseY, 0, height, 0, 100);
    MiPuerto.write("M2/"+M2+"\n");
  }
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
