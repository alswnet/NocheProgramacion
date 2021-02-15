#include <CapacitiveSensor.h>
//Libreria se Sensor Capacitivo puede descargar
//http://playground.arduino.cc/Main/CapacitiveSensor

CapacitiveSensor   SensorC = CapacitiveSensor(4, 2);
//Pines donde esta puesto el censor
int led = 13;

int limite = 100;
//Limite que puede llegar el valor del sensor antes de encender el led
//Cámbialo dependiendo de tu circuito, usa el puerto serial para ver que valor es el mas indicado


void setup(){
  SensorC.set_CS_AutocaL_Millis(0xFFFFFFFF);
  //Inicializa el sensor y desactiva la autocorrecion

  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop(){
  long Valor =  SensorC.capacitiveSensor(30);
  //toma el dato del sensor en el tiempo establecido

  Serial.println(Valor);
  //Muestra el dato en el puerto serial para depuracion

  if (Valor > limite) {
    digitalWrite(led, HIGH);
  }
  else {
    digitalWrite(led, LOW);
  }

  delay(100);
}
