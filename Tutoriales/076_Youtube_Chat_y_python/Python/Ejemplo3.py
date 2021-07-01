# Creado ChepeCarlos de ALSW
# Tutorial Completo en https://nocheprogramacion.com
# Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

import pytchat
Video_id = "123456"
chat = pytchat.create(video_id=Video_id)
while chat.is_alive():
    for c in chat.get().sync_items():
        if c.author.isChatOwner:
            print(f"Creador: {c.datetime} [{c.author.name}]- {c.message}")
        elif c.author.isChatSponsor:
            print(f"Miembro: {c.datetime} [{c.author.name}]- {c.message}")
        elif c.author.isChatModerator:
            print(f"Moderador: {c.datetime} [{c.author.name}]- {c.message}")
