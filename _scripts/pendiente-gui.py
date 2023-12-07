#!/usr/bin/python3
# -*- coding: utf-8 -*-

from PySide6.QtWidgets import (
    QApplication, QMainWindow, QLabel, QTabWidget, QWidget, QVBoxLayout)
from PySide6.QtCore import QSize
import sys
import os
import json
import yaml
from pathlib import Path, PosixPath


def obtenerArchivo(Archivo):
    if type(Archivo) not in [str, PosixPath]:
        raise TypeError("El Archivo tiene que ser str o PosixPath")

    if os.path.exists(Archivo):
        try:
            with open(Archivo) as f:
                if str(Archivo).endswith(".json"):
                    return json.load(f)
                elif str(Archivo).endswith(".md"):
                    return list(yaml.load_all(f, Loader=yaml.SafeLoader))[0]
                elif str(Archivo).endswith(".txt"):
                    return f.read()
        except Exception as e:
            print(f"Archivo[Error] {Archivo} {e}")

class Caja(QLabel):
    def __init__(self, data):
        super().__init__()
        self.setText(data.get("titulo"))
        self.setStyleSheet(f"background-color:{'blue'}")


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        print("Iniciando Generador Descripciones")
        folderNoche = Path(Path().resolve())
        # TODO mejorar busqueda automatica con el nombre en config.md
        while folderNoche.name != "1.NocheProgramacion":
            folderNoche = folderNoche.parent
            if folderNoche.name == "":
                raise Exception("No se encontro Folder de NocheProgramacion") 

        print(f"Folder NocheProgramacion {folderNoche.name}")
        archivoConfig = Path(folderNoche, "_scripts/config.md")
        config = obtenerArchivo(archivoConfig)
        archivoPendintes = folderNoche.joinpath(config.get("folder_data")).joinpath(config.get("archivo_pendiente"))
        dataPendiente = obtenerArchivo(archivoPendintes)
        print(dataPendiente)

        layout = QVBoxLayout()

        for pendiente in dataPendiente:
            layout.addWidget(Caja(pendiente))

        layout.setContentsMargins(0, 0, 0, 0)

        # modificamos el espaciado
        layout.setSpacing(0)

        # creamos un dummy widget para hacer de contenedor
        widget = QWidget()

        # le asignamos el layout
        widget.setLayout(layout)

        # establecemos el dummy widget como widget central
        self.setCentralWidget(widget)

       
        self.setMinimumSize(QSize(480, 320))


if __name__ == "__main__":
    app = QApplication(sys.argv)
    ventana = MainWindow()
    ventana.show()
    sys.exit(app.exec_())
