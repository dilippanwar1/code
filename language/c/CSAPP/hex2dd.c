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
    int hex;
    char *p;

    addr.s_addr = htonl(addr.s_addr);
    hex = sscanf(argv[1], "%x", &addr.s_addr);
    p = inet_ntoa(addr);

    printf("%s\n", p);
    
    return 0;
}
