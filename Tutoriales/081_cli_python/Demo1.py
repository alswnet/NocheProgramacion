# Creado ChepeCarlos de ALSW
# Tutorial Completo en https://nocheprogramacion.com
# Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

import argparse

parser = argparse.ArgumentParser(description='App demo :)')
parser.add_argument('--mensaje', '-m', help="Muestra mensaje esepcial %(prog)s", action="store_true")
parser.add_argument('--sub', '-s', help="Cuantas veces lo peditas", type=int)
parser.add_argument('--hola', '-H', help="Di hola a ")


def TeQuiero():
    print("Te quiero")


def Subcribete(Cantidad):
    # print("*" * 10)
    print("Subcribete a ALSW :)\n" * Cantidad)


def Hola(Nombre):
    print(f"Hola {Nombre}")


if __name__ == "__main__":
    args = parser.parse_args()

    if args.mensaje:
        TeQuiero()
    elif args.sub:
        Subcribete(args.sub)
    elif args.hola:
        Hola(args.hola)
    else:
        print("no opcion pueba con -h")
