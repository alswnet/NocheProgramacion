var Camara;
var BotonesEntrenar;


function setup() {
  createCanvas(320, 240);
  background(255, 0, 0);
  Camara = createCapture(VIDEO);
  Camara.size(320, 240);
  Camara.hide();

  createP('Presiona Botones para entrenar');

  var BotonArduino = createButton("Arduino");
  BotonArduino.class("BotonEntrenar");

  var BotonRedboard = createButton("Redboard");
  BotonRedboard.class("BotonEntrenar");

  var BotonESP8266 = createButton("ESP8266");
  BotonESP8266.class("BotonEntrenar");

  var BotonESP32 = createButton("ESP32");
  BotonESP32.class("BotonEntrenar");

  var BotonNada = createButton("Nada");
  BotonNada.class("BotonEntrenar");

  BotonesEntrenar = selectAll(".BotonEntrenar");

  for (var B = 0; B < BotonesEntrenar.length; B++) {
    BotonesEntrenar[B].style("margin", "5px");
    BotonesEntrenar[B].style("padding", "6px");
    BotonesEntrenar[B].mousePressed(PresionandoBoton);
  }

}

function PresionandoBoton() {
  var NombreBoton = this.elt.innerHTML;
  console.log("Entrenando con " + NombreBoton);
}

function draw() {
  image(Camara, 0, 0, 320, 240);
}