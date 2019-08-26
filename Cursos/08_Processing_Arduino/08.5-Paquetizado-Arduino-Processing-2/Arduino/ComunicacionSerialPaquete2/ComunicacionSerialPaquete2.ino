const int PinEcho1 = 7;
const int PinTrigger1 = 6;
const int PinEcho2 = 5;
const int PinTrigger2 = 4;
int M1, M2;

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
  if (Serial.available()) {
    DecodificarSerial();
  }
  long D1 = Distancia(PinTrigger1, PinEcho1);
  Serial.print("D1/");
  Serial.println(D1);
  delay(100);
  long D2 = Distancia(PinTrigger2, PinEcho2);
  Serial.print("D2/");
  Serial.println(D2);
  delay(100);
}

void DecodificarSerial() {
  // Mensaje de la forma M1/30
  // Donde M1 Es motor 1
  // 30 el valor
  String Mensaje = Serial.readStringUntil('\n');
  int PosicionPleca = Mensaje.indexOf('/');
  int PosicionSaltoLinea = Mensaje.length();
  String Dato = Mensaje.substring(0, PosicionPleca);
  int Valor = Mensaje.substring(PosicionPleca + 1, PosicionSaltoLinea).toInt();
  if (Dato.equals("M1")) {
    M1 = Valor;
  }
  else if (Dato.equals("M2")) {
    M2 = Valor;
  }

  /*
    Serial.print("M1:");
    Serial.print(M1);
    Serial.print(" M2:");
    Serial.print(M2);
    Serial.println();
  */
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
