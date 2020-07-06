#include "balance.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

LBal init_lbal () {
    return NULL;
}

LBal insert_head (LBal l, float value, char *desc, LBal sub) {
    LBal r = malloc (sizeof(Node));

    r->value = value;
    r->desc = strdup(desc);
    r->subset = sub;
    r->next = NULL;

    return r;
}
