// Creado ChepeCarlos de ALSW
// Tutorial Completo en https://nocheprogramacion.com
// Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

int PinSensor = A0;

void setup() {
  Serial.begin(9600);
  pinMode(PinSensor, INPUT);
}

void loop() {
  int Valor = analogRead(PinSensor);
  Serial.println(Valor);
  delay(100);
}
