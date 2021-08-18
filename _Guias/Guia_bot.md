---
title: "Guia del Bot para Streaming de ALSW"
redirect_from:
  - "/bot"
---

Comandos especiales para el chat de Youtube y Twitch de las trasmiciones de ALSW tantos **ProgramacionNews**, **Gameplay** y **Grabacion**

Puede usarlos aqui:

- Link de Streaming [Youtube de ALSW](https://www.youtube.com/alswnet/live)
- Link de Streaming [Twitch de ALSW](https://www.twitch.tv/alswnet)
- Canal especial de Discord de la comunidad de ALSW (Pronto)

## Como usar comandos

- Escribe los comandos dentro del chat de ALSW
- bot no le importa si son mayusculas o minusculas
- Algunos comandos puede o necesitan parametros para funcionar como **color**
- Puede que te toque enviar mensajes entre tiempos por poticias de **span** de Youtube o Twitch

> **Ejemplo: Reiniciar**
>
> !reiniciar

# Fondo OBS

Fondo intreractivo y procesado en tiempo real el cual puede ser controado por comandos de chat.

EL fondo OBS esta echo en [P5.js](https://p5js.org) que es una libreria JavaScrips para crear animaciones, por lo cual es una pagina web que esta hostiada localmente en Rasberry Pi, recibe los mensajes por medio de MQTT para cambiar de color o animacion, los cuales se los envia por [ALSW_bot](https://github.com/alswnet/ALSW_Bot)

- Codigo fuente de [FondoOBS en Github](https://github.com/alswnet/FondoOBS)
- Demo Interactivo [Github Page](https://alswnet.github.io/FondoOBS/)

Algoritmos disponibles:

- Juego de la vida
- Wavy Field basado en trabajo [Stephen Edwards](https://editor.p5js.org/sventi555/sketches/NT68eSZPq)

Pronto Video de Juego de la vida en Youtube

## Comandos Disponibles para SuperChat o Bits

Pronto :')

## Comandos Disponibles para Todos

### reiniciar

Reinicia el Algoritmos, borra el fondo y inicializa los parametros del Algoritmos muchos generados por numeros aleatoreos

> **Ejemplo: reiniciar**
>
> !reiniciar

### Color Base

Cambia el color base de Algoritmos.

> **Ejemplo: Color Base a Rojo**
>
> !colorbase rojo

### Color Linea

Cambia el color linea de Algoritmos.

> **Ejemplo: Color Linea a Azul**
>
> !colorlinea azul

### Color Fondo

Cambia el color Fondo de Algoritmos.

> **Ejemplo: Color Fondo a Morado en hex**
>
> !colorfondo #ff00aa

## Colores

Hay dos formar de pasar colores a los comandos por nombre del color o hex ambas son formar aceptables para los comandos

### Lista Colores

colores disponibles:

```json
{
  "rojo": "#ff0000",
  "azul": "#0000ff",
  "verde": "#00ff00",
  "blanco": "#ffffff",
  "negro": "#000000",
  "gris": "#999999",
  "aqua": "#00ffff",
  "amarillo": "#ffff00",
  "naranja": "#ef7f1a",
  "morado": "#a349a4",
  "rosado": "#ff0080",
  "cafe": "#804000",
  "dorado": "#efb810"
}
```

Lista Completa en [Colores.json](https://github.com/alswnet/FondoOBS/blob/master/Colores.json)

> **Ejemplo: Color Fondo Agua**
>
> !colorfondo aqua

### Color hex

Tambien es posible usar codigo hex de 3 digitos o 6 digitos

> **Ejemplo: Color Fondo Salmon en exa**
>
> !colorfondo #fa8072

## Errores o ideas

Reporta error en el funcionamiento de los comandos o tiene alguna idea que podamos hacer en futuro reportala aqui [Aqui](https://github.com/alswnet/NocheProgramacion/issues/new)
