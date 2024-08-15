---
title: Crea tu propia Alarma Vigilancia con TelegramBot
video_number: 7
date: 2022-09-19
video_id: TDsN1eN5b7I
repository: telegram_bot/07_SistemaVigilancia
tags:
  - telegram
  - esp32
  - esp8266
  - arduino
  - iot
  - bot

log:
  - title: Cambiando el tipo de variable IDchat de int a int64_t , porque el tamaño del id puede ser mas grande que int
  - title: al imprimir int64_t se tiene que convertir a string con la funcion int64ToAscii, toca importar la libreria "Utilities.h" que viene de CTbot
  - title: usar librería de ArduinoJson 6.19.4 por recomendación de libreria CTBot

topics:
  - title: Inicio
    time: "00:00"
  - title: Materiales
    time: "01:44"
  - title: Cuidado con el voltaje
    time: "02:01"
  - title: Como funciona el sistema
    time: "03:10"
  - title: Veamos el código
    time: "07:47"
  - title: Primera prueba
    time: "08:16"
  - title: No olvides el archivo token
    time: "08:22"
  - title: Explicación del código
    time: "09:05"
  - title: Teclado en bot telegram
    time: "10:17"
  - title: Uso de milis
    time: "11:40"
  - title: Detener Alarma
    time: "14:01"
  - title: Limitar control por usuario
    time: "15:42"
  - title: Uso de memoria interna
    time: "21:36"
  - title: Despedida
    time: "24:02"
  - title: Pantalla Final
    time: "24:27"

links:
  - title: Librería CTBot
    url: https://github.com/shurillu/CTBot

piezas:
  - title: esp32
  - title: esp8266

videos:
  - title: Truco de concatenar en arduino
    url: series/arduino/basico/007_Como_concatenar_en_Arduino
  - title: Sensor PIR con Arduino
    url: series/arduino/modulos/01_sensor_pir
  - title: Tutorial de Millis
    url: series/arduino/avanzado/008_millis_arduino
  - title: Archivo token.h
    url: series/arduino/basico/006_Contraseña_Arduino

colaboradores:
  - title: Editor
    colaborador: ingjuan
  - title: Camarógrafa
    colaborador: paty

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

Hoy haremos un proyecto completo un sistema de vigilancia que te envía mensajes de inmediato a tu telegram cada ves que detecta movimiento.
Para esto usaremos un sensor pir, Arduino ESP32 o ESP8266, Buzzer y un led que puede conseguir en muchas tienda de electronica, espero que te diviertas armándolo.
