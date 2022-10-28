# Creado por ChepeCarlos
# Tutorial Completo en https://nocheprogramacion.com
# Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

from chat_downloader import ChatDownloader

url = 'https://www.youtube.com/watch?v=To82IyUKS5U'
chat = ChatDownloader().get_chat(url)    
for mensaje in chat:               
    chat.print_formatted(mensaje)     
    if mensaje["message_type"] == "text_message":
        print("Mensaje normal")
    elif mensaje["message_type"] == "paid_message":
        print("Super Chat")
    elif mensaje["message_type"] == "paid_sticker":
        print("Super Stiker")
    elif mensaje["message_type"] == "membership_item":
        print("Nuevo Miembro")
    else:
         print(mensaje["message_type"])