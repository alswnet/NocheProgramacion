---
title: Dos Telegram Bot en un ESP32 y ESP8266
video_number: 05
date: 2022-07-10
video_id: e8MAOgswt4g
repository: telegram_bot/05_Dos_TelegramBot_en_un_ESP
tags:
  - telegram
  - esp32
  - esp8266
  - arduino
  - iot
  - bot

topics:
  - title: Inicio
    time: "00:00"
  - title: Hoy resolveremos una duda
    time: "00:16"
  - title: Tokens
    time: "01:50"
  - title: Explicación de código
    time: "01:58"
  - title: Probando código
    time: "02:43"
  - title: Probando el bot
    time: "03:30"
  - title: Conclusión
    time: "03:47"

video:
  - title: Archivo token.h
    url: series/arduino/basico/006_Contraseña_Arduino

links:
  - title: Librería CTBot
    url: https://github.com/shurillu/CTBot

piezas:
  - title: esp32
  - title: esp8266

log:
  - title: usar librería de ArduinoJson 6.19.4 por recomendación de librería CTBot
  - title: al imprimir int64_t se tiene que convertir a string con la función int64ToAscii, toca importar la librería "Utilities.h" que viene de CTbot
  - title: usar librería de ArduinoJson 6.19.4 por recomendación de librería CTBot

colaboradores:
  - title: Editor
    colaborador: ingjuan

miembros:
  - title: Maker Mega
    items:
      - title: Otmaro Miguel
  - title: Maker Uno
    items:
      - title: Manuel Alegría
      - title: Lolailo Aviles Arroyo
      - title: Erebos Ubuntu

actualizado: true
---

Se puede tener dos telegram bot en un solo ESP32 y ESP8266, si se puede y en este tutorial te enseño como se hace.
