const int PinEcho1 = 7;
const int PinTrigger1 = 6;
const int PinEcho2 = 5;
const int PinTrigger2 = 4;

void setup() {
  Serial.begin(9600);
  pinMode(PinEcho1, INPUT);
  pinMode(PinTrigger1, OUTPUT);
  digitalWrite(PinTrigger1, 0);
  pinMode(PinEcho2, INPUT);
  pinMode(PinTrigger2, OUTPUT);
  digitalWrite(PinTrigger2, 0);
}

void loop() {
  long D1 = Distancia(PinTrigger1, PinEcho1);
  Serial.print("D1/");
  Serial.println(D1);
  delay(100);
  long D2 = Distancia(PinTrigger2, PinEcho2);
  Serial.print("D2/");
  Serial.println(D2);
  delay(100);
}

long  Distancia(int Trigger, int Echo) {
  long D, T;
  digitalWrite(Trigger, 0);
  delayMicroseconds(2);
  digitalWrite(Trigger, 1);
  delayMicroseconds(10);
  digitalWrite(Trigger, 0);

  T = pulseIn(Echo, HIGH);

  D = T / 58;
  return D;
}
