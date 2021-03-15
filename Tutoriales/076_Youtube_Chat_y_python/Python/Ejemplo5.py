import pytchat
import os
import json

Video_id = "123456"
chat = pytchat.create(video_id=Video_id)


def Salvar(Archivo, Valor):
    if os.path.exists(Archivo):
        with open(Archivo) as f:
            data = json.load(f)
    else:
        data = []
    data.append(Valor)

    with open(Archivo, 'w') as f:
        json.dump(data, f, indent=4)


while chat.is_alive():
    for c in chat.get().sync_items():
        ChatData = {
            "Tiempo": c.datetime,
            "Tipo": c.type,
            "Nombre": c.author.name,
            "CanalID": c.author.channelId,
            "Mensaje": c.message
        }
        print(f"{c.datetime} [{c.author.name}]- {c.message}")
        Salvar('chat.json', ChatData)
