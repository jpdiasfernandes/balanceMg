#include "files.h"
#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "balance.h"
#define BUF_SIZE 1024
#include <string.h>

void save_file (State *state, char *path) {
    FILE *file = fopen(path, "w");

    if (file) print_state(state, 0, file);
}
State load_file (char *path) {
    FILE *file = fopen(path, "r");
    State state = init_state();
    char *line;
    char **args;
    int flag = 1;
    do {
        line = readLine(file);
        args = parseLine(line, " ");
        if (*line != EOF) add(args, &state, "set");
        else flag = 0;
    }while (flag);
    return state;
}

void print_paths(State state, char *parent_path, FILE *file) {
    if (state) {
        int bufsize = BUF_SIZE;
        char *desc = malloc (bufsize);
        char *original = strdup(parent_path);
        strcpy(desc, state->desc);
        strcat(desc, "/");
        strcat(parent_path, desc);
        strcpy(desc,parent_path);
        strcpy(parent_path, original);
        if (!state->subset) fprintf(file, "%s %.2f\n", desc,state->value);
        else print_paths(state->subset, desc, file);
        print_paths(state->next, parent_path, file);
    }
}
