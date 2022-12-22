const char* ssid_1     = "###";
const char* password_1 = "###";
const char* ssid_2     = "Subcribanse";
const char* password_2 = "ChepeCarlos";

//const
String Pagina =  R"====(<!DOCTYPE html>
<html>
  <head>
    <title>Servidor </title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <style>
      body {
        background-color: #424242;
      }

      h1, h2, h3 {
        background-color: rgb(47, 47, 47);
        color: white;
        padding: 10px;
      }
      
      #rangevalue{
        font-size:5vw;
        color: white;
      }

      .pollo {
        position: relative;
        display: inline-block;
        width: 60px;
        height: 34px;
        background-color: #ccc;
        border-radius: 34px;
      }

      .vivo .pollo {
        background-color: #2196f3;
      }

      .pollo:hover {
        background-color: #072a46;
      }

      .huevo {
        position: absolute;
        content: "";
        height: 26px;
        width: 26px;
        left: 4px;
        bottom: 4px;
        border-radius: 34px;
        background-color: white;
      }

      .vivo .huevo {
        left: 28px;
      }

      input {
        margin: 0.4rem;
      }

      input[type="range"] {
        -webkit-appearance: none;
        width: 200px;
        height: 10px;
        border-radius: 5px;
        background-image: linear-gradient(#71b9f4, #2196f3);
        background-repeat: no-repeat;
      }
    </style>
  </head>

  <body>
    <center>
      <h1>Control RGB</h1>
      <h3>Estado</h3>
      <div id="botonEstado" class="vivo">
        <span class="pollo">
          <span class="huevo"></span>
        </span>
      </div>
      
      <h3>Nivel</h3>
      <output id="rangevalue">50</output><br>
      <input type="range" value="50" min="0" max="255" id="rangeNivel" oninput="rangevalue.value=value">
     
      <h3>Color</h3>
      <input type="color"  id="colorHTML" name="colorHTML" value="#ff0000" > </br>
      
      <h3>Arcoiris</h3>
      <div id="botonArcoiris" class="vivo">
        <span class="pollo">
          <span class="huevo"></span>
        </span>
      </div>
    </center>

    <script>

      const elementoEstado = document.getElementById("botonEstado");
      const elementoNivel = document.getElementById("rangeNivel");
      const elementoColor = document.getElementById("colorHTML");
      const elementoArcoiris = document.getElementById("botonArcoiris");
      
      elementoEstado.addEventListener("click", cambiarEstado);
      elementoNivel.addEventListener("click", cambiarNivel);
      elementoColor.addEventListener("change", cambiarColor);
      elementoArcoiris.addEventListener("click", cambiarArcoiris);

      function cambiarEstado(){
        console.log("%ip");
        const elementoEstado = document.getElementById("botonEstado");

        if(elementoEstado.className == "vivo"){
          elementoEstado.className = "muerto";
        } else{
          elementoEstado.className = "vivo";
        }
        console.log("Cambiando boton a " + elementoEstado.className)
        consultaGET("http://%ip/" + elementoEstado.className);
      };

      function cambiarNivel(){
        const elementoNivel = document.getElementById("rangeNivel");
        console.log("Cambiando nivel a " + elementoNivel.value);
        consultaGET("http://%ip/nivel?valor=" +  elementoNivel.value);
      }

      function cambiarColor(){
        console.log("Cambiando color");
        console.log(colorHTML.value);
        colorActual = hexa_a_rgb(colorHTML.value);
        consultaGET("http://%ip/color?r=" + colorActual.r +"&g=" + colorActual.g + "&b=" + colorActual.b);
      };

      function hexa_a_rgb(hex) {
        var result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex);
        return result
          ? {
              r: parseInt(result[1], 16),
              g: parseInt(result[2], 16),
              b: parseInt(result[3], 16),
            }
          : null;
      }

      function cambiarArcoiris(){
        const elementoEstado = document.getElementById("botonArcoiris");

        if(elementoEstado.className == "vivo"){
          elementoEstado.className = "muerto";
        } else{
          elementoEstado.className = "vivo";
        }
        console.log("Cambiando Arcoiris a " + elementoEstado.className)
        consultaGET("http://%ip/arcoiris?estado=" + elementoEstado.className);
      }
      
      function consultaGET(consulta){
        const Http = new XMLHttpRequest();
        console.log(`Consultando  ${consulta}`)
        Http.open("GET", consulta);
        Http.send();

        Http.onreadystatechange = (e) => {
          console.log(Http.status );
          // console.log(Http.responseText);
        };
      };
    </script>
  </body>
</html>
)====";
