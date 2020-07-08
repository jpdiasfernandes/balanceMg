#include "balance.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//initializes a state with NULL
State init_state () {
    return NULL;
}

//Inserts a new node to a given a State
State insert_head (State l, float value, char *desc, State sub) {
    State *a = &l;
    while (*a) {
        a = &(*a)->next;
    }
    State r = malloc (sizeof(Node));

    r->value = value;
    r->desc = strdup(desc);
    r->subset = sub;
    r->next = NULL;

    *a = r;

    return l;
}

//Initializes a balance state with a given Description and value
State init_balance (char *desc, float value) {
    State r = init_state();
    r = insert_head(r, value, desc, NULL);

    return r;
}

