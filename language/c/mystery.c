#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>


#define GOT_PROG 0x01
#define GOT_VERS 0x02
#define GOT_PROC 0x04


int program = 0, version = 0, process = 0;
unsigned char flags = 0;


void parse(char *data)
{

    char *tmp = NULL;

    while(isspace((int)*data)) data++; /* should check if data is NULL */

    if(*data != '*')
    {
        program = strtoul(data,&tmp,0);
        flags|=GOT_PROG;
    }
    if(*tmp == '\0') return;    /* if first data is *, the we dereference NULL */
    data=++tmp;
    if(*data != '*') /* we should bypass whitespaces between two nums here
                      * if the middle one is *, then we'll get 0s*/
    {
        version = strtoul(data,&tmp,0);
        flags|=GOT_VERS;
    }
    else
    {
        tmp++;
    }
    if(*tmp == '\0') return;
    data=++tmp;                 /* we should bypass whitespaces here too */
    if(*data != '*')
    {
        process = strtoul(data,&tmp,0);
        flags|=GOT_PROC;
    }
}


int main(void) {

    char s[] = "12 * * 32";
    parse(s);

    if (flags & GOT_PROG) printf("find prog %d\n", program);
    if (flags & GOT_VERS) printf("find vers %d\n", version);
    if (flags & GOT_PROC) printf("find proc %d\n", process);

    return 0;
}
