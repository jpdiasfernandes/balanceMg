/*
 * Module in charge of the Input and Output on the shell.
 * Every function that has to do with interacting with the user.
 */
#ifndef BALANCEMG_INTERFACE_H
#define BALANCEMG_INTERFACE_H
void shell();
char *readLine();
char **parseLine(char *line);
#endif //BALANCEMG_INTERFACE_H
