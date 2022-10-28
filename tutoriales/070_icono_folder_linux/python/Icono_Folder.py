#!/usr/bin/python3
# -*- coding: utf-8 -*-
# Creado ChepeCarlos de ALSW
# Tutorial Completo en https://nocheprogramacion.com
# Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

import os
import argparse

parser = argparse.ArgumentParser(description='Heramienta Asignar iconos a folder')
parser.add_argument('--icono', '-i', help="Nombre el icono")


def ActualizarIconoFolder(Icono=".icono.png"):
    """Asignar un icono a folder recursicamente para gtk."""
    cantidad = 0

    FolderIgnorar = [".git", "venv", "node_modules", "BL_proxy", "bpsrender"]

    Ruta_Actual = os.getcwd()

    for ruta, directorios, archivos in os.walk(Ruta_Actual, topdown=True):

        for Folder in FolderIgnorar:
            if Folder in directorios:
                directorios.remove(Folder)

        for Archivo in archivos:
            if Archivo == Icono:
                cantidad += 1
                print(f"Asignando icono {Icono} a {ruta}")
                os.system(f"gio set {ruta} metadata::custom-icon {Icono}")

    print(f"Cantidad iconos asignados {cantidad}")


if __name__ == "__main__":

    args = parser.parse_args()
    print("Iniciando programa Basket")
    if args.icono:
        ActualizarIconoFolder(args.icono)
    else:
        ActualizarIconoFolder()
