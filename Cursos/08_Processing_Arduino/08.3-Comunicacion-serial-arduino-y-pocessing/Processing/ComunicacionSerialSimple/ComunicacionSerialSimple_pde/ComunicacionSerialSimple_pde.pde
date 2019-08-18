import processing.serial.*;

Serial MiPuerto; 
color ColorCirculo = color(255, 0, 0);
color ColorFondo = color(0);

void setup() {
  //printArray(Serial.list());
  MiPuerto = new Serial(this, "/dev/ttyUSB0", 9600);
  size(400, 600);
  ellipseMode(CENTER);
}

void draw() {
  background(ColorFondo);
  fill(ColorCirculo);
  circle(200, 300, 300);
}

void mousePressed() {
  float Distancia = dist(mouseX, mouseY, 200, 200);
  if (Distancia < 150) {
    ColorCirculo = color(255, 100, 100);
    MiPuerto.write("H");
  }
}

void mouseReleased() {
  ColorCirculo = color(255, 0, 0);
  MiPuerto.write("L");
}

void serialEvent(Serial p) {
  while (MiPuerto.available() == 1) {
    char Letra = MiPuerto.readChar();
    if (Letra == 'H') {
      ColorFondo = color(255);
    } else if (Letra == 'L') {
      ColorFondo = color(0);
    }
  }
}
