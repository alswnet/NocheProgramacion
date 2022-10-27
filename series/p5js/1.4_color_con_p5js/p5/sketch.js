function setup() {
  createCanvas(400, 400);
}

function draw() {
  background(255);
  strokeWeight(5);
  
  fill(255, 0, 0);
  noStroke();
  ellipse(100, 200, 150, 150);
  fill(100, 0, 100);
  noFill();
  stroke(0, 0, 255);
  rect(100, 100, 150, 50);
}
