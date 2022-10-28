# Creado ChepeCarlos de ALSW
# Tutorial Completo en https://nocheprogramacion.com
# Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

import multiprocessing
import time

import paho.mqtt.client as mqtt


def enviarMQTT(Topico, Mensaje, Host="test.mosquitto.org", Puerto=1883):
    client = mqtt.Client()
    client.connect(Host, Puerto, 60)
    client.publish(Topico, Mensaje)
    print("Se envió la data")


inicio = time.time()
procesoMQTT = multiprocessing.Process(target=enviarMQTT, args=("ALSW/demo", "hola_avanzado"))
procesoMQTT.start()
final = time.time()
tiempo = (final - inicio) * 1000
print(f"El código tardo {tiempo} ms")
