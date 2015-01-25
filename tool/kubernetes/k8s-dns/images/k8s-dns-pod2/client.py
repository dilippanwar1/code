import requests
import socket

ipaddress = socket.gethostbyname("k8s-dns-service1")
print ipaddress

# Need to supply port number.
response = requests.get("http://k8s-dns-service1:8765")
print response
