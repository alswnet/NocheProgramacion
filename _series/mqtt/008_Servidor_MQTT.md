---
title: Aprende a crear tu Servidor MQTT Mosquitto en Raspberry Pi y Linux
video_number: 8
date: 2024-9-5
video_id: OfD87ESs2nQ
repository: mqtt/008_Servidor_MQTT
tags:
  - mqtt
  - linux
  - rasberrypi

topics:
  - title: Inicio
    time: "00:00"
  - title: Guía de instalación
    time: "01:29"

links:
  - title: Pagina de Documentación de mosquitto.conf
    url: https://mosquitto.org/man/mosquitto-conf-5.html

videos:
  - title: Conectarte a SSH a Raspberry pi
    pendiente: true
  - title: Conéctate a Raspberry pi desde cualquier lugar
    pendiente: true
  - title: Que es mDNS
    url: tutoriales/072_Que_es_mDNS
  - title: Que terminar uso - Guake
    url: listas/03_linux/10_mi_terminal
  - title: Mosquito cliente
    url: series/mqtt/006_mosquitto_sub_pub
  - title: Como usar systemctl en Linux
    url: listas/03_linux/03_como_usar_systemctl
  - title: Poner IP Fija a Raspberry PI
    pendiente: true

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

Hoy veremos algo muy importante para proyectos IOT levantar tu propio servidor MQTT con Mosquitto

comando usados en el video con pequeñas explicación
Si no se leen bien en los comentarios, entrar al articulo del video en NocheProgramacion

actualizar paquetes
sudo apt update

actualizar la maquina
sudo apt updrade

instalar servidor mosquitto
sudo apt install mosquitto

(opcional) mosquito cliente
sudo apt install mosquitto-clients

prueba escuchar local de servidor mosquitto
mosquitto_sub -h localhost -t "#" -d

prueba publicación local
mosquitto_pub -h localhost -t "tu-topico" -m "tu-mesanje" -d

estado servidor de mosquitto
systemctl status mosquitto.service

apagar servidor de mosquitto
sudo systemctl stop mosquitto.service

encender servidor de mosquitto
sudo systemctl start mosquitto.service

editar archivo de mosquitto.conf
nano mosquitto.conf

levantar un servidor mosquitto
mosquitto -c mosquitto.conf

editar archivo de mosquitto.conf servidor de linux
sudo nano /etc/mosquitto/mosquitto.conf

leer los de servidor mosquitto
sudo tail -f /var/log/mosquitto/mosquitto.log
