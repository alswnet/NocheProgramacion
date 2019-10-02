---
title: "Mini-Curso de Internet de las cosas Full-ALSW"
video_number: 47
date: 2019-08-21
video_id: qpOZfdLLfPU

piezas:
  - title: "ESP8266 Thing"
  - title: "ESP32"
---

En este mini Curso aprenderán como comunicar un Arduino (ESP32 o ESP8266) con una pagina web en GithubPage usando MQTT con este que es nuestro agradecimiento por llegas a 6000 maker :D

==========================================================

## Cuentas necesarias

1. [github](https://github.com/) para Repositorio de codigo y hosting de pagina web
2. [shiftr.io](https://shiftr.io/) Broker de MQTT

## Software Necesarios

1. Instalar **Arduino ESP32 y Arduino ESP8266**
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
4. Git
  * Descargar (Git)[https://git-scm.com/]
5. Aceeso a **WiFi**
	* Pueto
		* 80 y 8080
		* 1883 0 8883(MQTT o MQTTS)

## Pasos

1. Github Crear Repositorio
	* Crear Repositorio en Github
	* Clonas en Atom (ctrl-shift-P)
	* Editar Read.md usando [Markdown](https://guides.github.com/features/mastering-markdown/)
	* Agregar mas informacion
	* Confirmar codigo (commit, pull, push)
  * Configurar Git
2. P5.js
	* P5.js >> JavasCript Sexy [Tutorial Recomendado](https://hello.p5js.org/)
  * P5.dom >> CDN (Red de distribución de contenidos)
	* index.html y sketch.js [Copia Aqui](https://p5js.org/get-started/)
	* Subit a Github y Activar a GithubPage
3. Arduino Configurar
	* ESP32 y ESP8266
		* #define cual es cual?
	* MultiWifi me voy con quien encuentre :3
  * Un Led indicador
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
6. P5.dom
	* Depurador de Navegador
	* Interfaces
		* Crear titulo
		* Crear P
		* Crear Botones
			* callbask
7. MQTT
  * paho-mqtt >> CDN (Red de distribución de contenidos)
  * Codigo de [Ejemplo](https://github.com/eclipse/paho.mqtt.javascript)
8. Subir Pagina a GithubPage
