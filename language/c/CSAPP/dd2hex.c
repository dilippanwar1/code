#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>


int main(int argc, char* argv[]) {
    if (argc != 2) {
	fprintf(stderr, "please specify address\n");
	exit(1);
    }

    struct in_addr addr;

    /* change application format into network format */
    if (inet_aton(argv[1], &addr) < 0) {
	fprintf(stderr, "error");
	exit(1);
    } else {
	addr.s_addr = ntohl(addr.s_addr);
	printf("hex is: %x\n", addr.s_addr);
    }
    
    return 0;
}
