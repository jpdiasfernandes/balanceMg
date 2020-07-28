#include "interface.h"
#include "balance.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "files.h"
#define BUF_SIZE 1024

    //TODO : Add prompts to confirm some actions
void shell (State *state) {
    char *line;
    char **args;
    int flag = 1;

    printf("For more information type 'intro' or 'help'.\n");
    do {
        printf("balance> ");
        line = readLine(stdin);
        args = parseLine(line, " \n\t");
        flag = interpreter(args, state);
    } while (flag); //if flag = 1 i.e exit has been ordered the
                    // shell finishes it porpuse and the app is
                    // shutted down

}

//Stores the input into a string
char *readLine (FILE *file) {
    int bufsize = BUF_SIZE; //bufsize is inialized with BUF_SIZE;
    char *line = malloc (bufsize);
    int index = 0;
    while (line) {
       char c = fgetc(file);
       if (index >= bufsize) { //if index equals the size of bufsize, bufize increments itself by BUF_SIZE
           bufsize += BUF_SIZE;
           line = realloc(line, bufsize);
       }
       line[index++] = c;
       if (c == '\n' || c <= 0 || c == EOF) return line; //if c is new line or EOF the line is ready to be returned
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
        print_state(state, 0,stdout);
    else if (!strcmp(s, "add"))
        add (&args[1], state);
    else if (!strcmp(s, "delete"))
        delete (&args[1], state);
    else if (!strcmp(s, "save"))
        save (args[1], state);
    else if (!strcmp(s, "load"))
        load(args[1], state);
    else if (!strcmp(s, "quit")) r = 0;
    else (puts("Instructions unclear abort!"));
    return r;
}

//Displays all the commands and features
void help () {
    char *help  = "This is help! Here you can see all the available commands and their purpose.\n"
                  "     'new' -> creates the main path 'Total'. You can initialize it with a value. Ex: 'new 100'.\n"
                  "     'print' -> prints the current state of the balance.\n"
                  "     'add' -> given a path it adds or creates a given path (depending if the path already exists) with a\n"
                  " certain value. Ex : 'add Total/orienteering/shoes 200'.\n"
                  " If the path does not exist then it will create the nodes missing and will start the leaf node with 200.\n"
                  "     'delete' -> given a path it deletes the node and the subsets bellow that node.\n"
                  "     'quit' -> exits the program.";

    puts(help);
}

//Displays an introduction to the app
void intro () {
    char *s = " This is an intro to the app and in a way a tutorial.\n"
              " My plan was to create a simple app so I could organize my money.\n"
              " Keep in mind that this is a leaf based model. This meaning that the total value is based on the leaf nodes\n"
              "of the balance. Ex: Total/home/painting the value of Total will only account for panting value.\n"
              " This way you shouldn't be able to set nor add values to other nodes other than leaf nodes.";
    puts(s);
}

//Creates a new state erasing the existing one
int new (char **args, State *state) {
    if (alertPrompt("Are you sure? It will remove your current balance!")) {
        float value;
        if (args[0]) {
            value = strFloat(args[0]); //If not a valid number it sets value to 0
            *state = init_balance("Total", value);
        }
        else *state = init_balance("Total", 0);

    }

}

//Prints the current state of the balance
void print_state (State *state, int tabs, FILE *path) {
    if (*state) {
        State sub = (*state)->subset;
        print_tabs(tabs, path);
        fprintf(path,"->%s : %.2f\n", (*state)->desc, (*state)->value);
        print_state(&sub, tabs+1,path);
        print_state(&(*state)->next,tabs, path);
    }
}

void print_tabs (int tabs, FILE *path) {
    int i;

    for (i = 0; i < tabs; i++)
        fputc('\t', path);
}


void add (char **args, State *state) {
    char **path;
    float value = 0;
    int flag = 0;
    if (args[0]) {
       path = parseLine(args[0], "/");
       if (args[1]) value = strFloat(args[1]);
       *state = add_balance(*state, path, value, &flag); 
       if (flag == 0) printf("Please verify if the path is valid. You can only add value to leaf nodes.\n");
       update_values(state);
    }
}

void delete (char **args, State *state) {
    char **path;
    int flag = 0;
    if (alertPrompt("Deleting will make you lose all the information connecting to that path.")) {
        if (args[0]) {
            path = parseLine(args[0], "/");
            *state = delete_entry(*state, path, &flag);
            if (flag == 0) printf("Please verify if the path is valid\n");
        }
    }
}

float strFloat (char *string) {
   return strtod(string,NULL); //returns 0 if an error occurs.
}

void save (char *file_path, State *state) {
    FILE *fp;
   if (fp = fopen(file_path, "w")) {
       char *parent_path = malloc(BUF_SIZE);
       parent_path = strcpy(parent_path, "");
       print_paths(*state, parent_path, fp);
   }
}

void load (char *file_path, State *state) {
    if (alertPrompt("Loading a new balance will erase your current one!") && fopen(file_path, "r")) {
            *state = load_file(file_path);
    }
}

int alertPrompt (char *alert) {
    int r = 0;
    char *resLine;
    char **resParsed;

    printf("%s %s ", alert, "(Y/N)");
    resLine = readLine(stdin);
    resParsed = parseLine(resLine, "\n ");
    if (!strcmp(*resParsed, "Y")) r = 1;
    return r;
}








