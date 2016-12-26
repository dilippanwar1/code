# NFQUEUE is an iptables and ip6tables target which delegate the decision on
# packets to a userspace software.
#
# https://pypi.python.org/pypi/NetfilterQueue
#
# Example 1:
# - In one terminal, run:
#     sudo iptables -I INPUT -d 192.168.33.0/24 -j NFQUEUE --queue-num 1
#   This will redirect packets destinated to 192.168.33.0/24 to quequ 1 (in the
#   python code, we bind to queue number 1).
# - In the same terminal, run:
#     sudo python nfqueue.py
# - In another terminal or an other machine in the same subnet, run:
#     ping 192.168.33.33
#   We'll see in the first terminal reporting ICMP packets.
# - In the first terminal, run
#     sudo iptables -D INPUT -d 192.168.33.0/24 -j NFQUEUE --queue-num 1
#   to delete the rule.
#
# Example 2:
# - On one terminal, run:
#     sudo iptables -I INPUT -d 192.168.33.0/24 -p tcp --tcp-flags FIN,SYN,RST,PSH,URG SYN -j NFQUEUE --queue-num 1
#   This tells netfilter to redirect only tcp packets; examining FIN,SYN,RST,PSH,URG
#   bits and only do the redirection if SYN bit is set.
# - In the same terminal, run:
#     sudo python nfqueue.py
# - In another terminal, start an HTTP server:
#     python -m SimpleHTTPServer
# - In a third terminal, run
#     curl http://192.168.33.33:8000
#   We'll see the first terminal reporting TCP packets. If we remove tcp flags,
#   we'll see more lines of report
# - In the first terminal, run
#     sudo iptables -D INPUT -d 192.168.33.0/24 -p tcp --tcp-flags FIN,SYN,RST,PSH,URG SYN -j NFQUEUE --queue-num 1
#   to delete the rule.

from netfilterqueue import NetfilterQueue

def print_and_accept(pkt):
    print(pkt)
    pkt.accept()

nfqueue = NetfilterQueue()
nfqueue.bind(1, print_and_accept)
try:
    nfqueue.run()
except KeyboardInterrupt:
    print('')

nfqueue.unbind()
