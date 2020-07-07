#include "interface.h"
#include "balance.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUF_SIZE 1024

void shell (LBal *state) {
    char *line;
    char **args;
    int flag = 1;

    printf("For more information type 'intro' or 'help'.\n");
    do {
        printf("balance> ");
        line = readLine();
        args = parseLine(line);
        flag = interpreter(args, state);
    } while (flag);

}

char *readLine () {
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

char **parseLine (char *line) {
    int bufsize = BUF_SIZE;
    char **args = malloc (sizeof(char *) * bufsize);
    char *token;
    const char delim[10] =  " \n\t";
    int index = 0;

    token = strtok(line, delim);
    while (token != NULL) {
        args[index] = token;
        index++;

        if (index >= bufsize) {
            bufsize += BUF_SIZE;
            args = realloc(args, bufsize * sizeof(char*));
        }

        token = strtok(NULL, delim);
    }
    args[index] = NULL;
    return args;
}

int interpreter (char **args, LBal *state) {
    int i = 0;
    int r = 1;
    char *s = args[0];

    if (!strcmp(s, "help"))
        help();
    else if (!strcmp(s,"intro"))
        intro();
    else if (!strcmp(s,"new")) {
        char *desc;
        float value;
        if (args[1]) {
            value = strtod(args[1],NULL);
            *state = init_balance("Total", value);
        }
        else *state = init_balance("Total", 0);
    }
    else if (!strcmp(s, "print"))
        print_state(state);
    else r = 0;

    return r;
}

void help () {
    printf("This is help!");
}

void intro () {
    char *s = "This is an intro to the app and in a way a tutorial."
              " My plan was to create a simple app so I could organize my money.\n"
              "Still a lot of work to do.";
    puts(s);
}

void print_state (LBal *state) {
    if (*state) {
        LBal sub = (*state)->subset;
        printf("%s : %.2f\n", (*state)->desc, (*state)->value);
        if (sub) printf("\t->");
        print_state(&sub);
        print_state(&(*state)->next);
    }
}
