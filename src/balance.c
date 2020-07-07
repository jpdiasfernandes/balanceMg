#include "balance.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

LBal init_lbal () {
    return NULL;
}

LBal insert_head (LBal l, float value, char *desc, LBal sub) {
    LBal *a = &l;
    while (*a) {
        a = &(*a)->next;
    }
    LBal r = malloc (sizeof(Node));

    r->value = value;
    r->desc = strdup(desc);
    r->subset = sub;
    r->next = NULL;

    *a = r;

    return l;
}

LBal init_balance (char *desc, float value) {
    LBal r = init_lbal();
    r = insert_head(r, value, desc, NULL);

    return r;
}

