// Creado ChepeCarlos de ALSW
// Tutorial Completo en https://nocheprogramacion.com
// Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

int SensorPIR = 2;

void setup() {
  Serial.begin(9600);
  pinMode(SensorPIR, INPUT);
}

void loop() {
  int Valor = digitalRead(SensorPIR);
  Serial.println(Valor);
  delay(250);
}
