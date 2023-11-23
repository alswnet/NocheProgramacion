#!/usr/bin/python3
# -*- coding: utf-8 -*-

import yaml
import shutil 
import pandas as pd
from pathlib import Path, PosixPath
from urllib.parse import urlparse

cantidadVideos = 0
cantidadSeries = 0
cantidadPendientes = 0

def main():
    print("Iniciando Generador Descripciones")
    folderNoche = Path(Path().resolve())
    while folderNoche.name != "1.NocheProgramacion":
        folderNoche = folderNoche.parent
        if folderNoche.name == "":
            raise Exception("No se encontro Folder de NocheProgramacion") 

    print("Folder NocheProgramacion; ", folderNoche.name)
    shutil.rmtree(folderNoche.joinpath("_actualizado"), ignore_errors=True)

    # TODO borrar videjos viejos

    archivoConfig = Path(folderNoche, "_scripts/config.md")
    print("Archivo Config", archivoConfig)
    config = leerArchivo(archivoConfig)[0]
    for folderActual in config.get("folder"):
        buscarFolder(folderNoche.joinpath(folderActual), folderNoche)
    print("Configs: ", config)

    mostarEstadisticas()

def leerArchivo(nombre):
    if not Path.exists(nombre):
        print()
        print(nombre)
        print(f"No exite el Archivo {nombre.name}")
        # quit()
        return None

    with open(nombre, encoding="utf-8") as archivo:
        if str(nombre).endswith(".md"):
            # TODO Capturar error en caso de carga
            try:
                data = yaml.load_all(archivo, Loader=yaml.SafeLoader)
                return list(data)
            except ValueError as ve:
                print(f"Error con el Valor en {nombre.name}: {ve}")
                quit()  
        elif str(nombre).endswith(".txt"):
            return archivo.read()
        
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

def dataPendiente(data, video):
    global cantidadPendientes
    if data.get("pendiente") is not None:
            cantidadPendientes += 1
            # TODO agregar colors
            print(f"Video: {video.get('title')} - {data.get('title')}")
            print("Pendiente Alerta")
            print()
            return True
    return False

def esUrl(url):
    try:
        result = urlparse(url)
        return all([result.scheme, result.netloc])
    except ValueError:
        return False
    
def buscaURLYoutube(url, nocheprogramacion):
    urlVideo = nocheprogramacion.joinpath(f"_{url}.md")
    if Path.exists(urlVideo):
        dataVideo = leerArchivo(urlVideo)
        return f"https://youtu.be/{dataVideo[0].get('video_id')}"
    urlIndex = nocheprogramacion.joinpath(f"_{url}/index.md")
    if Path.exists(urlIndex):
        print("urlIndex ", urlVideo)
        dataVideo = leerArchivo(urlVideo)
        return f"https://www.youtube.com/playlist?list={dataVideo[0].get('playlist_id')}"
    return "Muy Pronto"

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
    dataIndex = leerArchivo(archivoIndex)[0]
    idPlayList = dataIndex.get("playlist_id") 
    
    archivoRedes = nocheprogramacion.joinpath("_scripts/redes.txt")
    dataRedes = leerArchivo(archivoRedes)

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
            dataVideoAnterior = leerArchivo(folder.joinpath(listaVideos[id-1]))[0]
        else:
            dataVideoAnterior = None    
        if id < len(listaVideos) -1:
            dataVideoSiquiente = leerArchivo(folder.joinpath(listaVideos[id+1]))[0]
        else:
            dataVideoSiquiente = None

        cantidadVideos += 1
        dataFecha = dataVideo.get("date")
        fechaVideo = pd.to_datetime(dataFecha)
        anno = fechaVideo.year
        mes = fechaVideo.month
        url = f"_actualizado/{anno}/{mes}/{dataVideo.get('video_id')}.txt"

        descripcion = ""

        # Descripcions
        # TODO agreegar separador de descripciones
        descripcion += descripcionVideo
        descripcion += "\n\n"

        # ADS

        # Remake
        if dataVideo.get("remake"):
            urlRemake = dataVideo.get("remake")
            urlRemake = buscaURLYoutube(urlRemake, nocheprogramacion)
            descripcion = f"⚠️ Existe una NUEVA versión de este Video aqui 👉👉🏼👉🏾 {urlRemake} 👈🏾👈🏼👈\n\n" + descripcion

        # Correciones
        
        if idPlayList:

            # Video Anterior
            if dataVideoAnterior is not None:
                if idPlayList is not None:
                    descripcion += f"👈 Anterior Video {dataVideoAnterior.get('title')}: https://youtu.be/{dataVideoAnterior.get('video_id')}?list={idPlayList}\n"
                else:
                    descripcion += f"👈 Anterior Video {dataVideoAnterior.get('title')}: https://youtu.be/{dataVideoAnterior.get('video_id')}\n"
            
            # Video Siquiente
            if dataVideoSiquiente is not None:
                if idPlayList is not None:
                    descripcion += f"👉 Siguiente Video {dataVideoSiquiente.get('title')}: https://youtu.be/{dataVideoSiquiente.get('video_id')}?list={idPlayList}\n"
                else:
                    descripcion += f"👉 Siguiente Video {dataVideoSiquiente.get('title')}: https://youtu.be/{dataVideoSiquiente.get('video_id')}\n"

            # Lista de Reproduccion
            descripcion += f"🎥 Playlist({dataIndex.get('title')}): https://www.youtube.com/playlist?list={idPlayList}\n";
    
        # Videos Relecionados

        if dataVideo.get("videos"):
            descripcion += "\nVideos mencionados:\n"
            for video in dataVideo.get("videos"):
                if dataPendiente(video, dataVideo):
                    continue
                if video.get("video_id"):
                    descripcion += f" 🎞 {video.get('title')}: https://youtu.be/{video.get('video_id')}\n"
                elif video.get("url"):
                    if esUrl(video.get("url")):
                        descripcion += f" 🎞 ${video.get('title')}: {video.get('video_id')}\n"
                    else:
                        pass
                        # TODO buscar video en referencia
                        descripcion += f" 🎞  "

        # NocheProgramacion y Adjuntos

        # Links
        if dataVideo.get("links"):
            descripcion += "\nLink referencia:\n"
            for links in dataVideo.get("links"):
                if dataPendiente(links, dataVideo):
                    continue
                descripcion += f" 🔗 {links.get('title')} {links.get('url')}\n"

        # Compones y Links Amazon

        # Extra

        # Indice
        if dataVideo.get("topics"): 
            descripcion += "\n🕓 Índice:\n"
            for indice in dataVideo.get("topics"):
                descripcion += f"{indice.get('time')} {indice.get('title')}\n"

        # Redes Sosociales
        if dataRedes:
            descripcion += "\n"
            descripcion += dataRedes

        # Colabodores
        
        # Tags
        descripcion += "\n#ChepeCarlos"

        # Miembros

        # CTA Miembros
        descripcion += "\n"
        descripcion += "\n🔭 Agrega tu nombre, Únete tú también https://www.youtube.com/@chepecarlo/join 🔭"
        descripcion += "\n👊 Avances Exclusivo para Miembros: https://nocheprogramacion.com/miembros 👊"
     
        # Salvar archivo
        SalvarArchivo(nocheprogramacion.joinpath(url), descripcion)

    cantidadSeries += 1

def mostarEstadisticas():
    global cantidadVideos
    global cantidadSeries
    global cantidadPendientes
    print(f"Cantidad Totales Procesadas")
    print(f"Video: {cantidadVideos}")
    print(f"Series: {cantidadSeries}")
    print(f"Pendientes: {cantidadPendientes}")

if __name__ == "__main__":
    main()
   