# Creado ChepeCarlos de ALSW
# Tutorial Completo en https://nocheprogramacion.com
# Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

from os import path
from notifypy import Notify
import time

icono = "LogoALSW.png"
direcion = path.abspath(path.dirname(__file__))

NotigicacionBase = Notify(
    default_notification_title="Umaru",
    default_notification_icon=path.join(direcion, icono)
)


def EnviarNotificacion(mensaje, audio):
    NotigicacionBase = Notify()
    NotigicacionBase.title = "Titulo"
    NotigicacionBase.message = mensaje
    if audio is not None:
        NotigicacionBase.audio = path.join(direcion, audio)
    NotigicacionBase.send()


Mensajes = [
    {
        "mensaje": "Hola",
        "audio": None,
        "espera": 4
    }, {
        "mensaje": "Hola",
        "audio": "audio/Hola.wav",
        "espera": 4
    }, {
        "mensaje": "Disculpa tienes notificacion",
        "audio": "audio/Disculpa.wav",
        "espera": 4
    }, {
        "mensaje": "¿Estas grabando?",
        "audio":  "audio/Estas_Grabando.wav",
        "espera": 4
    }, {
        "mensaje": "Tienes una notificacion",
        "audio": "audio/Tienes.wav",
        "espera": 4
    }, {
        "mensaje": "OBS Estudio empezo a grabar",
        "audio": "audio/OBS.wav",
        "espera": 10
    }, {
        "mensaje": "Osi una cosa mas",
        "audio": "audio/Mas.wav",
        "espera": 5
    }, {
        "mensaje": "No se les olvide subcribirse a ALSW",
        "audio": "audio/Sub.wav",
        "espera": 10,
    }, {
        "mensaje": "Adios",
        "audio": "audio/Adios.wav",
        "espera": 4
    }
]

# time.sleep(espera)
for Mensaje in Mensajes:
    print(f"Repoducion: {Mensaje=}")
    EnviarNotificacion(Mensaje['mensaje'], Mensaje['audio'])
    time.sleep(Mensaje['espera'])
