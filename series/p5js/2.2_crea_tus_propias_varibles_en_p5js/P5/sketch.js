let posicionX = 100;

function setup() {
  createCanvas(400, 400);
}

function draw() {
  background(220);
  fill(255, 0, 255);
  posicionX++;
  circle(posicionX, 200, 50);
}

function mousePressed() {
  posicionX = 100;
}
