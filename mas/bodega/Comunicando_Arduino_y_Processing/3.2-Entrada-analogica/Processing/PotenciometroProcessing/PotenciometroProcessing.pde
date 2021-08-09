// Creado ChepeCarlos de ALSW
// Tutorial Completo en https://nocheprogramacion.com
// Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

import processing.serial.*;

Serial MiSerial;
int Valor = 0;
void setup() {
  size(400, 600);
  MiSerial = new Serial(this, "/dev/ttyACM0", 9600);
}

void draw() {
  int ValorRojo = int(map(Valor, 0, 1023, 0, 255));
  int ValorAzul = int(map(Valor, 0, 1023, 255, 0));
  color ColorFondo =  color(ValorRojo, 0, ValorAzul);
  background(ColorFondo);

  if (MiSerial.available() > 0) {
    String Texto  = MiSerial.readStringUntil('\n');
    if (Texto != null) {
      Valor = int(trim(Texto));
    }
    println(Valor);
  }
}