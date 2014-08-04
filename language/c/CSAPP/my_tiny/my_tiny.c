#include "csapp.h"


//=======================================================================
//== Declarations
//=======================================================================
int Open_listenfd(int prot);
void doit(int connfd);
void read_requesthdrs(rio_t *rp);
void clienterror(int fd, char *cause, char *errnum, 
		 char *shortmsg, char *longmsg);
void serve_static(int connfd, char* filename, struct stat filestat);
void serve_dynamic(int connfd, char* filename, char* cgiargs);

/*
 * main function of tiny server
 */
int main(int argc, char *argv[]) {

    if (argc != 2) {
	fprintf(stderr, "Tiny server usage: %s <port>\n", argv[0]);
	exit(1);
    }

    int listenfd, connfd, clientlen, port;
    struct sockaddr_in clientaddr;

    port = atoi(argv[1]);
    listenfd = Open_listenfd(port); /* open listen socket */
    while (1) {
	clientlen = sizeof(clientaddr);
	connfd = Accept(listenfd, (struct sockaddr*)&clientaddr, &clientlen);
	doit(connfd);
	Close(connfd);
    }
}


/*
 * doit - handle an HTTP transaction
 */
void doit(int connfd) {

    char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
    char filename[MAXLINE], cgiargs[MAXLINE];
    rio_t rio;
    int is_static;
    struct stat filestat;

    /* parse request, for Tiny Server, it's typically "GET / HTTP/1.0" */
    Rio_readinitb(&rio, connfd);	/* subsequent read will read from connfd */
    Rio_readlineb(&rio, buf, MAXLINE);	/* read first line of HTTP request */
    sscanf(buf, "%s %s %s", method, uri, version); /* format */

    if (strcasecmp(method, "GET")) { /* Tiny Server can only handle GET method */
	clienterror(connfd, method, "501", "Not Implemented",
		    "Tiny does not support the method ");
	return;
    }
    read_requesthdrs(&rio);

    /* parse uri, put requested file name into `filename`, and put arguments */
    /* into cgiargs if any */
    is_static = parse_uri(uri, filename, cgiargs);
    if (stat(filename, &filestat) < 0) {
	clienterror(connfd, filename, "404", "Not Found",
		    "Tiny couldn't find the file ");
	return;
    }

    if (is_static) {		/* serve static content */
	if (!S_ISREG(filestat.st_mode) || !(S_IRUSR & filestat.st_mode)) {
	    clienterror(connfd, filename, "403", "Forbidden",
			"Tiny couldn't read the file ");
	    return;
	}
	serve_static(connfd, filename, filestat);
    } else {
	if (!S_ISREG(filestat.st_mode) || !(S_IXUSR & filestat.st_mode)) {
	    clienterror(connfd, filename, "403", "Forbidden",
			"Tiny couldn't execute the cgi file ");
	    return;
	}
	serve_dynamic(connfd, filename, cgiargs);
    }
}


/*
 * clienterror - returns an error message to the client
 */
void clienterror(int fd, char *cause, char *errnum, 
		 char *shortmsg, char *longmsg) {

    char buf[MAXLINE], body[MAXBUF];

    /* Build HTTP response, like
     * 	HTTP/1.0 404 Not Found
     *	Content-type: text/html
     *	Content-length: xxx
     *
     *	Tiny couldn't find file.
     *	Server: 'The Tiny Web Server'
    */
    /* Build the HTTP response body */
    sprintf(body, "<html><title>Tiny Error</title>");
    sprintf(body, "%s<body bgcolor=""ffffff"">\r\n", body);
    sprintf(body, "%s%s: %s\r\n", body, errnum, shortmsg);
    sprintf(body, "%s<p>%s: %s\r\n", body, longmsg, cause);
    sprintf(body, "%s<hr><em>The Tiny Web server</em>\r\n", body);

    /* Print the HTTP response */
    sprintf(buf, "HTTP/1.0 %s %s\r\n", errnum, shortmsg);
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Content-type: text/html\r\n");
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Content-length: %d\r\n\r\n", (int)strlen(body));
    Rio_writen(fd, buf, strlen(buf));
    Rio_writen(fd, body, strlen(body));
}


/*
 * return a listen socket in a server to listen request from client
 * if error, return -1
 */
int Open_listenfd(int port) {

    int listenfd, optval;
    struct sockaddr_in sockaddr;

    /* create listen socket */
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
	fprintf(stderr, "create socket error!\n");
	exit(1);
    }

    /* fill in socket address */
    bzero((char *) &sockaddr, sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons((unsigned short)port);
    sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    /* bind socket address to this program */
    if (bind(listenfd, (struct sockaddr *) &sockaddr,
	     sizeof(sockaddr)) < 0) {
	fprintf(stderr, "bind error!\n");
	exit(1);
    }

    /* get rid of "address already in use" error */
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR,
		   (const void *)&optval , sizeof(int)) < 0) {
	fprintf(stderr, "set opt error!\n");	
	exit(1);
    }

    /* make listenfd a passive listen socket */
    if (listen(listenfd, 1024) < 0) {
	fprintf(stderr, "convert to listen socket error!\n");
	exit(1);
    }

    return listenfd;
}


/*
 * read_requesthdrs - read and ignore HTTP request headers, Tiny Server
 *	only need first line, like "GET / HTTP/1.0"
 */
void read_requesthdrs(rio_t *rp) {
    
    char buf[MAXLINE];

    Rio_readlineb(rp, buf, MAXLINE);
    while(strcmp(buf, "\r\n")) { /* check temination */
	Rio_readlineb(rp, buf, MAXLINE);
	printf("%s", buf);	/* print out received header */
	printf("i gess\n");
    }
    return;
}


/*
 * parse_uri - parse uri into filename and cgiargs, return whether it's
 *	static or dynamic. static: 1, dynamic: 0.
 */
int parse_uri(char* uri, char* filename, char* cgiargs) {

    char* ptr;
    
     /* static content, since our cgi is only contained in ./cgi-bin/ */
    if (!strstr(uri, "cgi-bin")) {
	strcpy(cgiargs, "");
	strcpy(filename, ".");
	strcat(filename, uri);
	if (uri[strlen(uri) - 1] == '/') {
	    strcat(filename, "home.html");
	}
	return 1;
    } else {
	ptr = index(uri, '?');
	if (ptr) {
	    strcpy(cgiargs, ptr+1);
	    *ptr = '\0';
	} else {
	    strcpy(cgiargs, "");
	}
	strcpy(filename, ".");
	strcat(filename, uri);
	return 0;
    }
}


/*
 * serve_static - serve static content
 */
void serve_static(int connfd, char* filename, struct stat filestat) {

    int srcfd;
    char *srcp;
    char filetype[MAXLINE], body[MAXBUF];
    
    /* get file type */
    if (strstr(filename, ".html"))
	strcpy(filetype, "text/html");
    else if (strstr(filename, ".gif"))
	strcpy(filetype, "text/gif");
    else if (strstr(filename, ".jpg"))
	strcpy(filetype, "text/jpg");
    else
	strcpy(filetype, "text/plain");

    /* send response headers to client */
    sprintf(body, "HTTP/1.0 200 OK\r\n");
    sprintf(body, "%sServer: Tiny Web Server\r\n", body);
    sprintf(body, "%sContent-length: %d\r\n", body, (int)filestat.st_size);
    sprintf(body, "%sContent-type: %s\r\n\r\n", body, filetype);
    Rio_writen(connfd, body, strlen(body));
    
    /* send response body to client */
    srcfd = Open(filename, O_RDONLY, 0);
    /* map the file into a chunk of virtual memory */
    srcp = Mmap(NULL, filestat.st_size, PROT_READ, MAP_PRIVATE, srcfd, 0);
    Close(srcfd);
    Rio_writen(connfd, srcp, filestat.st_size);
    Munmap(srcp, filestat.st_size);
}


/*
 * serve_dynamic - serve dynamic content
 */
void serve_dynamic(int connfd, char* filename, char* cgiargs) {

    char body[MAXBUF], *emptylist[] = {NULL};

    /* send response headers to client */
    sprintf(body, "HTTP/1.0 200 OK\r\n");
    sprintf(body, "%sServer: Tiny Web Server\r\n", body);
    Rio_writen(connfd, body, strlen(body));
    
    if (Fork() == 0) {		/* fork a new child */
	setenv("QUERY_STRING", cgiargs, 1);
	Dup2(connfd, STDOUT_FILENO); /* redirect stdout to connfd */
	Execve(filename, emptylist, environ);
    }

    Wait(NULL);			/* parent wait */
}
