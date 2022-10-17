# Creado por ChepeCarlos
# Tutorial Completo en https://nocheprogramacion.com
# Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

from chat_downloader import ChatDownloader

url = 'https://www.youtube.com/watch?v=To82IyUKS5U'
chat = ChatDownloader().get_chat(url)    
for mensaje in chat:   
    # print(dir(mensaje))            
    # print(mensaje.keys())
    print("----"*10)
    print(f"{mensaje['author']['name']} {mensaje['message']} {mensaje['message_type']}")