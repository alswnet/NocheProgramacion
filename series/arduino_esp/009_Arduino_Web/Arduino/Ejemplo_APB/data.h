//Configuración de red
const char* ssid = "xxxxx";
const char* password = "xxxxxx";

const char *Cuerpo = R"====(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <style  >
    body{
background-color:#415a77;
      /* background-color: #436C94; */
      font-family: Arial;
    }
    #main-container{
      padding-top: 20px;
      text-align: center;
    }

    .btn{
      border-radius: 35px;
      "display: inline-block";
      padding: 20px 15px;
      text-decoration: none;
      text-shadow: 0 1px 0 rgba(255,255,255,0.3);
      box-shadow: 0 1px 1px rgba(0,0,0,0.3);
    }

    .btn-green{
      /*color: white;*/
      background-color: #3CC93F;
    }
    .btn-green:hover{
      background-color: #ffffff;
    }
    .btn-green:active{
      background-color: #29962A;
    }

    .btn-red{
      color: white;
      background-color: #E34242;
    }
    .btn-red:hover{
      background-color: #C43535;
    }
    .btn-red:active{
      background-color: #A62828;
    }
    "#tabla"{
    "margin: auto;"
}

  </style>
</head>
<body>
    <header>Identificador ESP32 V1.2</header>
    <td>
)====";
