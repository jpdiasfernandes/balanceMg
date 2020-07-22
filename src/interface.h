/*
 * Module in charge of the Input and Output on the shell.
 * Every function that has to do with interacting with the user.
 */
#include <stdio.h>
#include "balance.h"
#ifndef BALANCEMG_INTERFACE_H
#define BALANCEMG_INTERFACE_H
void shell (State *state);
char *readLine ();
char **parseLine (char *line, const char *delim);
int interpreter (char **args, State *state);
void help();
void intro();
int new (char **args, State *state);
void print_state(State *state, int tabs, FILE *path);
float strFloat (char *string);
void add (char **args, State *state);
void print_tabs (int tabs, FILE *path);
void delete (char **args, State *state);
#endif //BALANCEMG_INTERFACE_H
