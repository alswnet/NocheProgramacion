// Creado ChepeCarlos de ALSW
// Tutorial Completo en https://nocheprogramacion.com
// Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

let Ancho;
let Columnas;
let Filas;
let Activo;

let Mundo;
let MundoSiquiente;

function setup() {
  createCanvas(500, 500);
  frameRate(4);
  Ancho = 10;
  Activo = true;
  Columnas = floor(width / Ancho);
  Filas = floor(height / Ancho);
  print(Columnas + " x " + Filas);
  Mundo = Array(Columnas);
  for (let x = 0; x < Columnas; x++) {
    Mundo[x] = new Array(Filas);
  }
  MundoSiquiente = Array(Columnas);
  for (let x = 0; x < Columnas; x++) {
    MundoSiquiente[x] = new Array(Filas);
  }
  Inicializar();
  background(0);
}

function draw() {
  // background(0,255, 255);
  if (Activo) {
    Acualizar();
  }
  Dibujar();
}

function Inicializar() {
  for (let x = 0; x < Columnas; x++) {
    for (let y = 0; y < Filas; y++) {
      if (x == 0 || y == 0 || x == Columnas - 1 || y == Filas - 1) {
        Mundo[x][y] = 0;
      } else {
        Mundo[x][y] = floor(random(2));
      }
    }
  }

  for (let x = 0; x < Columnas; x++) {
    for (let y = 0; y < Filas; y++) {
      MundoSiquiente[x][y] = 0;
    }
  }
}

function Acualizar() {
  for (let x = 1; x < Columnas - 1; x++) {
    for (let y = 1; y < Filas - 1; y++) {
      let Vecinos = 0;
      for (let i = -1; i <= 1; i++) {
        for (let j = -1; j <= 1; j++) {
          if (!(i == 0 && j == 0)) {
            Vecinos += Mundo[x + i][y + j];
          }
        }
      }

      if (Mundo[x][y] == 1) {
        if (Vecinos < 2 || Vecinos > 3) {
          MundoSiquiente[x][y] = 0;
        } else {
          MundoSiquiente[x][y] = 1;
        }
      } else {
        if (Vecinos == 3) {
          MundoSiquiente[x][y] = 1;
        } else {
          MundoSiquiente[x][y] = 0;
        }
      }
    }
  }

  let MundoTemporal = Mundo;
  Mundo = MundoSiquiente;
  MundoSiquiente = MundoTemporal;
}

function Dibujar() {
  for (let x = 0; x < Columnas; x++) {
    for (let y = 0; y < Filas; y++) {
      if (Mundo[x][y] == 1) {
        fill(0, 255, 255);
      } else {
        fill(0, 100);
      }
      // circle(x* Ancho,y * Ancho, Ancho);
      rect(x * Ancho, y * Ancho, Ancho, Ancho);
    }
  }
}

function keyPressed() {
  print(keyCode);
  if (keyCode === 32) {
    Activo = !Activo;
  } else if (keyCode === 67) {
    print("Borrar");
    for (let x = 0; x < Columnas; x++) {
      for (let y = 0; y < Filas; y++) {
        Mundo[x][y] = 0;
      }
    }
  } else if (keyCode == 82) {
    Inicializar();
  }
}

function mouseDragged() {
  DibujarConRaton();
}

function mouseClicked() {
  DibujarConRaton();
}

function DibujarConRaton() {
  print("Clip " + mouseX + " " + mouseY);
  let X = floor(mouseX / Ancho);
  let Y = floor(mouseY / Ancho);
  print("X " + X + ", Y" + Y);
  if (Mundo[X][Y] == 1) {
    Mundo[X][Y] = 0;
  } else {
    Mundo[X][Y] = 1;
  }
}
