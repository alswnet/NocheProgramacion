// Creado ChepeCarlos de ALSW
// Tutorial Completo en https://nocheprogramacion.com
// Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

import ketai.sensors.*;

KetaiSensor sensor;

float PosicionX, PosicionY;
float AreaX, AreaY;
PImage ImagenBT, ImagenAcelerometro, ImagenAyuda;
float SensorX, SensorY;
boolean ModoAcelerometro = false;

void setup() {
  fullScreen();
  orientation(PORTRAIT);

  AreaX = width;
  AreaY = height*0.90;

  PosicionX = 0;
  PosicionY = 0;

  ImagenBT = loadImage("LogoConectar.png");
  ImagenAcelerometro = loadImage("LogoAcelerometro.png");
  ImagenAyuda = loadImage("LogoAyuda.png");

  sensor = new KetaiSensor(this);
  sensor.start();
}

void draw() {
  DibujarPantalla();
  ActualizarPuntero();
}

void ActualizarPuntero() {
  if (ModoAcelerometro) {
    PosicionX = map(SensorX, -5, 5, -100, 100);
    PosicionY = map(SensorY, -5, 5, -100, 100);
  } else if (mousePressed && mouseY < AreaY) {
    PosicionX = map(mouseX, 0, AreaX, -100, 100);
    PosicionY = map(mouseY, 0, AreaY, -100, 100);
  } else {
    PosicionX = 0;
    PosicionY = 0 ;
  }

  PosicionX = constrain(PosicionX, -100, 100);
  PosicionY = constrain(PosicionY, -100, 100);
}

void DibujarPantalla() {
  float PX, PY;
  float GrosorLinea;
  float AltoBoton;

  PX = map(PosicionX, -100, 100, 0, AreaX);
  PY = map(PosicionY, -100, 100, 0, AreaY);
  GrosorLinea = map(AreaX, 1000, 5000, 10, 100);
  AltoBoton = height - AreaY;

  background(0);

  stroke(255, 0, 0);
  strokeWeight(GrosorLinea);

  line(0, PY, AreaX, PY);
  line(PX, 0, PX, AreaY);

  stroke(0, 255, 0);
  rectMode(CENTER);
  noFill();
  rect(PX, PY, AreaX/7, AreaX/7, AreaX/30);
  rectMode(CORNER);

  fill(96);
  stroke(0);
  DibujarBoton(0, AreaY, AreaX/3, AltoBoton, ImagenBT);
  DibujarBoton(AreaX/3, AreaY, AreaX/3, AltoBoton, ImagenAcelerometro);
  DibujarBoton(2*AreaX/3, AreaY, AreaX/3, AltoBoton, ImagenAyuda);
}

void DibujarBoton(float X, float Y, float Ancho, float Alto, PImage Imagen) {
  rect(X, Y, Ancho, Alto);
  imageMode(CENTER);
  image(Imagen, X+Ancho/2, Y+Alto/2, 0.8*Alto, 0.8*Alto);
}

void mousePressed() {
  float TamanoBoton = AreaX/3;
  if (mouseY > AreaY) {
    if (mouseX < TamanoBoton) {
      println("Conectar BT");
    } else if (mouseX < 2 * TamanoBoton) {
      println("Cambiar a Acelerometro");
      ModoAcelerometro = !ModoAcelerometro;
    } else {
      println("Pedir Ayuda");
    }
  }
}

void onAccelerometerEvent(float x, float y, float z) {
  SensorX = -x;
  SensorY = y;
}
