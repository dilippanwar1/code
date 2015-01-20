import socket

# Note that port is attached to IP address, but it is also relavent to the
# protocal that is being used.  In this case, even if we have a http server
# running at port 80 (e.g. Apache), we can still bind to port 80. However,
# we need admin in order to bind it.
UDP_IP = "127.0.0.1"
UDP_PORT = 80

# socket.socket([family[, type[, proto]]])
# Here, family: Internet, typt: UDP
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# socket.bind(address), address type changes according to address family.
# Here, AF_INET's address is (host, port), where host is a string representation
# of hostname, port is an integer.
sock.bind((UDP_IP, UDP_PORT))

while True:
  data, addr = sock.recvfrom(1024) # buffer size is 1024 bytes
  print "received message:", data
