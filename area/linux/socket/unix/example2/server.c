/**
 * A echo server using unix socket for IPC.
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCK_PATH "/var/run/echo_socket"

int main(void)
{
  /* Note here we create struct sockaddr_un instead of sockaddr_in. */
  struct sockaddr_un local, remote;
  int s, s2, t, len;
  char str[100];

  /* Create a stream socket. */
  if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
    perror("socket");
    exit(1);
  }

  local.sun_family = AF_UNIX;
  strcpy(local.sun_path, SOCK_PATH);
  unlink(local.sun_path);
  len = strlen(local.sun_path) + sizeof(local.sun_family);
  if (bind(s, (struct sockaddr *)&local, len) == -1) {
    perror("bind");
    exit(1);
  }

  /* The second argument, 5, is the number of incoming connections that can
     be queued before you call accept(), below. If there are this many
     connections waiting to be accepted, additional clients will generate
     the error ECONNREFUSED. */
  if (listen(s, 5) == -1) {
    perror("listen");
    exit(1);
  }

  for (;;) {
    int done, n;
    printf("Waiting for a connection...\n");
    t = sizeof(remote);
    /* When accept() returns, the remote variable will be filled with the
       remote side's struct sockaddr_un, and len will be set to its length. */
    if ((s2 = accept(s, (struct sockaddr *)&remote, &t)) == -1) {
      perror("accept");
      exit(1);
    }

    printf("Connected.\n");

    done = 0;
    do {
      n = recv(s2, str, 100, 0);
      if (n <= 0) {
        if (n < 0) perror("recv");
        done = 1;
      }

      if (!done)
        if (send(s2, str, n, 0) < 0) {
          perror("send");
          done = 1;
        }
    } while (!done);

    close(s2);
  }

  return 0;
}
