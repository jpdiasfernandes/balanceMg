#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
    FILE *input;
    char *path;
    if (argc == 1) input = stdin; //Choosing information path
    else {
        input = fopen(argv[1]);
        path = strdup(argv[1]);
    }

    if (!input) { //If fopen has a problem opening the file path prints a message and changes input to stdin
        printf("Error: path is faulty or doesn't exist.");
        input = stdin;
    }

    menu(input);
}

