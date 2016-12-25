# NFQUEUE is an iptables and ip6tables target which delegate the decision on
# packets to a userspace software.
#
# https://pypi.python.org/pypi/NetfilterQueue

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
