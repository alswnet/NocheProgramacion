import pytchat
Video_id = "ID_Video"
chat = pytchat.create(video_id=Video_id)
while chat.is_alive():
    for c in chat.get().sync_items():
        print(f"Creador: {c.datetime} [{c.author.name}]- url:{c.author.channelUrl} imagen{c.author.imageUrl}")
