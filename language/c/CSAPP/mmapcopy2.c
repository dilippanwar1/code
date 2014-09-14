#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>


int main(int argc, char *argv[]) {

    if (argc != 2) {
	fprintf(stderr, "please enter file name\n");
	return;
    }

    struct stat st;
    int fd;
    char *buf;

    if ((fd = open(argv[1], O_RDONLY)) < 0) {
	fprintf(stderr, "open error: %s\n", strerror(errno));
	return;
    }

    if (fstat(fd, &st) < 0) {
	fprintf(stderr, "fstat error\n");
	return;	
    }

    buf = (char*)mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (write(STDOUT_FILENO, buf, st.st_size) < 0) {
	fprintf(stderr, "mmap error\n");
	return;		
    }
}
    
