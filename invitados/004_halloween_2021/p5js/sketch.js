let video;
let poseNet;
let pose;
let poseActual;

let skeleton;
let ImagenEsqueleto = Object();
let ConfianzaMinima = 0.1;
let Opciones = {
  inputResolution: 313,
};

let ListaColores;
let listaExpreciones;
let EstadoFondo = "camara";
let EstadoExprecion;
let EstadoDepuracio = false;
let EstadoEsqueleto = true;

let FuerzaFiltro = 0.08;
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
      // console.log(Imagen)
      ImagenEsqueleto.Cabeza[listaExpreciones[i]] = loadImage(
        `assets/exprecion/${listaExpreciones[i]}.png`
      );
    }
  });
  console.log(listaExpreciones.length);
  for (let i = 0; i < listaExpreciones.length; i++) {
    console.log(i);
  }
  console.log(ListaColores, listaExpreciones, EstadoExprecion);

  // ImagenEsqueleto = Object();
  ImagenEsqueleto.Huezo = loadImage("assets/huezo.png");
  ImagenEsqueleto.Pecho = loadImage("assets/pecho.png");
  ImagenEsqueleto.Cadera = loadImage("assets/cadera.png");
  ImagenEsqueleto.Mano = loadImage("assets/mano.png");

  console.log("Imagenes Precargadas");
  // ImagenEsqueleto.Cabeza.feliz = loadImage("assets/exprecion/feliz.png");
  // ImagenEsqueleto.Cabeza.enojado =  loadImage("assets/exprecion/enojado.png");
}

function setup() {
  createCanvas(640, 480);
  imageMode(CENTER);
  angleMode(DEGREES);
  video = createCapture(VIDEO);
  video.hide();
  poseNet = ml5.poseNet(video, modelLoaded);
  console.log("Cargando Modelo");
  // poseNet = ml5.poseNet(video, Opciones, modelLoaded);
  poseNet.on("pose", gotPoses);
  ConectarMQTT();
}

function gotPoses(poses) {
  //console.log(poses);
  if (poses.length > 0) {
    if (!pose) {
      // poseActual = poses[0].pose;
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
  DibujarFondo();
  // background(0, 0, 0);
  image(video, width / 2, height / 2);

  if (pose) {
    // textSize(20);
    // textAlign(RIGHT);
    // text(pose.score, 100, 40);
    if (EstadoEsqueleto) {
      FiltarPose();
      DibujarCabeza();
      console.log("Dibujando Aqui ");

      for (let i = 0; i < ListaHuezos.length; i++) {
        DibujarHuezo(
          poseActual[ListaHuezos[i][0]],
          poseActual[ListaHuezos[i][1]]
        );
      }

      DibujarMano(poseActual.leftWrist, poseActual.leftElbow);
      DibujarMano(poseActual.rightWrist, poseActual.rightElbow);
      DibujarCuerpo();
    }

    // poseActual.rightShoulder = AplicarFiltro(
    //   poseActual.rightShoulder,
    //   pose.rightShoulder
    // );
    // poseActual.rightElbow = AplicarFiltro(
    //   poseActual.rightElbow,
    //   pose.rightElbow
    // );

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

function DibujarFondo() {
  // EstadoFondo;
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

function AnguloEntrePuntos(PuntoA, PuntoB) {}

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
  let Angulo = atan2(Izquierda.y - Derecha.y, Izquierda.x - Derecha.x);

  push();

  translate(Naris.x, Naris.y);
  rotate(Angulo);

  image(ImagenEsqueleto.Cabeza[EstadoExprecion], 0, 0, Distancia, Distancia);
  pop();

  // fill(255, 0, 0);
  // ellipse(Derecha.x, Derecha.y, 20, 20);
  // ellipse(Izquierda.x, Izquierda.y, 20, 20);
  // ellipse(Naris.x, Naris.y, 20, 20);
}

function DibujarMano(Muneca, Codo) {
  if (
    Muneca.confidence > ConfianzaMinima &&
    Muneca.confidence > ConfianzaMinima
  ) {
    push();
    let Angulo = atan2(Muneca.y - Codo.y, Muneca.x - Codo.x);
    let C = Object;
    C.magnitud = 30;
    // angleMode(RADIANS);
    C.x = C.magnitud * cos(Angulo);
    C.y = C.magnitud * sin(Angulo);
    fill(255, 0, 0);
    ellipse(C.x, C.y, 20, 20);
    // console.log(Angulo, C.x, C.y);

    imageMode(CENTER);
    translate(Muneca.x + C.x, Muneca.y + C.y);
    line(C.x, C.y, 0, 0);
    rotate(Angulo + 90);
    image(ImagenEsqueleto.Mano, 0, 0, 100, 100);
    pop();
  }
}

function DibujarHuezo(Punto1, Punto2) {
  if (
    Punto1.confidence > ConfianzaMinima &&
    Punto2.confidence > ConfianzaMinima
  ) {
    // line(Punto1.x, Punto2.y)
    push();

    let CentroX = (Punto1.x + Punto2.x) / 2;
    let CentroY = (Punto1.y + Punto2.y) / 2;
    // console.log(CentroX, CentroY);
    // let Distancia = CentroEntrePuntos(Punto1, Punto2);
    // dist(Punto1.x, Punto1.y, Punto2.x, Punto2.y);
    let Distancia = dist(Punto1.x, Punto1.y, Punto2.x, Punto2.y);
    let Angulo = atan2(Punto1.y - Punto2.y, Punto1.x - Punto2.x);
    // console.log(Angulo);
    translate(CentroX, CentroY);
    rotate(Angulo);
    // fill("#0f0ff2");
    // noStroke();
    // stroke("#00ffff");
    // strokeWeight(4);
    // rect(0, 0, Distancia, 60);
    Distancia = Distancia * 0.8;
    image(ImagenEsqueleto.Huezo, 0, 0, Distancia, 60);
    pop();

    // fill(255, 0, 0);
    // ellipse(Punto1.x, Punto1.y, 20, 20);
    // ellipse(Punto2.x, Punto2.y, 20, 20);
    // ellipse(Naris.x, Naris.y, 20, 20);
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

  // stroke(255, 0, 255);
  // fill(237, 34, 93);
  // beginShape();
  // vertex(HombroIzquierda.x, HombroIzquierda.y);
  // vertex(HombroDerecha.x, HombroDerecha.y);
  // vertex(CaderaIzquierda.x, CaderaIzquierda.y);
  // vertex(CaderaDerecha.x, CaderaDerecha.y);

  // endShape();
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

function CambiarFondo(Fondo) {
  switch (Operacion) {
    case "normal":
      EstadoFondo = "esqueleto";
      break;
  }
}
