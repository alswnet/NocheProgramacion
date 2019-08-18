import processing.serial.*;

Serial MiPuerto; 

void setup() {
  //printArray(Serial.list());
  MiPuerto = new Serial(this, "/dev/ttyUSB0", 9600);
  size(400, 600);
  ellipseMode(CENTER);
}

void draw() {
  background(0);
  fill(255, 0, 0);
  circle(200, 300, 300);
}
