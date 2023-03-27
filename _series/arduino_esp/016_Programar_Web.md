---
title: Forma oculta de como programar tu ESP32 y ESP8266
video_number: 16
date: 2023-03-06
video_id: CMglsVCi2t8
repository: arduino_esp/016_update
tags:
  - arduino
  - iot
  - ota
  - esp32
  - esp8266

variations:
  - name: Update Demo
    lang: arduino
    folder: arduino/UpdateDemo
  - name: Update Demo Estatico
    lang: arduino
    folder: arduino/UpdateDemoEstatico

topics:
  - title: Inicio
    time: "00:00"
  - title: Que es OTA
    time: "00:27"
  - title: Recomendación
    time: "01:22"
  - title: Demostración del funcionamiento
    time: "01:50"
  - title: Como generar un binario desde Arduino IDE
    time: "03:11"
  - title: Como se cargar un nuevo codigo (Binario)
    time: "04:25"
  - title: Explicación del código
    time: "05:19"
  - title: Paso 1
    time: "07:32"
  - title: Paso 2
    time: "07:43"
  - title: Prueba del código
    time: "09:35"
  - title: Comando Automático para cargar código
    time: "10:18"

videos:
  - title: mDNS
    url: series/arduino_esp/008_mdns_esp

piezas:
  - title: esp32
  - title: esp8266

colaboradores:
  - title: Editor
    colaborador: ingjuan
  - title: fotógrafa
    colaborador: paty

miembros:
  - title: Maker ESP
    items:
      - title: nery kastillo
      - title: Carlos Olivares Santis
  - title: Maker Uno
    items:
      - title: Waldo Ratti
      - title: Claudio Bloise
      - title: EDUARDO MARCELO PALACIOS
      - title: Manuel Alegría
      - title: Lolailo Aviles Arroyo

actualizado: true
---

Vemos una manera especial de poder programar nuestro proyecto por wifi usando una pagina web o OTA, que puede muy util para proyecto con ESP32 y ESP8266

Comando Automático:
curl -F "image=@codigo.bin" esp-update.local/actualizar
