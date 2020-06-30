#include "interface.h"
#include <stdio.h>
#include <stdlib.h>
#define BUF_SIZE 1024

void shell () {
    char *line;
    char **args;
    int flag;

    printf ("> ");

    do {
        line = readLine();
    } while (flag);

}

char *readLine () { //should I just use fgets or do a complicated non useful function myself?
    int bufsize = BUF_SIZE;
    char *line = malloc (bufsize);
    int index = 0;

    while (line) {
       char c = getchar();
       if (index >= bufsize) {
           bufsize += BUF_SIZE;
           line = realloc(line, bufsize);
       }
       line[index++] = c;
       if (c == '\n' || c == 0) return line;
    }
}

