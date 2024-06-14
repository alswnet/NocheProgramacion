import requests
import json

tokenNotion = "secret_123" # Cambiar

urlPregunta = "https://api.notion.com/v1/users"

cabecera = {
    "Authorization": f"Bearer {tokenNotion}",
    "Content-Type": "application/json",
    "Notion-Version": "2021-08-16"
}

respuesta = requests.get(urlPregunta, headers=cabecera)

print(json.dumps(respuesta.json(), sort_keys=False, indent=4))
