//Pines de los motores 
int MotorD[2] = {13.12};
int MotorI[2] = {9, 10};
int PwmD = 6;
int PwmI = 5;
int STBY = 11;

void setup() {
  pinMode(PwmD, OUTPUT);
  pinMode(PwmI, OUTPUT);
  for (int i = 0; i < 2; i++) {
    pinMode(MotorD[i], OUTPUT);
    pinMode(MotorI[i], OUTPUT);
  }
  pinMode(STBY, OUTPUT);
  digitalWrite(STBY, 1);
}

void loop() {
  VelocidadMotor(MotorD, PwmD, 255);//ejemplo de Motor Derecho
  VelocidadMotor(MotorI, PwmI, 255);//ejemplo de Motor Izquierdo
}

//Funcion para Poner una velocidad a un motor
//La velocidad puede ser desde -255 a 255
void VelocidadMotor(int Motor[], int PWM, int Velocidad) {
  if (Velocidad > 0 ) {
    digitalWrite(Motor[0],  1);
    digitalWrite(Motor[1],  0);
  }
  else {
    Velocidad = - Velocidad;
    digitalWrite(Motor[0], 0);
    digitalWrite(Motor[1], 1);
  }
  analogWrite(PWM, Velocidad);
}
