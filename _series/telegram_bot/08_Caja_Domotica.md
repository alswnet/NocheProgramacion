---
title: Descubre como controlar tu Casa con TelegramBot
video_number: 8
date: 2023-12-20
video_id: gE9GCR9vOC0
repository: telegram_bot/08_Caja_Domotica
tags:
  - telegram
  - esp32
  - esp8266
  - domotica
  - iot

log:
  - title: usar librería de ArduinoJson 6.19.4 por recomendación de libreria CTBot

topics:
  - title: Inicio
    time: "00:00"
  - title: Saludo
    time: "00:43"
  - title: Materiales
    time: "01:39"
  - title: Vamos con el código
    time: "02:40"
  - title: Estados del sistema
    time: "03:06"
  - title: Estructuras
    time: "04:42"
  - title: Agregando Relé
    time: "05:51"
  - title: Código concatenar en serial
    time: "06:51"
  - title: Archivo data.h
    time: "07:02"
  - title: configuración Wifi
    time: "07:32"
  - title: Token del bot
    time: "07:39"
  - title: ID de usuarios
    time: "07:46"
  - title: Nombre identificador
    time: "08:05"
  - title: Como llamar cada Relé
    time: "08:31"
  - title: Código para Wifi
    time: "09:17"
  - title: Comunicación Serial
    time: "12:27"
  - title: Telnet
    time: "12:49"
  - title: OTA
    time: "13:07"
  - title: EL poderoso LED
    time: "13:27"
  - title: Ticker
    time: "13:51"
  - title: Estados del led
    time: "15:11"
  - title: EL Bot
    time: "15:54"
  - title: Primera prueba del código
    time: "17:17"
  - title: Probando estado de LED
    time: "18:00"
  - title: Permisos del Bot
    time: "19:45"
  - title: Comando Bot - Estado
    time: "20:05"
  - title: Comando Bot - Opciones
    time: "20:35"
  - title: Bot - Teclado y opciones
    time: "20:49"
  - title: Memoria
    time: "24:32"
  - title: Memoria - Salvar Archivo
    time: "24:54"
  - title: Memoria - Leer Archivo
    time: "25:38"
  - title: Memoria - Formatear
    time: "26:01"
  - title: Memoria - Formatear por el Bot
    time: "26:33"
  - title: Memoria - Formatear por comunicación serial
    time: "26:56"
  - title: Memoria - Formatear por Telnet
    time: "27:29"
  - title: Prueba final
    time: "27:58"

links:
  - title: Modelo de la Caja Domótica
    url: https://www.printables.com/es/model/624197-domotic-power-strip

videos:
  - title: Serie de esp
    url: series/arduino_esp
  - title: Como Armar Caja Domótica
    url: listas/06_Armando_Circuitos/01_Caja_Domotica
  - title: Estructura en Arduino
    pendiente: true
  - title: Modulo Relay
    pendiente: true
  - title: if aplastado en Arduino
    pendiente: true
  - title: Concatenar en Arduino
    url: series/arduino/basico/07_Como_concatenar_en_Arduino
  - title: Que es mDNS
    url: tutoriales/072_Que_es_mDNS
  - title: Que es Ticker
    url: series/arduino_esp/006_Libreria_Ticker

piezas:
  - title: esp32
  - title: esp8266
  - title: fuente buck
  - title: resistencia 330 ohms
  - title: resistencia 10k
  - title: modulo relay 5v
  - title: boton
  - title: led
  - title: tuercas palanca
  - title: tuercas torcidas

colaboradores:
  - title: Editor
    colaborador: ingjuan
  - title: Camarógrafa
    colaborador: paty

miembros:
  - title: Maker ESP
    items:
      - title: nery kastillo
  - title: Maker Mega
    items:
      - title: Mario Radich
  - title: Maker Uno
    items:
      - title: Manuel Alegría
      - title: Jorge Xalambri
      - title: federicoymarta garcia garcia
      - title: Fernando Armada
      - title: Waldo Ratti
      - title: Claudio Bloise
      - title: Lolailo Aviles Arroyo

actualizado: true
---

Veamos un proyecto completo de Domótica con telegram, donde veremos paso por paso como controlar tus dispositivos fuera y dentro de tu casa con un bot
