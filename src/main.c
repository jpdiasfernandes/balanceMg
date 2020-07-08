#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "balance.h"

int main () {
    FILE *input;
    char *path;

    State state = init_state();
    shell(&state);


}

