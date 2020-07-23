/*
 *  Module in charge of the loading and saving the state from and to text files.
 */
#include "balance.h"
#include <stdio.h>
#ifndef INC_50QUESTOES_FILES_H
#define INC_50QUESTOES_FILES_H
void save_file (State *state, char *path);
State load_file (char *path);
void print_paths (State state, char *parent_path, FILE *file);
#endif //INC_50QUESTOES_FILES_H
