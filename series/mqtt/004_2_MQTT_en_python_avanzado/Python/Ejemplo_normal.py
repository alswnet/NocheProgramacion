# Creado ChepeCarlos de ALSW
# Tutorial Completo en https://nocheprogramacion.com
# Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

import time

import paho.mqtt.client as mqtt


def enviarMQTT(Topico, Mensaje, Host="test.mosquitto.org", Puerto=1883):
    client = mqtt.Client()
    client.connect(Host, Puerto, 60)
    client.publish(Topico, Mensaje)


inicio = time.time()
enviarMQTT("ALSW/demo", "hola")
final = time.time()
tiempo = (final - inicio) * 1000
print(f"El código tardo {tiempo} ms")
