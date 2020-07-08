/*
 * Module in charge of the Input and Output on the shell.
 * Every function that has to do with interacting with the user.
 */
#include "balance.h"
#ifndef BALANCEMG_INTERFACE_H
#define BALANCEMG_INTERFACE_H
void shell (State *state);
char *readLine ();
char **parseLine (char *line);
int interpreter (char **args, State *state);
void help();
void intro();
int new (char **args, State *state);
void print_state(State *state);
#endif //BALANCEMG_INTERFACE_H
