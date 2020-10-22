/*jshint esversion: 6 */
var Camara;
var RelacionCamara;
var CartaMensaje;
var Clasificando = false;
var CargandoNeurona = false;
var EntrenarFolder = false;
var knn;
var modelo;
var ListaFoto = [];
var sketchCanvas;

function setup() {
  var ObtenerCanva = document.getElementById('micanva');
  var AnchoCanvas = ObtenerCanva.offsetWidth;
  CartaMensaje = document.getElementById('CartaMensaje');
  CartaMensaje.innerText = "Cargando APP...";
  Camara = createCapture(VIDEO);
  // Camara.size(1280, 720);
  Camara.hide();
  RelacionCamara = Camara.height / Camara.width;
  var AltoCanvas = AnchoCanvas * RelacionCamara;
  sketchCanvas = createCanvas(AnchoCanvas, AltoCanvas);
  sketchCanvas.parent("micanva");

  modelo = ml5.featureExtractor('MobileNet', ModeloListo);
  knn = ml5.KNNClassifier();

  BotonesEntrenar = selectAll(".BotonEntrenar");
  for (var B = 0; B < BotonesEntrenar.length; B++) {
    BotonesEntrenar[B].mousePressed(PresionandoBoton);
  }

  var TexBoxBoton = select("#TextBoxBoton");
  TexBoxBoton.mousePressed(EntrenarTexBox);

  var LimpiarBoton = select("#LimpiarBoton");
  LimpiarBoton.mousePressed(LimpiarKnn);

  var SalvarBoton = select("#SalvarBoton");
  SalvarBoton.mousePressed(GuardadNeurona);

  var CargarBoton = select("#CargarBoton");
  CargarBoton.mousePressed(CargarNeurona);

  var FolderBoton = select("#FolderBoton");
  FolderBoton.mousePressed(CargarFolder);

  //CargarNeurona();
}

function draw() {
  if (!EntrenarFolder) {
    background("#b2dfdb");

    image(Camara, 0, 0, width, height);

    if (knn.getNumLabels() > 0 && !Clasificando) {
      console.log("Empezar a clasificar");
      setInterval(clasificar, 500);
      Clasificando = true;
    }

    var RelacionCamara2 = Camara.height / Camara.width;
    if (RelacionCamara != RelacionCamara2) {
      var Ancho = width;
      var Alto = Ancho * RelacionCamara2;
      RelacionCamara = RelacionCamara2;
      console.log("Cambiando " + Ancho + " - " + Alto);
      resizeCanvas(Ancho, Alto, true);
    }
  }
}

function windowResized() {
  var ObtenerCanva = document.getElementById('micanva');
  var Ancho = ObtenerCanva.offsetWidth;
  var Alto = Ancho * RelacionCamara;
  resizeCanvas(Ancho, Alto);
}

function ModeloListo() {
  console.log("Modelo Listo");
  CartaMensaje.innerText = "Modelo Listo";
}

function PresionandoBoton() {
  var NombreBoton = this.elt.innerText;
  console.log("Entrenando con " + NombreBoton);
  EntrenarKnn(NombreBoton);
}

function EntrenarKnn(ObjetoEntrenar) {
  var Imagen = modelo.infer(Camara);
  knn.addExample(Imagen, ObjetoEntrenar);
}

function clasificar() {
  if (Clasificando) {
    var Imagen = modelo.infer(Camara);
    knn.classify(Imagen, function(error, result) {
      if (error) {
        console.log("Error en clasificar");
        console.error();
      } else {
        console.log(result);
        var Etiqueta;
        var Confianza;
        if (!CargandoNeurona) {
          Etiqueta = result.label;
          Confianza = Math.ceil(result.confidencesByLabel[result.label] * 100);
        } else {
          Etiquetas = Object.keys(result.confidencesByLabel);
          Valores = Object.values(result.confidencesByLabel);
          var Indice = 0;
          for (var i = 0; i < Valores.length; i++) {
            if (Valores[i] > Valores[Indice]) {
              Indice = i;
            }
          }
          Etiqueta = Etiquetas[Indice];
          Confianza = Math.ceil(Valores[Indice] * 100);
        }
        CartaMensaje.innerText = Etiqueta + " - " + Confianza + "%";
      }
    });
  }
}

function EntrenarTexBox() {
  var Imagen = modelo.infer(Camara);
  var EtiquetaTextBox = select("#TextBox").value();
  knn.addExample(Imagen, EtiquetaTextBox);
}

function LimpiarKnn() {
  console.log("Borrando Neuroona");
  if (Clasificando) {
    Clasificando = false;
    clearInterval(clasificar);
    knn.clearAllLabels();
    CartaMensaje.innerText = "Neurona Borrada";
  }
}

function GuardadNeurona() {
  if (Clasificando) {
    console.log("Guardando la neurona");
    knn.save("NeuronaKNN");
  }
}

function CargarNeurona() {
  console.log("Cargando una Neurona");
  knn.load("./data/NeuronaKNN.json", function() {
    console.log("Neurona Cargada knn");
    CartaMensaje.innerText = "Neurona cargana de archivo";
    CargandoNeurona = true;
  });
}

function CargarFolder() {
  noLoop();
  EntrenarFolder = true;
  console.log("Cargando del Folder");
  CartaMensaje.innerText = "Cargando del Folder";
  loadJSON("./data/EntrenarFolder.json", ProcesarArchivo);
}

function ProcesarArchivo(data) {

  var Etiquetas = data.Entrenar;
  Etiquetas.forEach((Etiqueta, i) => {
    var EtiquetaActual = Etiqueta.Etiqueta;
    var DirectorioEtiqueta = Etiqueta.Directorio;
    var ImagenesActuales = Etiqueta.Imagenes;
    ImagenesActuales.forEach((item, i) => {
      var Areglo = {
        "Etiqueta": EtiquetaActual,
        "Direcion": DirectorioEtiqueta + "/" + item
      };
      ListaFoto.push(Areglo);
    });
  });
  setTimeout(EntrenarArchivo, 500);
}

function EntrenarArchivo() {
  if (ListaFoto.length > 0) {
    var ImagenActual = ListaFoto.pop();
    var Etiqueta = ImagenActual.Etiqueta;
    var Direcion = ImagenActual.Direcion;
    loadImage(Direcion, img => {
      image(img, 0, 0, width, height);
      CartaMensaje.innerText = "Entrenando " + Etiqueta + " - " + Direcion;
      redraw();
      var Imagen = modelo.infer(sketchCanvas);
      knn.addExample(Imagen, Etiqueta);
      setTimeout(EntrenarArchivo, 500);
    });
  } else {
    EntrenarFolder = false;
    loop();
  }
}
