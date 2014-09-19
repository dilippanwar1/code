#include "csapp.h"


/*
 * return a listen socket in a server to listen request from client
 * if error, return -1
 */
int my_open_listenfd(int port) {

  int listenfd, optval;
  struct sockaddr_in sockaddr;

  /* create listen socket */
  if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    fprintf(stderr, "create socket error!\n");
    return -1;
  }

  /* fill in socket address */
  bzero((char *) &sockaddr, sizeof(sockaddr));
  sockaddr.sin_family = AF_INET;
  sockaddr.sin_port = htons((unsigned short)port);
  sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  if (bind(listenfd, (struct sockaddr *) &sockaddr, sizeof(sockaddr)) < 0) {
    fprintf(stderr, "bind error!\n");
    return -1;
  }

  if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval , sizeof(int)) < 0)
    return -1;

  if (listen(listenfd, 1024) < 0) {
    fprintf(stderr, "convert to listen socket error!\n");
    return -1;
  }

  return listenfd;
}


void echo(int connfd) {
  size_t n;
  char buf[MAXLINE];
  rio_t rio;

  Rio_readinitb(&rio, connfd);

  while ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) {
    printf("server received %ld bytes\n", n);
    Rio_writen(connfd, buf, n);
  }
}


int main(int argc, char *argv[]) {

  int listenfd, connfd, port, clientlen;
  struct sockaddr_in clientaddr;
  struct hostent *hp;
  char *haddrp;

  if (argc != 2) {
    fprintf(stderr, "usage: %s <port>\n", argv[0]); exit(0);
  }

  port = atoi(argv[1]);
  listenfd = Open_listenfd(port);

  while (1) {
    clientlen = sizeof(clientaddr);
    connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
    /* Determine the domain name and IP address of the client */
    hp = Gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr,
                       sizeof(clientaddr.sin_addr.s_addr), AF_INET);
    haddrp = inet_ntoa(clientaddr.sin_addr);
    printf("server connected to %s (%s)\n", hp->h_name, haddrp);
    echo(connfd);
    Close(connfd);
  }
  exit(0);
}
