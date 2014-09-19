#include "csapp.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
	fprintf(stderr, "please specify host name or dotted-decimal ip address");
	exit(1);
    }

    char **pp;
    struct in_addr *addr;
    struct hostent *hostp;

    if (inet_aton(argv[1], addr) == 1) {
	hostp = Gethostbyaddr((const char*)addr, sizeof(addr), AF_INET);
    } else {
	hostp = Gethostbyname(argv[1]);
    }

    printf("official host name: %s\n", hostp->h_name);
    for (pp = hostp->h_aliases; *pp != NULL; pp++) {
	printf("alias: %s\n", *pp);
    }

    for (pp = hostp->h_addr_list; *pp != NULL; pp++) {
	char *p = inet_ntoa((*(struct in_addr *)pp));
	printf("host address: %s\n", p);
    }
}
