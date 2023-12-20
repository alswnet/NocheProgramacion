
void configurarReles() {
  for (int i = 0; i < CantidadAparatos; i++) {
    pinMode(Aparatos[i].pin, OUTPUT);
  }

  cargarRele();
  actualizarRele();
}

void cargarRele() {
  Serial.println("Cargando de memoria los aparatos");
  for (int i = 0; i < CantidadAparatos; i++) {
    Aparatos[i].Estado = leerArchivo(Aparatos[i].nombre);
    Serial << Aparatos[i].nombre << ": " << (Aparatos[i].Estado ? "Encendido" : "Apagado") << "\n";
  }
}

void actualizarRele() {
  for (int i = 0; i < CantidadAparatos; i++) {
    if (Aparatos[i].Estado != Aparatos[i].Estado_Anterior) {

      Serial.print("Aparato ");
      Serial.print(Aparatos[i].nombre);
      Serial.print(": ");
      Serial.print(Aparatos[i].Estado ? "Encendido" : "Apagado");
      Serial.println();

      TelnetStream.print("Aparato ");
      TelnetStream.print(Aparatos[i].nombre);
      TelnetStream.print(": ");
      TelnetStream.print(Aparatos[i].Estado ? "Encendido" : "Apagado");
      TelnetStream.println();

      Aparatos[i].Estado_Anterior = Aparatos[i].Estado;
      digitalWrite(Aparatos[i].pin, Aparatos[i].Invertido ? !Aparatos[i].Estado : Aparatos[i].Estado);
      salvarArchivo(Aparatos[i].nombre, Aparatos[i].Estado ? "Encendido" : "Apagado");
    }
  }
}

void estadoRele(Stream &miSerial) {
  for (int i = 0; i < CantidadAparatos; i++) {
    miSerial << "Aparato " << Aparatos[i].nombre << ": " << (Aparatos[i].Estado ? "Encencido" : "Apagado");
    miSerial << " - " << leerArchivo(Aparatos[i].nombre) << "\n";
  }
}
