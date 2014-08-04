#include "csapp.h"

/*
 * return a connection socket which can be connected to a server (hostname:port)
 * if error, return -1
 */
int my_open_clientfd(char *hostname, int port) {

    int clientfd;
    struct sockaddr_in sockaddr;
    struct hostent *hp;

    /* create connection socket */
    if ((clientfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
	fprintf(stderr, "create socket error!\n");
	return -1;
    }

    /* get host information by hostname */
    if ((hp = gethostbyname(hostname)) == NULL) {
	fprintf(stderr, "get host by name error!\n");
    }

    /* fill in socket address */
    bzero((char *) &sockaddr, sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons((unsigned short)port);
    sockaddr.sin_addr = (*(struct in_addr *)hp->h_addr_list[0]);

    /* connect to server */
    if (connect(clientfd, (struct sockaddr *) &sockaddr, sizeof(sockaddr)) < 0) {
	fprintf(stderr, "connect error!\n");
	return -1;
    }
}



int main(int argc, char *argv[]) {

    int clientfd, port;
    char *host, buf[MAXLINE];
    rio_t rio;

    if (argc != 3) {
	fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
	exit(0);
    }

    host = argv[1];
    port = atoi(argv[2]);

    clientfd = my_open_clientfd(host, port);
    Rio_readinitb(&rio, clientfd);

    while (Fgets(buf, MAXLINE, stdin) != NULL) {
        Rio_writen(clientfd, buf, strlen(buf));
        Rio_readlineb(&rio, buf, MAXLINE);
        Fputs(buf, stdout);
    }
    
    Close(clientfd);
    exit(0);
}
