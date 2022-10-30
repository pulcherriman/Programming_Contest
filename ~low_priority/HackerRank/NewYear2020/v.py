import requests
import urllib
import json
import time
import os

n = int(input())
code = "\n".join([input() for _ in range(n)])
encoded = urllib.parse.quote(f"int main(){{{code}}}")


# urllib.parse.quote

api = f"http://api.paiza.io:80/runners/create?source_code={encoded}&language=c&api_key=guest"

res = requests.post(api)
id = json.loads(res.text)['id']

check = f"http://api.paiza.io:80/runners/get_details?id={id}&api_key=guest"

time.sleep(1)
res = requests.get(check)

err = []


os.system(f"gcc")

for msg in json.loads(res.text)['build_stderr'].split('\n'):
	if msg[:4] != "Main":
		continue
	if ": error:" not in msg:
		continue
	err.append(int(msg.split()[0].split(":")[1]))

for i in range(1,n+1):
	print("INVALID" if i in err else "VALID")