void setup() {
  Serial.begin(9600);

  int edad = 23;

  Serial.print("Edad: ");
  Serial.print(edad);
  Serial.print(" es ");

  // if (edad > 18) {
  //   Serial.println("Mayor");
  // } else {
  //   Serial.println("Menos");
  // }

  Serial.println(edad > 18 ? "Mayor" : "Menos");

  Serial.println(" de Edad");
}

void loop() {
}
