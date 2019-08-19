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
  String[] PaqueteMensaje =  splitTokens(Mensaje, "/");
  if (PaqueteMensaje[0].equals("D1")) {
    println("La distancia 1 es : "+ PaqueteMensaje[1]);
  } else if (PaqueteMensaje[0].equals("D2")) {
    println("La distancia 2 es : "+ PaqueteMensaje[1]);
  }
  //printArray(PaqueteMensaje);
}
