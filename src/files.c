#include "files.h"
#include <stdio.h>
#include <stdlib.h>
#include "interface.h"

void save_file (State *state, char *path) {
    FILE *file = fopen(path, "w");

    if (file) print_state(state, 0, file);
}

void load_file (char *path) {
    FILE *file = fopen(path, "r");

    if (file) {

    }
}
