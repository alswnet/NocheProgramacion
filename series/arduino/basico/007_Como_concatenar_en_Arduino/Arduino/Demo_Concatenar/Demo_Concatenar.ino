// Creado ChepeCarlos de ALSW
// Tutorial Completo en https://nocheprogramacion.com
// Canal YouTube https://youtube.com/alswnet?sub_confirmation=1

template<class T> inline Print &operator <<(Print &obj, T arg) {
  obj.print(arg);
  return obj;
}

int Valores[10] = {2, 3, 10, 11, 2, 8, 9, 221, 7, 99};

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < 10; i++) {
    //    Serial.print("El Valor ");
    //    Serial.print(i);
    //    Serial.print(" es ");
    //    Serial.print(Valores[i]);
    //    Serial.println();

    //    Serial.println("El Valor " + i + " es " + Valores[i]);

    Serial << "El Valor " << i << " es " << Valores[i] << "\n";
  }

}


void loop() {
 
}
