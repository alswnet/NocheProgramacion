//librerias 
import java.util.*;
import ketai.ui.*;
import ketai.net.bluetooth.*;
import ketai.sensors.*;

//Variables de BT
KetaiBluetooth Kbt;
KetaiSensor Ksen;
ArrayList listaDisp;
String nombreDisp;
String mensaje="";


//
int AreaDibujo;
int Lectura[];
int CantidadLectura = 150;
int PunteroLectura = 0;
float Bateria = -1;
int Velocidad = 10;
boolean BTActivo = false;

void setup() {
  //Se asegura de que no se pueda girar la pantalla y la abarca a
  //totalidad
  orientation(LANDSCAPE);
  size(displayWidth, displayHeight);

  AreaDibujo = width-width/10;
  InicializarPantalla();


  //Inicializa las clases de bluetooth y sensores
  Kbt = new KetaiBluetooth(this);
  Ksen = new KetaiSensor(this);
  Ksen.start();


  //Obtiene la lista de dispositivos bluetooth emparejados
  listaDisp = Kbt.getPairedDeviceNames();

  //Imprime la lista en terminal
  Iterator itr = listaDisp.iterator();
  print("Dispositivos emparejados:");
  while (itr.hasNext()) {
    print(itr.next());
  }
}

void draw() {
  //Limpia el fondo de la pantalla
  background(0);

  //Dibuja el grafico del ECG en toda la pantalla, empleando una
  DibujarGUI();

  DibujarLinea();

  BuscarNumero();
}

void InicializarPantalla() {
  if (CantidadLectura < 100) {
    CantidadLectura = 100;
  }
  Lectura = new int[CantidadLectura];
  for (int i = 0; i<CantidadLectura; i++) {
    Lectura[i] = height/2;
  }
}

void DibujarGUI() {

  textSize(32);
  fill(255, 200, 0);
  text("Densidad: "+CantidadLectura+" Bateria: "+Bateria+"V Velocidad: "+Velocidad+"ms", 10, 30); 


  stroke(0);
  strokeWeight(1);

  if (BTActivo) {
    fill(0, 255, 0);
  } else {
    fill(255, 0, 0);
  }
  rect(AreaDibujo, 0, width/10, height/5);
  fill(255, 100, 0);
  rect(AreaDibujo, height/5, width/10, height/5);
  fill(255, 200, 0);
  rect(AreaDibujo, 2*height/5, width/10, height/5);
}

void DibujarLinea() {


  //linea verde con grosor de 5 pixeles
  stroke(0, 255, 0);
  strokeWeight(5);
  int X1, X2;
  int Y1, Y2;
  for (int i = 0; i< CantidadLectura; i++) {
    Y1 = ( PunteroLectura + i) % CantidadLectura;
    Y2 = ( Y1 + 1) % CantidadLectura;

    X1 = int( float(i) / float (CantidadLectura) * float(AreaDibujo));
    X2 = int( float(i + 1) / float (CantidadLectura) * float(AreaDibujo));

    line( X1, Lectura[Y1], X2, Lectura[Y2]);
  }
}

void BuscarNumero() {
  int FinPaquete = mensaje.indexOf(";");
  while (FinPaquete > -1) {
    String Paquete = mensaje.substring(0, FinPaquete);
    if (mensaje.indexOf("E") == 0) {
      try {
        int Numero = Integer.parseInt(Paquete.substring(1));
        println("Paquete Electro: "+Numero);
        Lectura[PunteroLectura] =  int( ( float(Numero)/1024) * float(height));
        PunteroLectura = (PunteroLectura+1) %  CantidadLectura;
      }
      catch(Exception e) {
        println("Error catch Electro: "+Paquete);
      }
    } else if (mensaje.indexOf("B") == 0) {
      try {
        int Numero = Integer.parseInt(Paquete.substring(1));
        Bateria = Numero/100;
        println("Paquete Bateria: "+Bateria);
      } 
      catch(Exception e) {
        println("Error catch Bateria: "+Paquete);
      }
    } else {
      println("Erro Paquete: "+Paquete);
    }
    mensaje = mensaje.substring(FinPaquete+1);
    FinPaquete = mensaje.indexOf(";");
  };
}

void onKetaiListSelection(KetaiList klist) {
  //Obtiene la cadena recien seleccionada
  nombreDisp = klist.getSelection();

  //Imprime el nombre de dispositivo en terminal
  print("Dispositivo seleccionado:");
  print(nombreDisp);

  //Efectua la conexion bluetooth al dispositivo seleccionado
  Kbt.connectToDeviceByName(nombreDisp);

  //Desaloja la lista, ya no es necesaria
  klist = null;
}


//Call back method to manage data received
void onBluetoothDataEvent(String who, byte[] data) {
  if (BTActivo) {
    mensaje+=new String(data);
  }
}



void mousePressed() {
  if (mouseX > AreaDibujo) {

    if (mouseY < height/5) {

      if (BTActivo) {
      } else {
        KetaiList klist = new KetaiList(this, listaDisp);
      }
      BTActivo =  !BTActivo;
      //Detecta clicks sobre el boton de conexion
      //Crea una nueva lista de seleccion en pantalla para que el
      //usuario elija un dispositivo bluetooth
    } else if (mouseY <  2 * height/5) {
      CantidadLectura = CantidadLectura + 10;
      InicializarPantalla();
      BTActivo = false;
    } else if (mouseY <  3 * height/5) {
      CantidadLectura = CantidadLectura - 10;
      InicializarPantalla();
      BTActivo = false;
    }
  }
}
