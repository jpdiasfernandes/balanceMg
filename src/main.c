#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "balance.h"

int main () {
    FILE *input;
    char *path;

    LBal state = init_lbal();
    shell(state);


}

