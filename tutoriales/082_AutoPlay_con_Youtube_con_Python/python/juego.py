# Creado por ChepeCarlos
# Tutorial Completo en https://nocheprogramacion.com
# Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

import argparse

from chat_downloader import ChatDownloader
import pyautogui
import time

delay = 0.1

parser = argparse.ArgumentParser(
    description="AutoJuego Demo delay por ChepeCarlos")
parser.add_argument("--youtube", "-y", help="ID de youtube")

if __name__ == "__main__":
    args = parser.parse_args()

    if args.youtube:
        print(f"Iniciando Bot:{args.youtube}")
        url = f"https://www.youtube.com/watch?v={args.youtube}"
        chat = ChatDownloader().get_chat(url)
        for mensaje in chat:
            chat.print_formatted(mensaje)
            if mensaje['message'].lower() == "arriba" or mensaje['message'].lower() == "up":
                print("Ariba :)")
                pyautogui.keyDown("up")
                time.sleep(delay)
                pyautogui.keyUp("up")
            elif mensaje['message'].lower() == "abajo" or mensaje['message'].lower() == "down":
                print("abajo :)")
                pyautogui.keyDown("down")
                time.sleep(delay)
                pyautogui.keyUp("down")
            elif mensaje['message'].lower() == "izquierda" or mensaje['message'].lower() == "left":
                print("izquiera :)")
                pyautogui.keyDown("left")
                time.sleep(delay)
                pyautogui.keyUp("left")
            elif mensaje['message'].lower() == "derecha" or mensaje['message'].lower() == "right":
                print("derecha :)")
                pyautogui.keyDown("right")
                time.sleep(delay)
                pyautogui.keyUp("right")
            elif mensaje['message'].lower() == "confirmar" or mensaje['message'].lower() == "a":
                print("confiarm :)")
                pyautogui.keyDown("z")
                time.sleep(delay)
                pyautogui.keyUp("z")
            elif mensaje['message'].lower() == "cancelar" or mensaje['message'].lower() == "b":
                print("cancelar :)")
                pyautogui.keyDown("x")
                time.sleep(delay)
                pyautogui.keyUp("x")
    else:
        print("no opción prueba con -h")
