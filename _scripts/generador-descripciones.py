
import pathlib
from pathlib import Path

if __name__ == "__main__":
    print("Iniciando Generador Descripciones")
    folderBase = Path(pathlib.Path().resolve())
    print(folderBase)
    print(folderBase.parents[0])
    print(folderBase.parents[1])
    archivoFolder = Path(folderBase, "folder.txt")
    print(archivoFolder)

    lista = list()
    with open(archivoFolder) as archivo:
        data = str(archivo.readlines())
        
        print(type(data))
        lista.append(data)
        print(data)

    print(lista)
    