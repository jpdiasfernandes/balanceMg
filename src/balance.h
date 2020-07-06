#ifndef BALANCEMG_BALANCE_H
#define BALANCEMG_BALANCE_H


typedef struct linkbal {
    float value;
    char *desc;
    struct linkbal *subset;
    struct linkbal *next;
} *LBal, Node;
#endif //BALANCEMG_BALANCE_H
