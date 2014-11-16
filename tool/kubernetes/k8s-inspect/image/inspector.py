import netifaces

for interface in netifaces.interfaces():
  if netifaces.AF_INET in netifaces.ifaddresses(interface):
    print interface
    print netifaces.ifaddresses(interface)[netifaces.AF_INET]
