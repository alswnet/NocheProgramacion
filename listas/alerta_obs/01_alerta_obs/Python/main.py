from select import select
from mi_mqtt import MiMQTT
from mi_obs import MiOBS
import os
import json

def leerArchivo(archivo):
    try:
        with open(archivo) as f:
            return json.load(f)
    except Exception as e:
        print(f"Error: {e}")

infoMQTT = leerArchivo("mqtt.json")
infoOBS = leerArchivo("obs.json")

servidorMQTT = MiMQTT(infoMQTT)
servidorOBS = MiOBS(infoOBS)

servidorOBS.Notificar = servidorMQTT.EnviarMQTT
servidorMQTT.funcionCambiarGrabacion = servidorOBS.CambiarGrabacion
servidorMQTT.funcionCambiarEnVivo = servidorOBS.CambiarEnVivo

servidorMQTT.Conectar()

servidorOBS.Conectar()

while True:
    Salir = input("Salir(S):")
    if Salir == "S" or Salir == "s":
        servidorMQTT.EnviarMQTT(servidorOBS.topic, "OBS-No-Conectado")
        os._exit(0)
