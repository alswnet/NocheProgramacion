---
title: Problema con ESP32 y ESP8266 en Linux con BRLTTY
video_number: 2
date: 2024-03-18
video_id: E0MZh3EjoJI
tags:
  - esp32
  - esp8266
  - linux
  - arduino
  - problema
  - error

topics:
  - title: Inicio
    time: '00:00'
  - title: Cosas hacer antes
    time: '00:12'
  - title: Diagnosticar ESP con journalctl
    time: '00:47'
  - title: Mensajes Normales
    time: '01:35'
  - title: Mensaje Error
    time: '02:05'
  - title: Problema del ESP8266 y ESP32 cpm Brltty
    time: '02:35'
  - title: Resolver Otros problemas con ESP32 y ESP8266
    time: '03:16'

links:
  - title: Brltty
    url: https://brltty.app/
  - title: Foro de Problema de Brltty
    url: https://forum.arduino.cc/t/solved-tools-serial-port-greyed-out-in-ubuntu-22-04-lts/991568/15

videos:
  - title: Serie ESP32 y ESP8266
    url: series/arduino_esp
  - title: journalctl  
    url: listas/03_linux/04_como_usar_journalctl
  - title: instalar esp
    url: series/arduino_esp/002_Instalar_ESP_en_Arduino
  - title: instalar arduino ide en Linux
    url: series/arduino/basico/02_instalar_arduino_linux
  - title: Abrir puertos en linux
    url: series/arduino/basico/03_problemas_puerto_arduino

piezas:
  - title: esp32
  - title: esp8266

colaboradores:
  - title: "Editor"
    colaborador: ingjuan
  - title: fotógrafa
    colaborador: paty

miembros:
  - title: Maker ESP
    items:
      - title: EDUARDO MARCELO PALACIOS
  - title: Maker Mega
    items:
      - title: Mario Radich
  - title: Maker Uno
    items:
      - title: federicoymarta garcia garcia
      - title: Fernando Armada
      - title: Waldo Ratti
      - title: Claudio Bloise
      - title: Lolailo Aviles Arroyo

actualizado: true
---

Hoy quiero montarles un problema que encontrar con el esp8266 y esp32 con linux que les puede ayudar en sus proyectos con arduino

comando
sudo apt remove brltty
