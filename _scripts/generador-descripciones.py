#!/usr/bin/python3
# -*- coding: utf-8 -*-

import yaml
import pandas as pd
from pathlib import Path, PosixPath

cantidadVideos = 0
cantidadSeries = 0

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
    config = leerArchivo(archivoConfig)[0]
    for foldesActual in config.get("folder"):
        buscarFolder(folderNoche.joinpath(foldesActual), folderNoche)
    print("Configs: ", config)

    mostarEstadisticas()

def leerArchivo(nombre):
    if not Path.exists(nombre):
        print(f"No exite el Archivo {nombre}")
        return None

    with open(nombre) as archivo:
        if str(nombre).endswith(".md"):
            return list(yaml.load_all(archivo, Loader=yaml.SafeLoader))
        
    return None

def SalvarArchivo(Archivo: str, data):
    """Sobre escribe data en archivo."""
    if type(Archivo) not in [str, PosixPath]:
        raise TypeError("Los Path tiene que ser str o PosixPath")

    # NombreArchivo = Path(Archivo).name
    RutaArchivo = Path(Archivo).parent
    # SufijoArchivo = Path(Archivo).suffix
    RutaArchivo.mkdir(parents=True, exist_ok=True)
    with open(Archivo, "w+") as f:
        f.write(data)

def procesarArchivo(archivo):

    if not archivo.exists():
        return False
    
    with open(archivo) as f:
        data = f.read()

    return data.__contains__("actualizado: true")

def buscarFolder(folder, nocheprogramacion):
    global cantidadVideos
    global cantidadSeries

    if type(folder) not in [str, PosixPath]:
        raise TypeError("Los Path tiene que ser str o PosixPath")
    if not folder.exists():
        return
    
    archivoIndex = folder.joinpath("index.md")
    if not procesarArchivo(archivoIndex):
        return
    dataIndex = leerArchivo(archivoIndex)
    print("\n Buscar en Folder ", folder.name)

    listaVideos = []
    for archivo in Path.iterdir(folder):
        rutaActual = folder.joinpath(archivo)
        
        
        if Path.is_dir(rutaActual):
            buscarFolder(rutaActual, nocheprogramacion)
        if Path.is_file(rutaActual):
            if not procesarArchivo(rutaActual) or rutaActual.name == "index.md":
                continue
            listaVideos.append(rutaActual.name)
        
    listaVideos.sort()
 
    for id in range(len(listaVideos)): 
        rutaVideo =  folder.joinpath(listaVideos[id])
        dataVideo = leerArchivo(rutaVideo)[0]
        descripcionVideo = leerArchivo(rutaVideo)[1]
        if id > 1:
            dataVideoAnterior = leerArchivo(folder.joinpath(listaVideos[id-1]))
        else:
            dataVideoAnterior = None    
        if id < len(listaVideos) -1:
            dataVideoSiquiente = leerArchivo(folder.joinpath(listaVideos[id+1]))
        else:
            dataVideoSiquiente = None

        cantidadVideos += 1
        dataFecha = dataVideo.get("date")
        fechaVideo = pd.to_datetime(dataFecha)
        anno = fechaVideo.year
        mes = fechaVideo.month
        url = f"_actualizado/{anno}/{mes}/{dataVideo.get('video_id')}.txt"

        print(mes, anno, url)
        print(nocheprogramacion.joinpath(url))
        
        print(dataVideo)

        descripcion = ""
        descripcion += leerArchivo(rutaVideo)[1]

        SalvarArchivo(nocheprogramacion.joinpath(url), descripcion)
        print()
    cantidadSeries += 1

def mostarEstadisticas():
    global cantidadVideos
    global cantidadSeries
    print(f"Cantidad Video procesados {cantidadVideos}")
    print(f"Series procesadas {cantidadSeries}")

if __name__ == "__main__":
    main()
   