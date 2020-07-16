#include "balance.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//initializes a state with NULL
State init_state () {
    return NULL;
}

//Inserts a new node to a given a State
void insert_head (State *l, float value, char *desc, State sub) {
    while (*l) {
        l = &(*l)->next;
    }
    State r = malloc (sizeof(Node));

    r->value = value;
    r->desc = strdup(desc);
    r->subset = sub;
    r->next = NULL;

    *l = r;
}

//Initializes a balance state with a given Description and value
State init_balance (char *desc, float value) {
    State r = init_state();
    insert_head(&r, value, desc, NULL);

    return r;
}

float update_values (State *state) {
    float total = 0;
    if (*state) {
        State sub = (*state)->subset;
        if (sub) (*state)->value = update_values(sub);
        total = (*state)->value + update_values((*state)->next);
    }

    return total;
}
