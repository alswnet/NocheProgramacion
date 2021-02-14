/*jshint esversion: 6 */
var Camara;
var BotonesEntrenar;
var knn;
var modelo;
var Texto;
var Clasificando = false;

function setup() {
  createCanvas(320, 240);
  background(255, 0, 0);
  Camara = createCapture(VIDEO);
  Camara.size(320, 240);
  Camara.hide();

  modelo = ml5.featureExtractor("MobileNet", ModeloListo);
  knn = ml5.KNNClassifier();

  createP("Presiona Botones para entrenar");

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

  Texto = createP("Modelo no Listo, esperando");

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
  EntrenarKnn(NombreBoton);
}

function EntrenarKnn(ObjetoEntrenar) {
  const Imagen = modelo.infer(Camara);
  knn.addExample(Imagen, ObjetoEntrenar);
}

function ModeloListo() {
  console.log("Modelo Listo");
  Texto.html("Modelo Listo");
}

function clasificar() {
  const Imagen = modelo.infer(Camara);
  knn.classify(Imagen, function(error, result) {
    if (error) {
      console.error();
    } else {
      Texto.html("Es un " + result.label);
      //clasificar();
    }
  });
}

function draw() {
  image(Camara, 0, 0, 320, 240);
  if (knn.getNumLabels() > 0 && !Clasificando) {
    //clasificar();
    setInterval(clasificar, 500);
    Clasificando = true;
  }
}
