#include "interface.h"
#include "balance.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define BUF_SIZE 1024

void shell (State *state) {
    char *line;
    char **args;
    int flag = 1;

    printf("For more information type 'intro' or 'help'.\n");
    do {
        printf("balance> ");
        line = readLine();
        args = parseLine(line, " \n\t");
        flag = interpreter(args, state);
    } while (flag); //if flag = 1 i.e exit has been ordered the
                    // shell finishes it porpuse and the app is
                    // shutted down

}

//Stores the input into a string
char *readLine () {
    int bufsize = BUF_SIZE; //bufsize is inialized with BUF_SIZE;
    char *line = malloc (bufsize);
    int index = 0;
    while (line) {
       char c = getchar();
       if (index >= bufsize) { //if index equals the size of bufsize, bufize increments itself by BUF_SIZE
           bufsize += BUF_SIZE;
           line = realloc(line, bufsize);
       }
       line[index++] = c;
       if (c == '\n' || c == 0) return line; //if c is new line or EOF the line is ready to be returned
    }
}

//Parses the given Line in order to separate it into possible args
char **parseLine (char *line, const char*delim) {
    int bufsize = BUF_SIZE;
    char **args = malloc (sizeof(char *) * bufsize);
    char *token;
    int index = 0;

    token = strtok(line, delim); //Gets first token
    while (token != NULL) {
        args[index] = token;
        index++;

        if (index >= bufsize) { //if index equals the size of bufsize bufize increments itself by BUF_SIZE;
            bufsize += BUF_SIZE;
            args = realloc(args, bufsize * sizeof(char*));
        }

        token = strtok(NULL, delim);
    }
    args[index] = NULL;
    return args;
}

//Given a state and a list of args executes certain procedures
int interpreter (char **args, State *state) {
    int r = 1;
    char *s = args[0];

    if (!strcmp(s, "help"))
        help();
    else if (!strcmp(s,"intro"))
        intro();
    else if (!strcmp(s,"new"))
        new(&args[1], state);
    else if (!strcmp(s, "print"))
        print_state(state, 0);
    else if (!strcmp(s, "add"))
        add (&args[1], state);
    else if (!strcmp(s, "delete"))
        delete (&args[1], state);
    else if (!strcmp(s, "quit")) r = 0;
    else (puts("Instructions unclear abort!"));
    return r;
}

//Displays all the commands and features
void help () {
    char *help  = "This is help! Here you can see all the available commands and their purpose.\n"
                  " 'new' -> creates the main path 'Total'. You can initialize it with a value. Ex: 'new 100'.\n"
                  " 'print' -> prints the current state of the balance.\n"
                  " 'add' -> given a path it adds or creates a given path (depending if the path already exists) with a certain value.\n"
                  " 'quit' -> exits the program.";

    puts(help);
}

//Displays an introduction to the app
void intro () {
    char *s = "This is an intro to the app and in a way a tutorial."
              " My plan was to create a simple app so I could organize my money.\n"
              "Still a lot of work to do.";
    puts(s);
}

//Creates a new state erasing the existing one
int new (char **args, State *state) {
    float value;
    if (args[0]) {
        value = strFloat(args[0]); //If not a valid number it sets value to 0
        *state = init_balance("Total", value);
    }
    else *state = init_balance("Total", 0);

}

//Prints the current state of the balance
void print_state (State *state, int tabs) {
    if (*state) {
        State sub = (*state)->subset;
        print_tabs(tabs);
        printf("->%s : %.2f\n", (*state)->desc, (*state)->value);
        print_state(&sub, tabs+1);
        print_state(&(*state)->next,tabs);
    }
}

void print_tabs (int tabs) {
    int i;

    for (i = 0; i < tabs; i++)
        putchar('\t');
}


void add (char **args, State *state) {
    char **path;
    float value = 0;
    int flag = 0;
    if (args[0]) {
       path = parseLine(args[0], "/");
       if (args[1]) value = strFloat(args[1]);
       *state = add_balance(*state, path, value, &flag); 
       if (flag == 0) printf("Please verify if the path is valid\n");
       update_values(state);
    }
}

void delete (char **args, State *state) {
    char **path;
    int flag = 0;
    if (args[0]) {
        path = parseLine(args[0], "/");
        *state = delete_entry(*state, path, &flag);
        if (flag == 0) printf("Please verify if the path is valid\n");
    }
}

float strFloat (char *string) {
   return strtod(string,NULL); //returns 0 if an error occurs.
}













