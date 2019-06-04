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

void setup() {
  //Se asegura de que no se pueda girar la pantalla y la abarca a
  //totalidad
  orientation(LANDSCAPE);
  size(displayWidth, displayHeight);

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
  fill(255, 0, 0);
  rect(100, 40, 100, 100);
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

String mensaje="";
//Call back method to manage data received
void onBluetoothDataEvent(String who, byte[] data)
{
  mensaje+=new String(data);
  print(mensaje);
  mensaje="";
}



void mousePressed() {
  //Detecta clicks sobre el boton de conexion
  //Crea una nueva lista de seleccion en pantalla para que el
  //usuario elija un dispositivo bluetooth
  KetaiList klist = new KetaiList(this, listaDisp);
}
