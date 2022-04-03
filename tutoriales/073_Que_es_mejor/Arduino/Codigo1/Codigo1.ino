// Creado ChepeCarlos de ALSW
// Tutorial Completo en https://nocheprogramacion.com
// Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

float TiempoInicial = 0;
float TiempoFinal = 0;

void setup() {
  Serial.begin(115200);
  TiempoInicial = micros();
  
  String html = "";
  
  for (int i = 0; i < 100; i++) {
    html += "<p> SALIDA #";
    html += i;
    html += "  </p>\n";
  }


  TiempoFinal = micros();
  while (!Serial) {}
  Serial.println(html);
  Serial.print("El codigo tardo ");
  Serial.println(TiempoFinal - TiempoInicial);

}

void loop() {
}
