const char* nombre = "esp-update";
const char* ssid    = "ALSW_ESTUDIO";
const char* password = "Fullpower7##";
String Pagina = R"====(
<!DOCTYPE html>
<html lang="es">
<head>
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>Actualización de Firmware</title>
<style>
  body {
    font-family: 'Segoe UI', sans-serif;
    margin: 0;
    padding: 0;
    background: linear-gradient(-45deg, #74ABE2, #5563DE, #58D5C9, #50C878);
    background-size: 400% 400%;
    animation: gradientBG 10s ease infinite;
    display: flex;
    justify-content: center;
    align-items: center;
    min-height: 100vh;
  }
  @keyframes gradientBG {
    0% {background-position: 0% 50%;}
    50% {background-position: 100% 50%;}
    100% {background-position: 0% 50%;}
  }
  .upload-container {
    background: rgba(255, 255, 255, 0.15);
    backdrop-filter: blur(10px);
    border-radius: 15px;
    padding: 30px;
    max-width: 450px;
    width: 90%;
    text-align: center;
    color: #fff;
    box-shadow: 0 8px 30px rgba(0,0,0,0.2);
    animation: fadeIn 1s ease;
  }
  @keyframes fadeIn {
    from {opacity: 0; transform: translateY(-10px);}
    to {opacity: 1; transform: translateY(0);}
  }
  h1 {
    margin-bottom: 15px;
    font-size: 1.8em;
    font-weight: 600;
  }
  p {
    font-size: 0.95em;
    margin-bottom: 25px;
  }
  input[type="file"] {
    display: none;
  }
  .file-label {
    display: inline-block;
    padding: 12px 20px;
    border: 2px dashed rgba(255,255,255,0.7);
    border-radius: 8px;
    cursor: pointer;
    transition: all 0.3s;
  }
  .file-label:hover {
    background: rgba(255,255,255,0.1);
    border-color: #fff;
  }
  input[type="submit"] {
    background: #50C878;
    color: white;
    border: none;
    padding: 12px 25px;
    border-radius: 8px;
    cursor: pointer;
    font-size: 16px;
    font-weight: bold;
    margin-top: 20px;
    transition: all 0.3s ease;
    box-shadow: 0 4px 10px rgba(0,0,0,0.3);
  }
  input[type="submit"]:hover {
    background: #3ba262;
    box-shadow: 0 6px 14px rgba(0,0,0,0.4);
  }
  #file-name {
    margin-top: 10px;
    font-size: 0.85em;
    color: rgba(255,255,255,0.8);
  }
</style>
</head>
<body>
  <div class="upload-container"><h1>Actualizacion OTA</h1>
    <p>Selecciona el archivo <b>.bin</b> para actualizar tu dispositivo</p>
    <form method='POST' action='/actualizar' enctype='multipart/form-data'>
      <label class="file-label">
      Seleccionar archivo
        <input type='file' name='update' accept='.bin' onchange="document.getElementById('file-name').innerText = this.files[0]?.name || ''">
      </label>
      <div id="file-name"></div>
      <input type='submit' value='Subir e Instalar'>
    </form>
  </div>
</body>
</html>
)====";

