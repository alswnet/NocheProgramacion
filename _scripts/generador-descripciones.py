#!/usr/bin/python3
# -*- coding: utf-8 -*-

import yaml
import os
from pathlib import Path, PosixPath


def main():
    print("Iniciando Generador Descripciones")
    folderNoche = Path(Path().resolve())
    while folderNoche.name != "1.NocheProgramacion":
        folderNoche = folderNoche.parent
        if folderNoche.name == "":
            raise Exception("No se encontro Folder de NocheProgramacion") 

    print("Folder NocheProgramacion; ", folderNoche.name)

    archivoConfig = Path(folderNoche, "_scripts/config.md")
    print("Archivo Config", archivoConfig)
    config = leerArchivo(archivoConfig)
    for foldesActual in config.get("folder"):
        buscarFolder(folderNoche.joinpath(foldesActual))
    print("Configs: ", config)

def leerArchivo(nombre):
    if not Path.exists(nombre):
        print(f"No exite el Archivo {nombre}")
        return None

    with open(nombre) as archivo:
        if str(nombre).endswith(".md"):
            return list(yaml.load_all(archivo, Loader=yaml.SafeLoader))[0]
        
    return None

def procesarArchivo(archivo):

    if not archivo.exists():
        return False
    
    with open(archivo) as f:
        data = f.read()

    return data.__contains__("actualizado: true")

def buscarFolder(folder):

    if type(folder) not in [str, PosixPath]:
        raise TypeError("Los Path tiene que ser str o PosixPath")
    if not folder.exists():
        return
    
    archivoIndex = folder.joinpath("index.md")
    if not procesarArchivo(archivoIndex):
        return
    dataIndex = leerArchivo(archivoIndex)
    print("\n Buscar en Folder ", folder)

    for archivo in Path.iterdir(folder):
        rutaActual = folder.joinpath(archivo)
        
        if Path.is_dir(rutaActual):
            
            buscarFolder(rutaActual)
        if Path.is_file(rutaActual):
            if not procesarArchivo(rutaActual) or rutaActual.name == "index.md":
                continue
            print(f"Archivo {rutaActual.name}")

if __name__ == "__main__":
    main()
   