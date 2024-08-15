---
title: Agregar TelegramBot a un grupo con ESP32 y ESP8266
video_number: 3
date: 2022-09-30
video_id: GyBhjAA4jo0
repository: telegram_bot/03_TelegrarmBot_Grupo
tags:
  - telegram
  - esp32
  - esp8266
  - arduino
  - iot
  - bot

log:
  - title: usar librería de ArduinoJson 6.19.4 por recomendación de librería CTBot
  - title: al imprimir int64_t se tiene que convertir a string con la función int64ToAscii, toca importar la librería "Utilities.h" que viene de CTbot
  - title: usar librería de ArduinoJson 6.19.4 por recomendación de librería CTBot

topics:
  - title: Inicio
    time: "00:00"
  - title: Serie completa TelegramBot
    time: "00:26"
  - title: Problema con telegraBot en grupos
    time: "01:31"
  - title: Permisos para el telegramBot
    time: "01:53"
  - title: Código de demo telegramBot en grupos
    time: "02:20"
  - title: Prueba de telegramBot en grupos con esp
    time: "04:09"

links:
  - title: Librería CTBot
    url: https://github.com/shurillu/CTBot

videos:
  - title: Truco de concatenar en arduino
    url: series/arduino/basico/007_Como_concatenar_en_Arduino
  - title: Archivo token.h
    url: series/arduino/basico/006_Contraseña_Arduino


piezas:
  - title: esp32
  - title: esp8266

colaboradores:
  - title: Editor
    colaborador: ingjuan

miembros:
  - title: Maker ESP
    items:
      - title: Carlos Olivares Santis
  - title: Maker Mega
    items:
      - title: Otmaro Miguel
  - title: Maker Uno
    items:
      - title: EDUARDO MARCELO PALACIOS
      - title: Manuel Alegría
      - title: Lolailo Aviles Arroyo
      - title: Erebos Ubuntu

actualizado: true
---

Una excelente pregunta sobre como usar el telegramBot en grupos, que puede ser una buena idea para tus sistemas automatizados con tu esp32 o esp8266.

hoy veremos como hacerlo con arduino con ESP32 y ESP8266
