// Creado ChepeCarlos de ALSW
// Tutorial Completo en https://nocheprogramacion.com
// Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

let Camara;
let poseNet;
let poses = [];
let emoji;

function setup() {
  createCanvas(640, 480);
  emoji = loadImage("./emoji.png", CargoImagen, ErrorImagen);
  Camara = createCapture(VIDEO);
  Camara.size(width, height);
  Camara.hide();

  poseNet = ml5.poseNet(Camara, ModeloListo);

  poseNet.on("pose", function(results) {
    poses = results;
  });
}

function draw() {
  image(Camara, 0, 0, width, height);
  //  drawKeypoints();
  //  drawSkeleton();
  //  image(emoji, 100, 100, 100, 100);
  DibujarEmoji();
}

function ModeloListo() {
  console.log("Modelo Listo");
  select("#status").html("Modelos listo");
}

function CargoImagen() {
  console.log("Cargare Imagen");
}

function ErrorImagen() {
  console.log("error imagen ");
}

function DibujarEmoji() {
  push();
  for (let i = 0; i < poses.length; i++) {
    let PoseActual = poses[i].pose;
    fill(255, 255, 0);
    noStroke();
    imageMode(CENTER);
    image(emoji, PoseActual.nose.x, PoseActual.nose.y, 100, 100);
  }
  pop();
}

function drawKeypoints() {
  //console.log("Candida de personas" + poses.length);
  for (let i = 0; i < poses.length; i++) {
    let pose = poses[i].pose;
    for (let j = 0; j < pose.keypoints.length; j++) {
      let keypoint = pose.keypoints[j];
      if (keypoint.score > 0.2) {
        fill(255, 255, 0);
        noStroke();
        ellipse(keypoint.position.x, keypoint.position.y, 20, 20);
      }
    }
  }
}

// A function to draw the skeletons
function drawSkeleton() {
  // Loop through all the skeletons detected
  for (let i = 0; i < poses.length; i++) {
    let skeleton = poses[i].skeleton;
    // For every skeleton, loop through all body connections
    for (let j = 0; j < skeleton.length; j++) {
      let partA = skeleton[j][0];
      let partB = skeleton[j][1];
      stroke(255, 0, 0);
      line(
        partA.position.x,
        partA.position.y,
        partB.position.x,
        partB.position.y
      );
    }
  }
}
