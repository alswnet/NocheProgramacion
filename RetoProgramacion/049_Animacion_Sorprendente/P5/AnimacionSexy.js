let Frecuencia = 200; 
let Tiempo = 0;
let P1, P2; 
let L1, L2; 
let Panel1, Panel2;
let Grosor;


function setup() {
  createCanvas(500, 500);
  background(0);
}


function draw() {
  if (Tiempo + Frecuencia < millis()) {
    Tiempo = millis();
    EscojerLina();
    EscojerPanel();
    ActualizarPanel();
    ActualizarLinea();
  }
}

function ActualizarPanel() {
  let Vector = p5.Vector.sub(P1, P2);
  let Angulo1 = p5.Vector.fromAngle(Vector.heading + PI/2);
  Angulo1 = Angulo1.mult(Grosor/2);
  let Angulo2 = p5.Vector.fromAngle(Vector.heading + PI/2);
  Angulo2 = Angulo2.mult(-Grosor/2);
  print(Angulo);
  push();
  //translate(Angulo1.x, Angulo1.y);
  image(Panel1, Angulo1.x, Angulo1.y);
  pop();
  push();
 // translate(Angulo2.x, Angulo2.y);
 // image(Panel2, 0, 0);
  pop()
}

function EscojerPanel() {
  Panel1 = get();
  Panel2 = get();
  Panel1.loadPixels();
  Panel2.loadPixels();
  let Vector = p5.Vector.sub(P1, P2);
  let Angulo = Vector.heading();
  let P;
  for (let x = 0; x < Panel1.width; x++) {
    for (let y = 0; y < Panel2.height; y++) {
      P = createVector(x, y);
      let PM =  p5.Vector.sub(P1, P);
      let PAngulo = PM.heading();
      if (Angulo < PAngulo) {
        Panel1.set(x, y, color(0, 0, 0, 0));
      } else {
        Panel2.set(x, y, color(0, 0, 0, 0));
      }
    }
  }


  Panel1.updatePixels();
  Panel2.updatePixels();
}

function ActualizarLinea() {
  strokeWeight(Grosor/3);
  stroke(255);
  DibujarLineaGrosor(Grosor/2);
  DibujarLineaGrosor(-Grosor/2);  
  strokeWeight(Grosor);
  stroke(0);
  DibujarLinea();
}

function DibujarLineaGrosor(G) {
  push();
  translate(P1.x, P1.y);
  let Vector = p5.Vector.sub(P2, P1);
  let VectorInicial = p5.Vector.fromAngle(Vector.heading() + PI/2);
  VectorInicial=VectorInicial.mult(G);
  translate(VectorInicial.x, VectorInicial.y);
  line(0, 0, Vector.x, Vector.y);
  pop();
}

function DibujarLinea() {
  line(P1.x, P1.y, P2.x, P2.y);
}

function EscojerLina() {
  L1 = int(random(0, 4));
  do {
    L2 = int(random(0, 4));
  } while (L1 == L2);
  if (L2 > L1) {
    let Ltmp= L2;
    L2 = L1;
    L1 = Ltmp;
  }
  print("L1 " + L1);
  P1 = EscojerLado(L1);
  P2 = EscojerLado(L2);
  Grosor = random(5, 30);
}

function EscojerLado(l) {
  let V = createVector(0, 0);
  switch(l) {
  case 0:
    V.x = 0;
    V.y = random(height);
    break;
  case 1:
    V.x = random(width);
    V.y = 0;
    break;
  case 2:
    V.x = width;
    V.y = random(height);
    break;
  case 3:
    V.x = random(width);
    V.y = height;
    break;
  }
  return V;
}

let EstadoLoop = true;
function mousePressed() {
  if (EstadoLoop) {
    noLoop();
  } else {
    loop();
  }
  EstadoLoop= !EstadoLoop;
}
