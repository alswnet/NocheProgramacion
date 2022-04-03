# Creado ChepeCarlos de ALSW
# Tutorial Completo en https://nocheprogramacion.com
# Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

import pytchat

Video_id = "G0lKP8bIv1E"
chat = pytchat.create(video_id=Video_id)
while chat.is_alive():
    for c in chat.get().sync_items():
        print(f"URL: {c.author.imageUrl}")
        if c.type == "superChat":
            print(
                f"**Super chat**: {c.currency}{c.amountString} {c.datetime} - [{c.type}] [{c.author.name}]- {c.message}"
            )
        elif c.type == "superSticker":
            print(f"**SuperStiker**: {c.datetime} - [{c.type}] [{c.author.name}]")
        elif c.type == "newSponsor":
            print(f"**Nuevo Miembro**: {c.datetime} - [{c.type}] [{c.author.name}]")
        if c.author.isChatSponsor:
            print(f"**Miembro**: {c.datetime} [{c.author.name}]- {c.message}")
