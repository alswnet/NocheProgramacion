import requests
import json

tokenNotion = "secret_123" # Cambiar

idDataBase = "123abc" # Cambiar

urlPregunta = f"https://api.notion.com/v1/pages"

cabecera = {
    "Authorization": f"Bearer {tokenNotion}",
    "Content-Type": "application/json",
    "Notion-Version": "2021-08-16"
}

pagina = {
    "parent": {
        "database_id": idDataBase
    },
    "properties": {
        "Nombre": {
            "title": [
                {
                    "text": {
                        "content": "super pollo 3"
                    }
                }
            ]
        },
        "Asignado": {
            "select": {
                "name": "desconocido"
            }
        },
        "Estado": {
            "select": {
                "name": "desconocido"
            }
        },
        "URL NocheProgramacion": {
            "rich_text": [
                {
                    "text": {
                        "content": "mega pollo"
                    }
                }
            ]
        }
    }
}

respuesta = requests.post(
    urlPregunta, headers=cabecera, data=json.dumps(pagina))
print(json.dumps(respuesta.json(), sort_keys=False, indent=4))


with open("db.json", "w") as fd:
    json.dump(respuesta.json(), fd, sort_keys=False, indent=4)
