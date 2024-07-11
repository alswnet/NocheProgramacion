#!/usr/bin/python3
# -*- coding: utf-8 -*-

import yaml
import json
import shutil 
import pandas as pd
from pathlib import Path, PosixPath
from urllib.parse import urlparse

class color:
    PURPLE = "\033[95m"
    CYAN = "\033[96m"
    DARKCYAN = "\033[36m"
    BLUE = "\033[94m"
    GREEN = "\033[92m"
    YELLOW = "\033[93m"
    RED = "\033[91m"
    BOLD = "\033[1m"
    UNDERLINE = "\033[4m"
    END = "\033[0m"

cantidadVideos = 0
cantidadSeries = 0
cantidadPendientes = 0
noProcesar = 0
noAmazon = 0

config = None
producto = None
infoPendiente = list()

def main():
    global config
    global producto
    print("Iniciando Generador Descripciones")
    folderNoche = Path(Path().resolve())
    # TODO mejorar busqueda automatica con el nombre en config.md
    while folderNoche.name != "01.NocheProgramacion":
        folderNoche = folderNoche.parent
        if folderNoche.name == "":
            raise Exception("No se encontro Folder de NocheProgramacion") 

    print(f"Folder NocheProgramacion {folderNoche.name}")
    archivoConfig = Path(folderNoche, "_scripts/config.md")
    config = leerArchivo(archivoConfig)
    archivoProducto = Path(folderNoche, "_scripts/producto.md")
    producto = leerArchivo(archivoProducto).get("productos")
    canales = config.get("canal_extra")

    print("Borrando todas los Archivos Anteriores")
    shutil.rmtree(folderNoche.joinpath(config.get("folder_archivos")), ignore_errors=True)
    shutil.rmtree(folderNoche.joinpath(config.get("folder_data")), ignore_errors=True)
    for canal in canales:
        shutil.rmtree(folderNoche.joinpath(f"{config.get('folder_archivos')}_{canal}"), ignore_errors=True)

    for folderActual in config.get("folder"):
        buscarFolder(folderNoche.joinpath(folderActual), folderNoche, folderActual)
    mostarEstadisticas()

    rutaPendiente = folderNoche.joinpath(config.get("folder_data")).joinpath("pendiente.json")
    SalvarArchivo(rutaPendiente, infoPendiente)


def leerDescripcion(nombre):
    if not Path.exists(nombre):
        print()
        print(nombre)
        print(f"No exite el Archivo {nombre.name}")
        return None
    
    with open(nombre, encoding="utf-8") as archivo:
        if str(nombre).endswith(".md"):
            texto = archivo.read()
            texto = texto.split("---")[2].strip()
            return texto
        
    return None


def leerArchivo(nombre):
    if not Path.exists(nombre):
        print()
        print(nombre)
        print(f"No exite el Archivo {nombre.name}")
        # quit()
        return None
    
    # TODO revisas se se puede leer
    # if not procesarArchivo(nombre):
    #     return None

    with open(nombre, encoding="utf-8") as archivo:
        if str(nombre).endswith(".md"):
            try:
                data = yaml.load_all(archivo, Loader=yaml.SafeLoader)
                return list(data)[0]
            except ValueError as error:
                print(f"Error con el Valor en {nombre.name}: {error}")
                quit()  
            except yaml.scanner.ScannerError as error:
                print(f"Error con el formato {nombre.name}: {error}")
                quit()
                pass
        elif str(nombre).endswith(".txt"):
            return archivo.read()
        
    return None

def SalvarArchivo(Archivo: str, data):
    """Sobre escribe data en archivo."""
    if type(Archivo) not in [str, PosixPath]:
        raise TypeError("Los Path tiene que ser str o PosixPath")

    RutaArchivo = Path(Archivo).parent
    SufijoArchivo = Path(Archivo).suffix
    RutaArchivo.mkdir(parents=True, exist_ok=True)
    with open(Archivo, "w+") as f:
        if SufijoArchivo == ".json":
            json.dump(data, f, indent=2)
        else:
            f.write(data)

def procesarArchivo(archivo):
    global noProcesar

    if not archivo.exists():
        return False
    
    with open(archivo) as f:
        data = f.read()

    procesar = data.__contains__("actualizado: true")
    if not procesar:
        noProcesar += 1

    return procesar

def dataPendiente(data, video, ruta, tipo):
    global cantidadPendientes
    if data.get("pendiente") is not None:
            cantidadPendientes += 1
            data = {
                "titulo": video.get('title'),
                "tipo": tipo,
                "data": data.get('title'),
                "url": ruta.name
            }
            infoPendiente.append(data)
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
        return f"https://youtu.be/{dataVideo.get('video_id')}"
    urlIndex = nocheprogramacion.joinpath(f"_{url}/index.md")
    if Path.exists(urlIndex):
        dataVideo = leerArchivo(urlIndex)
        return f"https://www.youtube.com/playlist?list={dataVideo.get('playlist_id')}"
    return "Muy Pronto"

def linkAmazon(idAmazon):
    global config
    texto = ""
    for codigoAmazon in config.get("amazon"):
        pais = codigoAmazon.get("pais")
        emoji = codigoAmazon.get("emoji")
        if isinstance(idAmazon, str):
            texto += f"    {emoji} {pais}: {codigoAmazon.get('url')}/dp/{idAmazon}/ref=nosim?tag={codigoAmazon.get('codigo')}\n"
        elif isinstance(idAmazon, list):
            for idActual in idAmazon:
                texto += f"    {emoji} {pais}: {codigoAmazon.get('url')}/dp/{idActual}/ref=nosim?tag={codigoAmazon.get('codigo')}\n"
        else:
            print(f"Error en formato de Producto {idAmazon}-{type(idAmazon)}")
    return texto

def buscarAmazon(nombreProducto, titulo, ruta):
    global config
    global producto
    global noAmazon
    texto = ""
    for productoActual in producto:
        if nombreProducto.lower() == productoActual.get("name").lower():
            for codigoAmazon in config.get("amazon"):
                pais = codigoAmazon.get("pais")
                emoji = codigoAmazon.get("emoji")
                codigos = productoActual.get(pais.lower())
                if isinstance(codigos, str):
                    texto += f"    {emoji} {pais}: {codigoAmazon.get('url')}/dp/{codigos}/ref=nosim?tag={codigoAmazon.get('codigo')}\n"
                elif isinstance(codigos, list):
                    texto += f"    {emoji} {pais}:\n"
                    for codigoActual in codigos:
                        texto += f"       {codigoAmazon.get('url')}/dp/{codigoActual}/ref=nosim?tag={codigoAmazon.get('codigo')}\n"
                else: 
                    noAmazon += 1
                    texto += f"       😱Pendiente😱\n"
                    data = {
                        "titulo": titulo,
                        "tipo": "producto",
                        "data": f"{pais}-{nombreProducto}",
                        "url": ruta
                    }
                    infoPendiente.append(data)
            return texto
    noAmazon += 1
    data = {
        "titulo": titulo,
        "tipo": "producto",
        "data": nombreProducto,
        "url": ruta
    }
    infoPendiente.append(data)
    texto += f"       😱Pendiente😱\n"
    return texto

def confirmarData(dataVideo, rutaVideo, descripcionVideo, nocheprogramacion, folderBusqueda):

    # Comprobar que hay descripcion
    idYoutube = dataVideo.get("video_id")
    if descripcionVideo is None or descripcionVideo == "":
        print(f"{color.RED}Error[descripcion]{color.END} '{descripcionVideo}' - {idYoutube}")
        print(f"Ruta {rutaVideo}")
        exit()

    # Comprobar que el existo titulo
    tituloActual = dataVideo.get("title")
    if tituloActual is None:
        print(f"{color.RED}Error[title]{color.END} '{tituloActual}' - {idYoutube}")
        print(f"Ruta {rutaVideo}")
        exit()

    # Comprobar que Video ID es un enterró
    idActual = dataVideo.get("video_number")
    if idActual is None or (not isinstance(idActual, int) and not isinstance(idActual, float)):
        print(f"{color.RED}Error[video_number]{color.END} {idActual} 'int' {idYoutube}")
        print(f"Ruta {rutaVideo}")
        exit()

    # Comprobar que repository existe
    descarga = dataVideo.get("repository")
    if descarga is not None:
        rutaDescargables = f"{nocheprogramacion}/{str(folderBusqueda).removeprefix('_')}/{descarga}" 
        if not Path(rutaDescargables).exists():
            print(f"{color.RED}Error[repository]{color.END} no existe {descarga} - {idYoutube}")
            print(f"Ruta {rutaVideo}")
            # exit()

def buscarFolder(folder, nocheprogramacion, folderBusqueda):
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
    idPlayList = dataIndex.get("playlist_id") 
    canal = dataIndex.get("canal")
    
    if canal is not None and "ctrlz" in canal:
        archivoRedes = nocheprogramacion.joinpath("_scripts/redes_ctrlz.txt")
        archivoMejores = nocheprogramacion.joinpath("_scripts/mejores_ctrlz.txt")
    else:
        archivoRedes = nocheprogramacion.joinpath("_scripts/redes.txt")
        archivoMejores = nocheprogramacion.joinpath("_scripts/mejores.txt")

    dataRedes = leerArchivo(archivoRedes)
    dataMejores = leerArchivo(archivoMejores)
    listaVideos = []
    for archivo in Path.iterdir(folder):
        rutaActual = folder.joinpath(archivo)
        
        if Path.is_dir(rutaActual):
            buscarFolder(rutaActual, nocheprogramacion, folderBusqueda)
        if Path.is_file(rutaActual):
            if not procesarArchivo(rutaActual) or rutaActual.name == "index.md":
                continue
            listaVideos.append(rutaActual.name)
        
    listaVideos.sort()
 
    for id in range(len(listaVideos)): 
        rutaVideo =  folder.joinpath(listaVideos[id])
        dataVideo = leerArchivo(rutaVideo)
        descripcionVideo = leerDescripcion(rutaVideo)

        confirmarData(dataVideo, rutaVideo, descripcionVideo ,nocheprogramacion, folderBusqueda)

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
        try:
            fechaVideo = pd.to_datetime(dataFecha)
        except ValueError as error:
            print(f"Error en Fecha en: {rutaVideo}: {error}")
            quit()
        anno = fechaVideo.year
        mes = fechaVideo.month
        if mes < 10:
            mes = '0' + str(mes)

        if canal is not None:
            url = f"{config.get('folder_archivos')}_{canal}/{anno}/{mes}/{dataVideo.get('video_id')}.txt"
        else:        
            url = f"{config.get('folder_archivos')}/{anno}/{mes}/{dataVideo.get('video_id')}.txt"

        descripcion = ""

        # Descripción
        descripcion += descripcionVideo

        # SeoMostar
        lineaMaxima = 90
        lineas = descripcion.split('\n')
        if len(descripcion) <= lineaMaxima:
            descripcion += "\n"

        if len(descripcion) <= lineaMaxima * 2:
            if len(lineas) <= 2:
                descripcion += "\n👇 👇 HAZ CLICK 👇 👇\n"
            else:
                nuevaDescripcion = lineas[0]
                nuevaDescripcion += "\n👇 👇 HAZ CLICK 👇 👇"
                for linea in lineas[1:]:
                    nuevaDescripcion += f"\n{linea}"
                descripcion = nuevaDescripcion
        descripcion += "\n"

        # Todo buscar numero correcto para enter
        if len(descripcion) >= 160:
            descripcion += "\n"

        # ADS
        if dataVideo.get("ads"):
            for ads in dataVideo.get("ads"):
                if dataPendiente(ads, dataVideo, rutaVideo, "ads"):
                    continue
                descripcion += f"💸 {ads.get('title')}: {ads.get('url')}\n"
            descripcion += "\n"

        # Remake
        if dataVideo.get("remake"):
            urlRemake = dataVideo.get("remake")
            urlRemake = buscaURLYoutube(urlRemake, nocheprogramacion)
            descripcion = f"⚠️ Existe una NUEVA versión de este Video aqui 👉👉🏼👉🏾 {urlRemake} 👈🏾👈🏼👈\n\n" + descripcion

        # Correciones
        if dataVideo.get("log"):
            descripcion += "⚠️ Correcciones ⚠️:\n"
            for correcion in dataVideo.get("log"):
                if dataPendiente(correcion, dataVideo, rutaVideo, "log"):
                    descripcion += f"  😱Pendiente😱"
                    continue
                descripcion += f"  ♦️ {correcion.get('title')}\n"
                
        # Siquiente y Anterior Video
        if idPlayList:
            # Video Anterior
            if dataVideoAnterior is not None:
                if idPlayList is not None:
                    descripcion += f"👈 Anterior Video \"{dataVideoAnterior.get('title')}\": https://youtu.be/{dataVideoAnterior.get('video_id')}?list={idPlayList}\n"
                else:
                    descripcion += f"👈 Anterior Video \"{dataVideoAnterior.get('title')}\": https://youtu.be/{dataVideoAnterior.get('video_id')}\n"
            
            # Video Siquiente
            if dataVideoSiquiente is not None:
                if idPlayList is not None:
                    descripcion += f"👉 Siguiente Video \"{dataVideoSiquiente.get('title')}\": https://youtu.be/{dataVideoSiquiente.get('video_id')}?list={idPlayList}\n"
                else:
                    descripcion += f"👉 Siguiente Video \"{dataVideoSiquiente.get('title')}\": https://youtu.be/{dataVideoSiquiente.get('video_id')}\n"

            # Lista de Reproduccion
            descripcion += f"🎥 Playlist({dataIndex.get('title')}): https://www.youtube.com/playlist?list={idPlayList}\n";
            descripcion += "\n"
    
        # Videos Relecionados
        if dataVideo.get("videos"):
            descripcion += "Videos mencionados:\n"
            for video in dataVideo.get("videos"):
                if dataPendiente(video, dataVideo, rutaVideo, "videos"):
                    descripcion += f" 🎞 {video.get('title')}: 😱Pendiente😱\n"
                    continue
                if video.get("video_id"):
                    descripcion += f" 🎞 {video.get('title')}: https://youtu.be/{video.get('video_id')}\n"
                elif video.get("url"):
                    if esUrl(video.get("url")):
                        descripcion += f" 🎞 {video.get('title')}: {video.get('video_id')}\n"
                    else:
                        urlBuscada = buscaURLYoutube(video.get("url"), nocheprogramacion)
                        descripcion += f" 🎞 {video.get('title')}: {urlBuscada}\n"
            descripcion += "\n"

        # NocheProgramacion y Adjuntos
        urlArticulo = str(rutaVideo).split("NocheProgramacion/_")
        urlArticulo = urlArticulo[1].removesuffix(".md")
        if dataVideo.get("repository"):
            direccionDescargables = dataVideo.get("repository")
            rutaDescargables = f"{nocheprogramacion}/{str(folderBusqueda).removeprefix('_')}/{direccionDescargables}" 
            if Path(rutaDescargables).exists():
                descripcionDescarga = f"💻 Descarga("
                rutaBuscar = Path.iterdir(Path(rutaDescargables))
                cantidadDescargables = len(list(Path.iterdir(Path(rutaDescargables))))

                for i, folderDescargable in enumerate(rutaBuscar):
                    if(cantidadDescargables -1 == i):
                        descripcionDescarga += f"{folderDescargable.name.upper()}"
                    else:
                        descripcionDescarga += f"{folderDescargable.name.upper()}, "

                descripcionDescarga += f"): https://nocheprogramacion.com/{urlArticulo}.html\n"
                descripcion += descripcionDescarga
            else:
                data = {
                    "titulo": dataVideo.get('title'),
                    "tipo": "descargables",
                    "data": urlArticulo,
                    "url": rutaVideo.name
                }
                infoPendiente.append(data)
                descripcion += f"💻 Descarga(Pendiente): https://nocheprogramacion.com/{urlArticulo}.html\n"
        else:
            descripcion += f"💻 Articulo: https://nocheprogramacion.com/{urlArticulo}.html\n"
        descripcion += "\n"

        # Links
        if dataVideo.get("links"):
            descripcion += "Link referencia:\n"
            for links in dataVideo.get("links"):
                if dataPendiente(links, dataVideo, rutaVideo, "links"):
                    descripcion += f"  🔗 {links.get('title')}: 😱Pendiente😱\n"
                    continue
                descripcion += f"  🔗 {links.get('title')}: {links.get('url')}\n"
            descripcion += "\n"

        # Compones y Links Amazon
        if dataVideo.get("piezas"):
            descripcion += "Componentes electrónicos:\n"
            for pieza in dataVideo.get("piezas"):
                if dataPendiente(pieza, dataVideo, rutaVideo, "productos"):
                    continue
                if pieza.get("url"): 
                    urlPieza = pieza.get("url")
                    if esUrl(urlPieza):
                        descripcion += f" 🤖 {pieza.get('title')}: {urlPieza}\n"
                elif pieza.get("amazon"):
                    descripcion += f" 🤖 {pieza.get('title')}:\n"
                    descripcion += linkAmazon(pieza.get("amazon"))
                else:
                    descripcion += f" 🤖 {pieza.get('title')}:\n"
                    descripcion += buscarAmazon(pieza.get('title'), dataVideo.get('title'), rutaVideo.name)
            descripcion += "Link de Afilaron de amazon, ganamos una comisión si los usas\n"
            descripcion += "\n"

        # Extra
        if dataVideo.get("custom_sections"): 
            descripcion += "Link Extras:\n"
            for extras in dataVideo.get("custom_sections"):
                if dataPendiente(extras, dataVideo, rutaVideo, "extra"):
                    continue
                if extras.get("title"):
                    descripcion += f" ✪ {extras.get('title')}:\n"
                    for miniExtras in extras.get('items'):
                        if dataPendiente(miniExtras, dataVideo, rutaVideo, "extra extra"):
                            continue
                        urlMini = miniExtras.get('url')
                        urlTitle = miniExtras.get("titule")
                        descripcion += f"  ➤ {urlTitle}: {urlMini}\n"
            descripcion += "\n"

        # Indice
        if dataVideo.get("topics"): 
            descripcion += "🕓 Índice:\n"
            for indice in dataVideo.get("topics"):
                descripcion += f"{indice.get('time')} {indice.get('title')}\n"
            descripcion += "\n"

        # Redes Sosociales
        if dataRedes:
            descripcion += dataRedes
            descripcion += "\n"

        # Colabodores
        if dataVideo.get("colaboradores"): 
            descripcion += "Creado con los Compañeros:\n"
            for Colaborador in dataVideo.get("colaboradores"):
                descripcion += f" 🧙🏼‍♂️ {Colaborador.get('title')} - {Colaborador.get('colaborador')}\n"
            descripcion += "\n"
        
        # Tags
        descripcion += "#ChepeCarlos"
        if dataVideo.get("tags"):
            for tags in dataVideo.get("tags"):
                if tags == "shorts":
                    descripcion += f" #{tags}"
        descripcion += "\n"

        # Mejores Series
        if dataMejores:
            descripcion += "\n"
            descripcion += "🎁 Lo mejor del Canal 🎁:\n"
            descripcion += dataMejores
            descripcion += "\n"

        # Miembros
        if dataVideo.get("miembros"): 
            descripcion += "\n🦾 Creado gracias al Apoyo de Miembros(Patrocinadores):\n"
            for nivel in dataVideo.get("miembros"):
                descripcion += f"   🏆Nivel {nivel.get('title')}\n     "
                for miembro in nivel.get("items"):
                    descripcion += f"{miembro.get('title')}, "
                descripcion += "\n"
            descripcion += "\n"

        # CTA Miembros
        descripcion += "🔭 Agrega tu nombre, Únete tú también https://www.youtube.com/@chepecarlo/join 🔭\n"
        descripcion += "👊 Avances Exclusivo para Miembros: https://nocheprogramacion.com/miembros 👊"
     
        # Salvar archivo
        SalvarArchivo(nocheprogramacion.joinpath(url), descripcion)

    cantidadSeries += 1

def mostarEstadisticas():
    global config
    global cantidadVideos
    global cantidadSeries
    global cantidadPendientes
    global noProcesar
    global noAmazon
    print()
    print(f"Cantidad Totales Procesadas")
    print(f"Video: {color.GREEN}{cantidadVideos}{color.END}")
    print(f"Series: {cantidadSeries}")
    print(f"Pendientes: {color.RED}{cantidadPendientes}{color.END} Falta")
    print(f"No procesados: {noProcesar}")
    print(f"Producto no encontrado: {color.RED}{noAmazon}{color.END} Pendiente")
    print()

if __name__ == "__main__":
    main()
   