const char* ssid_1     = "ALSW_ESTUDIO";
const char* password_1 = "Fullpower7##";
const char* ssid_2     = "Subcribanse";
const char* password_2 = "alswnet";

String Pagina = R"====(<!doctypehtml><title>Servidor</title><style>body{background-color:#424242}h1,h2,h3{background-color:#474747;color:#fff;padding:10px}.pollo{position:relative;display:inline-block;width:60px;height:34px;background-color:#ccc;border-radius:34px}.vivo .pollo{background-color:#2196f3}.pollo:hover{background-color:#072a46}.huevo{position:absolute;content:"";height:26px;width:26px;left:4px;bottom:4px;border-radius:34px;background-color:#fff}.vivo .huevo{left:28px}input{margin:.4rem}input[type=range]{-webkit-appearance:none;width:200px;height:10px;border-radius:5px;background-image:linear-gradient(#71b9f4,#2196f3);background-repeat:no-repeat}#rangevalue{font-size:5vw;color:#fff}</style><center><h1>Control RGB</h1><h3>Estado</h3><div class=vivo id=botonEstado><span class=pollo><span class=huevo></span></span></div><h3>Nivel</h3><output id=rangevalue>50</output><br><input id=rangeNivel type=range value=50 max=255 min=0 oninput="rangevalue.value=value"><h3>Color</h3><input id=colorHTML type=color value=#ff0000><h3>Arcoiris</h3><div class=vivo id=botonArcoiris><span class=pollo><span class=huevo></span></span></div></center><script>const elementoEstado = document.getElementById("botonEstado");
            const elementoNivel = document.getElementById("rangeNivel");
            const elementoColor = document.getElementById("colorHTML");
            const elementoArcoiris = document.getElementById("botonArcoiris");

            elementoEstado.addEventListener("click", cambiarEstado);
            elementoNivel.addEventListener("click", cambiarNivel);
            elementoColor.addEventListener("change", cambiarColor);
            elementoArcoiris.addEventListener("click", cambiarArcoiris);

            function cambiarEstado(){
                const elementoEstado = document.getElementById("botonEstado");
                
                if(elementoEstado.className == "vivo"){
                    elementoEstado.className = "muerto"
                } else {
                    elementoEstado.className = "vivo";
                }
                consultaGET("http://%ip/" + elementoEstado.className);
                console.log("Cambiando Boton");
            }

            function cambiarNivel(){
                const elementoNivel = document.getElementById("rangeNivel");
                consultaGET("http://%ip/nivel?valor=" + elementoNivel.value)
                console.log("Cambiando Nivel " + elementoNivel.value);
            }
            
            function cambiarColor(){
                const elementoColor = document.getElementById("colorHTML");
                let ColorActual = hexa_a_rgb(elementoColor.value);
                consultaGET("http://%ip/color?r=" + ColorActual.r + "&g=" + ColorActual.g + "&b=" + ColorActual.b);
                console.log("Cambiando Color " + elementoColor.value);
            } 

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
                const elementoArcoiris = document.getElementById("botonArcoiris");
                
                if(elementoArcoiris.className == "vivo"){
                    elementoArcoiris.className = "muerto"
                } else {
                    elementoArcoiris.className = "vivo";
                }
                consultaGET("http://%ip/arcoiris?estado=" + elementoArcoiris.className);
                console.log("Cambiando Arcoires");
            }

            function consultaGET(consulta){
                const Http = new XMLHttpRequest();
                console.log("Consultando "+ consulta);

                Http.open("GET", consulta);
                Http.send();

                Http.onreadystatechange = (e) => {
                    console.log(Http.status);
                    console.log(Http.responseText);
                }
            }</script>)====";
