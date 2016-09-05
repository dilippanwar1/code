simpletun, a (too) simple tunnelling program.

### Detailed steps

**On local machine (client), do:**

```
sudo ip tuntap add tunclient mode tun
sudo ip link set tunclient dev
sudo ip addr add 192.168.100.2/24 dev tunclient
./simpletun -i tunclient -c xxx.xxx.xxx.xxx -p 8888 -d
```

where xxx.xxx.xxx.xxx is the public IP (or accessible internal ip) of the remote
machine. Also, a new route will be added to route traffic in subnet 192.168.100.0/24
to tunclient. Note, make sure port 8888 is not blocked by firewall. The new
route looks like:
```
192.168.100.0/24 dev tunclient  proto kernel  scope link  src 192.168.100.2 linkdown
```

**On remote machine (server), do:**

```
sudo ip tuntap add dev tunserver mode tun
sudo ip link set tunserver dev
sudo ip addr add 192.168.100.1/24 dev tunserver
sudo ./simpletun -s -i tunserver -d
```

With above setup, the tunnel between client and server has been established, e.g.
`ssh ubuntu@192.168.100.1` is the same as `ssh ubuntu@xxx.xxx.xxx.xxx`.

### How it works

On client machine, if we access remote machine using 192.168.100.1, the packet
will be sent to tunclient (from routing table). Based on how tun works in kernel,
the packet will then be passed to our simpletun.c program, since it opens a
file descriptor via `/dev/net/tun` and use `select` on the file descriptor.
In simpletun.c, it simply sends the data via network socket (default is tcp).
This is actually ip in tcp (the data received via tun is ip packet, and we send
it to remote machine using tcp).

On remote machine, simpletun.c will receive the packet (it is listening on
public interface, with given port). It reads the data and simply sends it to
tun tunserver. The data is then received by application as if it is received
via the wire (through the tun interface). For example, if the data is ssh
connection, ssh application will reply it, send the response back to tun
interface. simpletun.c will receive the response from ssh application and write
it back to public network. Therefore, there are a totol of 4 data exchange at
server side, i.e.

```
TAP2NET 1: Read 84 bytes from the tap interface
TAP2NET 1: Written 84 bytes to the network
NET2TAP 1: Read 84 bytes from the network
NET2TAP 1: Written 84 bytes to the tap interface
```

-------

To compile the program, just do

```
$ gcc simpletun.c -o simpletun
```

If you have GNU make, you can also exploit implicit targets and do

```
$ make simpletun
```

-------

Usage:

```
Usage:
simpletun -i <ifacename> [-s|-c <serverIP>] [-p <port>] [-u|-a] [-d]
simpletun -h

-i <ifacename>: Name of interface to use (mandatory)
-s|-c <serverIP>: run in server mode (-s), or specify server address (-c <serverIP>) (mandatory)
-p <port>: port to listen on (if run in server mode) or to connect to (in client mode), default 55555
-u|-a: use TUN (-u, default) or TAP (-a)
-d: outputs debug information while running
-b: use base64 to encode/decode data
-h: prints this help text
```

-------

Refer to http://backreference.org/2010/03/26/tuntap-interface-tutorial/ for
more information on tun/tap interfaces in Linux in general, and on this
program in particular.
The program must be run at one end as a server, and as client at the other
end. The tun/tap interface must already exist, be up and configured with an IP
address, and owned by the user who runs simpletun. That user must also have
read/write permission on /dev/net/tun. (Alternatively, you can run the
program as root, and configure the transient interfaces manually before
starting to exchange packets. This is not recommended)

Use is straightforward. On one end just run

```
[server]$ ./simpletun -i tun13 -s
```

at the other end run

```
[client]$ ./simpletun -i tun0 -c 10.2.3.4
```

where 10.2.3.4 is the remote server's IP address, and tun13 and tun0 must be
replaced with the names of the actual tun interfaces used on the computers.
By default it assumes a tun device is being used (use -u to be explicit), and
-a can be used to tell the program that the interface is tap.
By default it uses TCP port 55555, but you can change that by using -p (the
value you use must match on the client and the server, of course). Use -d to
add some debug information. Press ctrl-c on either side to exit (the other end
will exit too).

The program is very limited, so expect to be disappointed.
