

const char* ssid_1     = "ALSW_ESTUDIO";
const char* password_1 = "Fullpower7##";
const char* ssid_2     = "Subcribanse";
const char* password_2 = "alswnet";

const String Pagina =  R"====(<!doctypehtml><title>ESP con JavaScript</title><h1>Botones</h1><input id=botonEncender type=button value=Encendido onclick=botonEncender()> <input id=botonApagar type=button value=Apagado><script>function botonEncender(){
        console.log("Encender LED");
        consultarGET("encender");
    }

    function botonApagar(){
        console.log("Apagar LED");
        consultarGET("apagar");
    }

    function consultarGET(consulta){
        const Http = new XMLHttpRequest();
        console.log(`Consulta ${consulta}`);
        Http.open("GET", consulta);
        Http.send();

        Http.onreadystatechange = (e) => {
            console.log(Http.status);
            console.log(Http.response);
        }
    }

    const elementoApagar = document.getElementById("botonApagar");
    elementoApagar.addEventListener("click", botonApagar)</script>)====";
