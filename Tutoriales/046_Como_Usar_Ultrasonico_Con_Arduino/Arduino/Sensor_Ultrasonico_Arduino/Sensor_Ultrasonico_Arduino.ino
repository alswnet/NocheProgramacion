// Creado ChepeCarlos de ALSW
// Tutorial Completo en https://nocheprogramacion.com
// Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

const int PinEcho = 7;
const int PinTrigger = 6;

long Tiempo, Distancia;

void setup() {
  Serial.begin(9600);
  pinMode(PinEcho, INPUT);
  pinMode(PinTrigger, OUTPUT);
  digitalWrite(PinTrigger, 0);
}

void loop() {
  digitalWrite(PinTrigger, 0);
  delayMicroseconds(2);
  digitalWrite(PinTrigger, 1);
  delayMicroseconds(10);
  digitalWrite(PinTrigger, 0);

  Tiempo = pulseIn(PinEcho, HIGH);

  Distancia = Tiempo / 58;

  Serial.print("Distancia : ");
  Serial.print(Distancia);
  Serial.println(" cm");
  delay(200);
}
