---
title: "exa el mejor ls"
video_number: 2
date: 2021-06-14
video_id: lsozcDjzkuY
tags:
  - linux
  - comando

topics:
  - title: Introducción
    time: "00:00"
  - title: Que es exa
    time: "00:28"
  - title: Instalar exa en Linux
    time: "00:58"
  - title: Problema Linux mint 20.1
    time: "01:12"
  - title: Probando exa
    time: "01:53"
  - title: Alias de exa a ls
    time: "02:42"
  - title: Archivo Especial para Alias
    time: "02:51"
  - title: Nuevo Comando ls
    time: "03:29"
  - title: Comando ld Directorios
    time: "03:41"
  - title: Comando ll formato largo
    time: "03:54"
  - title: Comando l. solo ocultos
    time: "04:15"
  - title: Comando li innora gitinore
    time: "04:23"
  - title: Comando lg mostar esta de git
    time: "04:54"
  - title: comando lp octal
    time: "05:34"
  - title: Resumen
    time: "05:51"

links:
  - title: "Pagina Exa"
    url: "https://the.exa.website/"
  - title: "Github Exa"
    url: "https://github.com/ogham/exa"
  - title: "Mis Alias de exa de bash_aliases"
    url: "https://github.com/chepecarlos/dotfile/blob/master/.bash_aliases"
  - title: "Mi bashrc para llamar los alias"
    url: "https://github.com/chepecarlos/dotfile/blob/master/.bashrc"

actualizado: true
---

exa es el nuevo y mas moderno comando ls para nuestro linux, es momento de actualizar y mejor nuestra flujo de trabajo en la terminal

Instalar en Linux mint
unzip exa-(vercion).zip
cp bin/exa ~/.local/bin/exa
sudo cp completions/exa.bash /etc/bash_completion.d/exa.bash
sudo cp man/exa.1 /usr/share/man/man1/exa.1
