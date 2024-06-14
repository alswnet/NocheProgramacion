import requests
import json

tokenNotion = "secret_123" # Cambiar

idDataBase = "123abc" # Cambiar

urlPregunta = f"https://api.notion.com/v1/databases/{idDataBase}/query"

cabecera = {
    "Authorization": f"Bearer {tokenNotion}",
    "Content-Type": "application/json",
    "Notion-Version": "2021-08-16"
}

busqueda = {
    "filter": {
        "property": "URL NocheProgramacion",
        "text": {
            "contains": "4.Shorts/2024/09_controlar_impresora_con_esp8266"
        }
    }
}

respuesta = requests.post(
    urlPregunta, headers=cabecera, data=json.dumps(busqueda))

idActualizar = respuesta.json()["results"][0]["id"]

print(f"Id a Actualizar {idActualizar}")

urlPregunta = f"https://api.notion.com/v1/pages/{idActualizar}"


actualizar = {
    "properties": {
        "Estado": {
            "select": {
                "name": "publicado"
            }
        }
    }
}

respuesta = requests.patch(urlPregunta, json=actualizar, headers=cabecera)
print(json.dumps(respuesta.json(), sort_keys=False, indent=4))


with open("db.json", "w") as fd:
    json.dump(respuesta.json(), fd, sort_keys=False, indent=4)
