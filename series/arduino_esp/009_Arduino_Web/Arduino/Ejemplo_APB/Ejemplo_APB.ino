#include <WiFi.h>
#include "data.h"

WiFiServer Servidor(80);

String Cabecera;

unsigned long TiempoActual = 0;
unsigned long TiempoAnterior = 0;
const long TiempoCancelacion = 2000;

#define CantidadBotones 7
int Pin[CantidadBotones] = {18, 19, 5, 4, 3, 2, 0};
boolean Estado[CantidadBotones] = {false, false, false, false, false, false, false};

void setup() {
  Serial.begin(115200);

  Serial.println("Iniciando programa");

  for (int i = 0; i < CantidadBotones; i++) {
    pinMode(Pin[i], OUTPUT);
  }
  ActualizarSalidas();

  Serial.printf("Conectando: %s\n", ssid);
  WiFi.begin(ssid, password);

  Serial.print("Conectando...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(2000);
  }
  Serial.println(".. Conectado.");
  Serial.print("IP Servidor: ");
  Serial.println(WiFi.localIP());

  Servidor.begin();
}

void loop() {
  WiFiClient Cliente = Servidor.available();

  if (Cliente) {
    TiempoActual = millis();
    TiempoAnterior = TiempoActual;

    Serial.println("Nuevo Cliente");
    String LineaActual = "";
    while (Cliente.connected() && TiempoActual - TiempoAnterior <= TiempoCancelacion) {
      if (Cliente.available()) {
        TiempoActual = millis();
        char Letra = Cliente.read();
        Serial.print(Letra);
        Cabecera += Letra;
        if (Letra == '\n') {
          if (LineaActual.length() == 0) {
            ResponderPagina(Cliente, Cabecera);
            break;
          } else {
            LineaActual = "";
          }

        } else if (Letra != '\r') {
          LineaActual += Letra;
        }
      }
    }
    Cabecera = "";
    Cliente.stop();
    Serial.println("Cliente desconectado");
    Serial.println("");
  }
}

void ResponderPagina(WiFiClient Cliente, String Cabecera) {
  ActualizarBotones(Cabecera);
  Cliente.println("HTTP/1.1 200 OK");
  Cliente.println("Content-type:text/html");
  Cliente.println("Connection: close");
  Cliente.println();
  Cliente.println(Cuerpo);
  Cliente.print("<p>");
  ImprimirTodos(Cliente);
  ImprimirBotones(Cliente);
  Cliente.print("/<p>");

  Cliente.println("</html>");
  Cliente.println();

}

void ActualizarBotones(String Mensaje) {
  if (Mensaje.indexOf("GET") >= 0) {
    for (int i = 1; i <= CantidadBotones; i++) {
      if (Mensaje.indexOf("/on" + String(i)) >= 0) {
        Serial.print("Boton[");
        Serial.print(i);
        Serial.println("] ON");
        Estado[i - 1] = true;
      }
      else if (Mensaje.indexOf("/off" + String(i)) >= 0) {
        Serial.print("Boton[");
        Serial.print(i);
        Serial.println("] off");
        Estado[i - 1] = false;
      }
    }
  }
}

void ImprimirTodos(WiFiClient Cliente) {
  Cliente.print("<p>");
  ImprirTodo(Cliente, "on");
  ImprirTodo(Cliente, "off");
  Cliente.print("</p>");
}

void ImprirTodo(WiFiClient Cliente, String Etiqueta) {
  Cliente.print("<a href=\"");
  for (int i = 0; i < CantidadBotones; i++) {
    Cliente.print("/");
    Cliente.print(Etiqueta);
    Cliente.print(i + 1);
  }
  Cliente.print("\" class=\"btn btn-green\"><button class=\"button\">");
  Cliente.print(Etiqueta);
  Cliente.print("</button></a>");
}

void ImprimirBotones(WiFiClient client) {
  for (int i = 0; i < CantidadBotones; i++) {
    client.print("<p>");
    ImprimirBoton(client, i + 1, Estado[i], "on");
    ImprimirBoton(client, i + 1, !Estado[i], "off");
    client.print("</p>");
    client.println();
  }
}

void ImprimirBoton(WiFiClient Cliente, int i, boolean Estado, String Etiqueta) {
  Cliente.print("<a href=\"/");
  Cliente.print(Etiqueta);
  Cliente.print(i);
  Cliente.print("\" class=\"btn ");
  if (Estado) {
    Cliente.print(" btn-green");
  } else {
    Cliente.print(" btn-red");
  }
  Cliente.print("\"><button class=\"button\">");
  Cliente.print(Etiqueta);
  Cliente.print(" ");
  Cliente.print(i);
  Cliente.print("</button></a>");
}

void ActualizarSalidas() {
  for (int i = 0; i < CantidadBotones; i++) {
    if (Estado[i]) {
      digitalWrite(Pin[i], HIGH);
    }
    else {
      digitalWrite(Pin[i], LOW);
    }
  }
}
