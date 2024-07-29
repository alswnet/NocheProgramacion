---
title: Depuración por WIFI con el ESP32 y ESP8266
video_number: 18
date: 2023-4-26
video_id: a-YILV2ziKs
repository: arduino_esp/018_Depurar_Wifi
tags:
  - arduino
  - iot
  - esp8266
  - esp32

log:
  - title: Problemas con la Librería en la Version 1.3.0 en Arduino IDE 2.x con Addons esp32 2.x

topics:
  - title: inicio
    time: "00:00"
  - title: Depuración por WiFi
    time: "01:09"
  - title: Instalar librería Telnet
    time: "01:30"
  - title: Como funciona Telnet
    time: "03:21"
  - title: Probando código en el ESP32
    time: "06:02"
  - title: Instalando Telnet en Linux
    time: "06:56"
  - title: Enviar mensajes a esp por wifi
    time: "07:32"
  - title: Para que sirve telnet en esp
    time: "08:20"
  - title: Usando mdns para depuración por wifi
    time: "09:12"
  - title: Telnet en Windows
    time: "09:51"
  - title: Probando el código en ESP8266
    time: "09:54"
  - title: Como nos conectamos por Telnet en Windows
    time: "10:57"
  - title: Demostración de uso en un proyecto real
    time: "13:19"

links:
  - title: Librería TelnetStream de Juraj Andrassy
    url: https://github.com/jandrassy/TelnetStream
  - title: Sitio Web Putty
    url: https://www.chiark.greenend.org.uk/~sgtatham/putty/

videos:
  - title: Que es mDNS
    url: tutoriales/072_Que_es_mDNS
  - title: Tutorial de Millis
    url: series/arduino/avanzado/008_millis_arduino
  - title: Archivo token.h
    url: series/arduino/basico/006_Contraseña_Arduino

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
      - title: ramiro gattas
      - title: Carlos Flores
      - title: nery kastillo
      - title: Carlos Olivares Santis
  - title: Maker Uno
    items:
      - title: Manuel Alegría
      - title: Dark alambrito
      - title: Fernando Armada
      - title: Waldo Ratti
      - title: Claudio Bloise
      - title: EDUARDO MARCELO PALACIOS
      - title: Lolailo Aviles Arroyo

actualizado: true
---

La depuración serial es muy util, pero como lo hacemos si el proyecto es por wifi, para esto podemos usar telnet para un remplazo de tener conectado nuestro proyecto por cable usb
