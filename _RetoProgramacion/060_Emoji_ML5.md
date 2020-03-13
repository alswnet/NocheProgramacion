---
title: "Inteligencia artifical para hacer filtros faciales"
video_number: 60
date: 2019-08-09
video_id: EAUHuPPd4OM
repository: 060_Emoji_ML5

links:
  - title: "ML5"
    url: "https://ml5js.org/"
  - title: "poseNet"
    url: "https://ml5js.org/reference/api-PoseNet/"
  - title: "Post Blog poseNet"
    url: "https://medium.com/tensorflow/real-time-human-pose-estimation-in-the-browser-with-tensorflow-js-7dd0bc881cd5"


---

Vamos a enseñarles como unir inteligencia artificial con poseNet para poner emojis en tu cara.

### Mini Curso de MQTT
==========================================================


### Cuentas necesarias

1. [github](https://github.com/) para Repositorio de codigo y hosting de pagina web
2. [shiftr.io](https://shiftr.io/) Broker de MQTT

### Software Necesarios

1. Instalar **Arduino** ESP32 y Arduino ESP8266
	* Installar [Arduino IDE](http://www.arduino.cc/en/main/software) 1.8 o superior
	* Abir Preferencia de Archivo>Preferencia
	* Pegar en "Gestos de URLs Adicionales de tarjeta" esta url `https://dl.espressif.com/dl/package_esp32_dev_index.json,http://arduino.esp8266.com/stable/package_esp8266com_index.json,https://raw.githubusercontent.com/sparkfun/Arduino_Boards/master/IDE_Board_Manager/package_sparkfun_index.json`
	* Instalar hardware Extra, Heramientas>>Placas>>Gestos de Tarjetas..
	* Buscar e instalar ESP8266 y ESP32
	* Instalar [Driver FTDI](https://alsw.net/heramientas-para-trabajar-arduino/) y reiniciar la pc
	* Instalar MQTT de Librerias  
2. Instalar **ATON**
	* Descargar [Aton IDE](https://atom.io/)
	* Instalar Plugin Extra, Edit>>Preferencia>>Install
		* atom-beautify
		* aton-live-server
		* desables
			* aton-terjs
			* file-icons
			* minimap
3. **Navegador**
	*	Firefox o Google Chrome
4. Aceeso a **WiFi**
	* Pueto
		* 80 y 8080
		* mqtt

### Guia

1. Github Crear Repositorio
	* Crear Repositorio en Github
	* Clonas en Atom (ctrl-shift-P)
	* Editar Read.md usando [Markdown](https://guides.github.com/features/mastering-markdown/)
	* Agregar mas informacion
	* Confirmar codigo (commit, pull, push)
2. GithubPage
	* P5.js >> JavasCript Sexy
	* index.html y sketch.js (Copia aquia)
	* Subit a Github y Activar a GithubPage
3. Arduino Configurar
	* ESP32 y ESP8266
		* #define cual es cual?
	* MultiWifi me voy con quien encuentre :3
	*
4. MQTT
	* Protocolo
		* Broker - shiftr.io
			* Mosquitto
		* Topic
			* /Tmp
			* /Robot/Sensor/Temperatura
			* /Robot/Sensor/Humedad
			* /Laboratorio/Piso1/Sensor/Humo
		* Pub - Publicar
		* Sub - Suscribirse
	* Shiftr.io
		* Crear Area de trabajo
		* Crear contraseña y usuario de acceso
5. MQTT Arduino
	* Hola mundo Boton
		* boolean Estado
	* Cliente MQTT
	* begin("broker", cliente);
	* onMessage("callbas")
	* connect("Nombre", "Usuario", "Contrasena");
	* subscribe("topic");
	* loop();
	* callbaks
6. P5.js
	* Depurador de Navegador
	* Interfaces
		* Crear titulo
		* Crear P
		* Crear Botones
			* callbask
7.
