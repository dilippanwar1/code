#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/* int parse_uri(char *uri, char *path, char *host, int *port) { */

/*     char* begin; */
/*     char *end; */
/*     char *colon; */
    
/*     if ((begin = strstr(uri, "http://")) != NULL) { */
	
/* 	begin = begin + strlen("http://"); */
/* 	end = strchr(begin, '/'); */
/* 	if (end != NULL) *end = '\0'; */

/* 	if ((colon = strchr(begin, ':')) != NULL) { */
/* 	    *colon = '\0'; */
/* 	    colon = colon + 1; */
/* 	    *port = atoi(colon); */
/* 	    strcpy(host, begin); */
/* 	    if (end != NULL) { */
/* 		*end = '/'; */
/* 		strcpy(path, end);		 */
/* 	    } else { */
/* 		strcpy(path, "/"); */
/* 	    } */


/* 	    return 2; */
/* 	} else { */
/* 	    *port = -1; */
/* 	    strcpy(host, begin); */
/* 	    if (end != NULL) { */
/* 		*end = '/'; */
/* 		strcpy(path, end); */
/* 	    } else { */
/* 		strcpy(path, "/"); */
/* 	    } */
	    

/* 	    return 1; */
/* 	} */
/*     } */

/*     return 0; */
/* } */


/* 
 * store the host and path if available 
 */
void parse_uri(char *uri, char *host, char*port, char *path){
    char ubuf[1024];
    char buf[1024];
    char *ptr;
    
    /* if uri contains host */
    if(strstr(uri, "http://")){
	sscanf(uri,"http://%s", ubuf);
	ptr = index(ubuf, '/');
	strcpy(path, ptr+1);
	*ptr = '\0';
	strcpy(buf, ubuf);

	ptr = index(buf, ':');
	/* if port is already given */
	if(ptr) {
	    strcpy(port, ptr+1);
	    *ptr = '\0';
	}
	else{
	    strcpy(port, "80");
	}
	strcpy(host, buf);
    }
    else {
	strcpy(path, uri);
	strcpy(port, "80");
    }
}


int main(void) {
       char uri[] = "http://www.cmu.edu:8080/hub/index.html";
       // char uri[] = "http://cboard.cprogramming.com/online.php";
    //char uri[] = "/hub";
    //    char uri[] = "http://www.cmu.edu";
    char path[100];
    char host[100];
    char port[100];

    parse_uri(uri, host, port, path);
    printf("%s, %s, %s\n", host, path, port);
    /* if (parse_uri(uri, host, port, path)) { */
    /* 	printf("%s, %s, %d\n", host, path, port); */
    /* } else { */
    /* 	printf("%s\n", uri); */
    /* } */
}
