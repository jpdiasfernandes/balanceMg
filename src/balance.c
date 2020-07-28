#include "balance.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUF_SIZE 1024

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
        if ((*state)->subset) (*state)->value = update_values(&(*state)->subset);
        total = (*state)->value + update_values(&(*state)->next);
    }

    return total;
}

State add_balance (State state, char **path, float value, int *flag, char *mode) { //If the value is added return value will be 1
    if (!*path) return state;
    if (!state  && (*path)) insert_head(&state, value, path[0], NULL);
    if (!strcmp(state->desc, *path)) {
        if (!state->subset && !path[1]) {
           state->value = (!strcmp(mode, "add"))? state->value + value : value;
           *flag = 1;
        }
        else if (!state->subset) {
            //Here we set the value to 0 since only the leafs contribute
            //to the total amount of money.
            insert_head(&state->subset, 0, path[1], NULL);
            *flag = 1;
        }
        state->subset = add_balance(state->subset, &path[1], value, flag, mode);
    }
    else {
        if (!state->next) {
            insert_head(&state, 0, *path, NULL);
            *flag = 1;
        }
        state->next = add_balance(state->next, path, value, flag, mode);
    }
    return state;

}

State delete_entry (State state, char **path, int *flag) {
    if (!state || !(*path)) return state;
    if (!strcmp(state->desc, *path)) {
        if (!path[1]) {
            *flag = 1;
            return state->next;
        }
        state->subset = delete_entry(state->subset, &path[1], flag);
    }
    else state->next = delete_entry(state->next, &path[0], flag);
}









