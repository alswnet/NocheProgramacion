// Creado ChepeCarlos de ALSW
// Tutorial Completo en https://nocheprogramacion.com
// Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

float TiempoInicial = 0;
float TiempoFinal = 0;

void setup() {
  Serial.begin(115200);
  TiempoInicial = micros();

  TiempoFinal = micros();
  while (!Serial) {}

  Serial.print("El codigo tardo ");
  Serial.println(TiempoFinal - TiempoInicial);
}

void loop() {
}
