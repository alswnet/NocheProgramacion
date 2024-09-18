---
title: Agrega Seguridad a tu Servidor MQTT Mosquitto con Usuario y Contraseña
video_number: 9
date: 2024-9-16
video_id: 1UxMq0EnRqE
tags:
  - mqtt
  - mosquitto

topics:
  - title: inico
    time: "00:00"
  - title: Agregar usuario a contraseña Mosquitto
    time: "02:00"
  - title: Agregar con usuario y Contraseña a mosquitto
    time: "03:16"
  - title: Elminar usuario de Servidor de Mosquitto
    time: "03:45"
  - title: Agregar Contraseñas a Servidor de Mosquitto
    time: "04:16"

links:
  - title: Pagina de Documentación de mosquitto.conf
    url: https://mosquitto.org/man/mosquitto-conf-5.html

piezas:
  - title: Raspberry Pi

colaboradores:
  - title: Editor
    colaborador: ingjuan
  - title: Camarografa
    colaborador: paty

miembros:
  - title: Maker ESP
    items:
      - title: EDUARDO MARCELO PALACIOS
  - title: Maker Uno
    items:
      - title: JORGE LUIS RODRIGUEZ RAMIREZ
      - title: alexis carrasco
      - title: Carlos Jiménez
      - title: Mauricio Miramont
      - title: Nippur Nestor
      - title: federicoymarta garcia garcia
      - title: Fernando Armada
      - title: Waldo Ratti
      - title: Claudio Bloise
      - title: Lolailo Aviles Arroyo

actualizado: true
---

Hoy veremos como agregar seguridad de usuario y contraseña a nuestro servidor mqtt usando mosquitto 

Comando de mensajes de depuración
sudo tail -f /var/log/mosquitto/mosquitto.log

Entrar en folder servidor mosquitto
cd /etc/mosquitto/

Entrar a archivo de contra 
sudo nano contra.txt

agregar un usuario
sudo mosquitto_passwd -c contra.txt user

agregar un usuario y contraseña
sudo mosquitto_passwd -b contra.txt user password

borrar usuario
sudo mosquitto_passwd -D contra.txt user

linea a agregar en archivo de configuración de mosquitto
password_file /etc/mosquitto/contra.txt

parar servidor
sudo systemctl stop mosquitto.service

iniciar servidor
sudo systemctl start mosquitto.service
