#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
    FILE *input;
    if (argc == 1) input = stdin;
    else input = fopen(argv[1]);

    if (!input) {
        printf("Error: path is faulty or doesn't exist.");
        input = stdin;
    }

    menu(input);
}

