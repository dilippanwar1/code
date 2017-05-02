// Following experiment from:
//   http://backreference.org/2010/03/26/tuntap-interface-tutorial/
//
// A TAP is a simulated interface which exists only in the kernel and has no
// physical component associated with it. It can be viewed as a simple
// Point-to-Point or Ethernet device, which instead of receiving packets from
// a physical media, receives them from user space program and instead of
// sending packets via physical media writes them to the user space program
// (from kernel's perspective).
//
// 1. Create a tun device name 'tuntest'
//   $ sudo ip tuntap add dev tuntest mode tun
// 2. Bring it up
//   $ sudo ip link set tuntest up
// 3. Give it an address
//   $ sudo ip addr add 10.0.0.1/24 dev tuntest
// 4. Compile this code
//   $ gcc basic.c
// 5. Run it
//   $ ./a.out
// 6. Ping any ip in 10.0.0.0/24, and we'll see output from a.out. Ping any
//   address works because 10.0.0.1 is the gateway for the subnet, i.e.
//   because the kernel sees that the address is not local, and the route to
//   reach it points to the tap interface.
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <linux/if.h>
#include <linux/if_tun.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <errno.h>

// tun_alloc creates a new tun/tap interface, or connects to an existing
// one if the interface exists.
int tun_alloc(char *dev, int flags)
{
  struct ifreq ifr;
  int fd, err;
  char *clonedev = "/dev/net/tun";

  /* Arguments taken by the function:
   *
   * char *dev: the name of an interface (or '\0'). MUST have enough
   *   space to hold the interface name if '\0' is passed
   * int flags: interface flags (eg, IFF_TUN etc.)
   */

  /* open the clone device */
  if( (fd = open(clonedev, O_RDWR)) < 0 ) {
    return fd;
  }

  /* preparation of the struct ifr, of type "struct ifreq" */
  memset(&ifr, 0, sizeof(ifr));

  ifr.ifr_flags = flags;   /* IFF_TUN or IFF_TAP, plus maybe IFF_NO_PI */

  if (*dev) {
    /* if a device name was specified, put it in the structure; otherwise,
     * the kernel will try to allocate the "next" device of the
     * specified type */
    strncpy(ifr.ifr_name, dev, IFNAMSIZ);
  }

  /* try to create the device */
  if( (err = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0 ) {
    close(fd);
    return err;
  }

  /* if the operation was successful, write back the name of the
   * interface to the variable "dev", so the caller can know
   * it. Note that the caller MUST reserve space in *dev (see calling
   * code below) */
  strcpy(dev, ifr.ifr_name);

  /* this is the special file descriptor that the caller will use to talk
   * with the virtual interface */
  return fd;
}

int main() {
  char tun_name[IFNAMSIZ];
  char buffer[1500];
  int tun_fd;
  int nread;

  /* Connect to the device */
  strcpy(tun_name, "tuntest");
  tun_fd = tun_alloc(tun_name, IFF_TUN | IFF_NO_PI); /* tun interface */

  if (tun_fd < 0){
    perror("Allocating interface");
    exit(1);
  }

  /* Now read data coming from the kernel */
  while(1) {
    /* Note that "buffer" should be at least the MTU size of the interface,
       eg 1500 bytes */
    nread = read(tun_fd, buffer, sizeof(buffer));
    if (nread < 0) {
      perror("Reading from interface");
      close(tun_fd);
      exit(1);
    }

    /* Do whatever with the data */
    printf("Read %d bytes from device %s\n", nread, tun_name);
  }
}
