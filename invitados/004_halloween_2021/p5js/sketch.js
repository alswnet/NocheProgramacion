let video;
let poseNet;
let pose;
let poseActual;

let skeleton;
let ImagenEsqueleto = Object();
let ConfianzaMinima = 0.1;
let RelacionCamara;

let ExprecionColores = /^#[0-9a-f]{3,6}$/i;
let ListaColores;
let listaExpreciones;
let EstadoFondo = "camara";
let EstadoFondoColor;
let EstadoExprecion;
let EstadoDepuracio = false;
let EstadoEsqueleto = true;

let FuerzaFiltro = 0.06;
let AnguloBraso;
let TamanoHuezo = 100;

let poseLista = [
  "leftShoulder",
  "rightShoulder",
  "leftElbow",
  "rightElbow",
  "leftWrist",
  "rightWrist",
  "leftEar",
  "rightEar",
  "rightHip",
  "leftHip",
  "rightKnee",
  "leftKnee",
  "rightAnkle",
  "leftAnkle",
  "nose",
];

let ListaHuezos = [
  ["leftShoulder", "leftElbow"],
  ["rightShoulder", "rightElbow"],
  ["leftElbow", "leftWrist"],
  ["rightElbow", "rightWrist"],
  ["leftHip", "leftKnee"],
  ["rightHip", "rightKnee"],
  ["rightAnkle", "rightKnee"],
  ["leftAnkle", "leftKnee"],
];

function preload() {
  console.log("PreCargando Imagenes");

  ListaColores = loadJSON("Colores.json");
  listaExpreciones = loadJSON("Expreciones.json", function () {
    EstadoExprecion = listaExpreciones[0];

    listaExpreciones.length = Object.values(listaExpreciones).length;
    ImagenEsqueleto.Cabeza = [];
    for (let i = 0; i < listaExpreciones.length; i++) {
      let Imagen = `assets/exprecion/${listaExpreciones[i]}.png`;
      ImagenEsqueleto.Cabeza[listaExpreciones[i]] = loadImage(Imagen);
    }
  });

  ImagenEsqueleto.Huezo = loadImage("assets/huezo.png");
  ImagenEsqueleto.Pecho = loadImage("assets/pecho.png");
  ImagenEsqueleto.Cadera = loadImage("assets/cadera.png");
  ImagenEsqueleto.Mano = loadImage("assets/mano.png");
}

function setup() {
  var ObtenerCanva = document.getElementById("micanva");
  video = createCapture(VIDEO);
  video.hide();
  var AnchoCanvas = ObtenerCanva.offsetWidth;
  RelacionCamara = video.height / video.width;
  var AltoCanvas = AnchoCanvas * RelacionCamara;
  var sketchCanvas = createCanvas(AnchoCanvas, AltoCanvas);
  sketchCanvas.parent("micanva");

  imageMode(CENTER);
  angleMode(DEGREES);
  poseNet = ml5.poseNet(video, modelLoaded);
  console.log("Cargando Modelo");
  poseNet.on("pose", gotPoses);
  ConectarMQTT();
  EstadoFondoColor = color(0, 0, 0);
  AnguloBraso = [0, 0];
}

function gotPoses(poses) {
  if (poses.length > 0) {
    if (!pose) {
      poseActual = Object();
      for (let i = 0; i < poseLista.length; i++) {
        poseActual[poseLista[i]] = Object();
        poseActual[poseLista[i]].x = 0;
        poseActual[poseLista[i]].y = 0;
        poseActual[poseLista[i]].confidence = 0;
      }
    }
    pose = poses[0].pose;
    skeleton = poses[0].skeleton;
  }
}

function modelLoaded() {
  console.log("Modelo:PoneNet Listo");
}

function draw() {
  AjuntarCamara();
  DibujarFondo();

  if (pose) {
    imageMode(CENTER);
    if (EstadoEsqueleto) {
      FiltarPose();
      DibujarCabeza();
      for (let i = 0; i < ListaHuezos.length; i++) {
        DibujarHuezo(
          poseActual[ListaHuezos[i][0]],
          poseActual[ListaHuezos[i][1]]
        );
      }

      DibujarMano(poseActual.leftWrist, poseActual.leftElbow, 0);
      DibujarMano(poseActual.rightWrist, poseActual.rightElbow, 1);

      DibujarCuerpo();
    }

    if (EstadoDepuracio) {
      for (let i = 0; i < pose.keypoints.length; i++) {
        let x = pose.keypoints[i].position.x;
        let y = pose.keypoints[i].position.y;
        fill(0, 255, 0);
        ellipse(x, y, 16, 16);
      }

      for (let i = 0; i < skeleton.length; i++) {
        let a = skeleton[i][0];
        let b = skeleton[i][1];
        strokeWeight(2);
        stroke(255);
        line(a.position.x, a.position.y, b.position.x, b.position.y);
      }
    }
  }
}

function AjuntarCamara() {
  var RelacionCamara2 = video.height / video.width;
  if (RelacionCamara != RelacionCamara2) {
    var Ancho = width;
    var Alto = Ancho * RelacionCamara2;
    RelacionCamara = RelacionCamara2;
    console.log("Cambiando " + Ancho + " - " + Alto);
    resizeCanvas(Ancho, Alto, true);
  }
}

function DibujarFondo() {
  if (EstadoFondo == "camara") {
    background("#fff");
    imageMode(CORNER);
    image(video, 0, 0);
  } else {
    background(EstadoFondoColor);
  }
}

function AplicarFiltro(PuntoActual, Punto) {
  PuntoActual.x = (1 - FuerzaFiltro) * PuntoActual.x + FuerzaFiltro * Punto.x;
  PuntoActual.y = (1 - FuerzaFiltro) * PuntoActual.y + FuerzaFiltro * Punto.y;
  return PuntoActual;
}

function CentroEntrePuntos(PuntoA, PuntoB) {
  let Punto = Object();
  Punto.x = (PuntoA.x + PuntoB.x) / 2;
  Punto.y = (PuntoA.y + PuntoB.y) / 2;
  return Punto;
}

function FiltarPose() {
  for (let i = 0; i < poseLista.length; i++) {
    poseActual[poseLista[i]].confidence = pose[poseLista[i]].confidence;
    poseActual[poseLista[i]] = AplicarFiltro(
      poseActual[poseLista[i]],
      pose[poseLista[i]]
    );
  }
}

function DibujarCabeza() {
  let Izquierda = poseActual.leftEar;
  let Derecha = poseActual.rightEar;
  let Naris = poseActual.nose;

  let Distancia = dist(Izquierda.x, Izquierda.y, Derecha.x, Derecha.y) * 1.25;
  TamanoHuezo = Distancia / 4;
  let Angulo = atan2(Izquierda.y - Derecha.y, Izquierda.x - Derecha.x);

  push();

  translate(Naris.x, Naris.y);
  rotate(Angulo);

  image(ImagenEsqueleto.Cabeza[EstadoExprecion], 0, 0, Distancia, Distancia);
  pop();
}

function DibujarMano(Muneca, Codo, IdAngulo) {
  if (
    Muneca.confidence > ConfianzaMinima &&
    Muneca.confidence > ConfianzaMinima
  ) {
    push();
    let AnguloPasado = AnguloBraso[IdAngulo];
    let AnguloActual = atan2(Muneca.y - Codo.y, Muneca.x - Codo.x);
    let Filtro = 0.02;
    let Angulo = (1 - Filtro) * AnguloPasado + Filtro * AnguloActual;
    let C = Object;
    C.magnitud = 10;
    C.x = C.magnitud * cos(Angulo);
    C.y = C.magnitud * sin(Angulo);

    imageMode(CENTER);
    translate(Muneca.x + C.x, Muneca.y + C.y);
    rotate(Angulo + 90);
    image(ImagenEsqueleto.Mano, 0, 0, 4 * TamanoHuezo, 4 * TamanoHuezo);
    AnguloBraso[IdAngulo] = Angulo;
    pop();
  }
}

function DibujarHuezo(Punto1, Punto2) {
  if (
    Punto1.confidence > ConfianzaMinima &&
    Punto2.confidence > ConfianzaMinima
  ) {
    push();

    let CentroX = (Punto1.x + Punto2.x) / 2;
    let CentroY = (Punto1.y + Punto2.y) / 2;
    let Distancia = dist(Punto1.x, Punto1.y, Punto2.x, Punto2.y);
    let Angulo = atan2(Punto1.y - Punto2.y, Punto1.x - Punto2.x);
    translate(CentroX, CentroY);
    rotate(Angulo);
    Distancia = Distancia * 0.8;
    image(ImagenEsqueleto.Huezo, 0, 0, Distancia, TamanoHuezo);
    pop();
  }
}

function DibujarCuerpo() {
  let Hombro = Object();
  let Cadera = Object();

  Hombro.Izquierda = poseActual.leftShoulder;
  Hombro.Derecha = poseActual.rightShoulder;

  Cadera.Izquierda = poseActual.leftHip;
  Cadera.Derecha = poseActual.rightHip;

  Hombro.Ancho = dist(
    Hombro.Izquierda.x,
    Hombro.Izquierda.y,
    Hombro.Derecha.x,
    Hombro.Derecha.y
  );
  Cadera.Ancho = dist(
    Cadera.Izquierda.x,
    Cadera.Izquierda.y,
    Cadera.Derecha.x,
    Cadera.Derecha.y
  );

  Hombro.Centro = Object();
  Hombro.Centro.x = (Hombro.Derecha.x + Hombro.Izquierda.x) / 2;
  Hombro.Centro.y = (Hombro.Derecha.y + Hombro.Izquierda.y) / 2;

  Cadera.Centro = Object();
  Cadera.Centro.x = (Cadera.Derecha.x + Cadera.Izquierda.x) / 2;
  Cadera.Centro.y = (Cadera.Derecha.y + Cadera.Izquierda.y) / 2;

  let Alto = dist(
    Hombro.Centro.x,
    Hombro.Centro.y,
    Cadera.Centro.x,
    Cadera.Centro.y
  );

  Hombro.Angulo = atan2(
    Hombro.Izquierda.y - Hombro.Derecha.y,
    Hombro.Izquierda.x - Hombro.Derecha.x
  );
  Cadera.Angulo = atan2(
    Cadera.Izquierda.y - Cadera.Derecha.y,
    Cadera.Izquierda.x - Cadera.Derecha.x
  );

  push();
  imageMode(CENTER);

  push();
  translate(Hombro.Centro.x, Hombro.Centro.y + (3 * Alto) / 8);
  rotate(Hombro.Angulo);
  image(ImagenEsqueleto.Pecho, 0, 0, Hombro.Ancho, (3 * Alto) / 4);
  pop();

  push();
  translate(Cadera.Centro.x, Cadera.Centro.y - Alto / 6);
  rotate(Cadera.Angulo);
  image(ImagenEsqueleto.Cadera, 0, 0, Cadera.Ancho, Alto / 4);
  pop();

  pop();
}
