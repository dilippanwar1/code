// Linux namespace API includes clone(), setns() and ushare(), as well as files under /proc.
//
// Steps:
// 1. Run a docker container:
//    $ docker run -d ubuntu sleep 300  --> f3acd469b1ca
// 2. Find the container's PID in host system:
//    $ docker inspect docker inspect --format "{{ .State.Pid }}" f3acd469b1ca --> 6612
// 3. Now build the file and run:
//    $ gcc setns.c -o setns
//    $ sudo ./setns /proc/6612/ns/uts bash
//    Running this command will put us in the uts namespace of the container, i.e. our hostname
//    will be f3acd469b1ca.

#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char** argv) {
  int fd = open(argv[1], O_RDONLY);
  setns(fd, 0);
  execvp(argv[2], &argv[2]);
}
