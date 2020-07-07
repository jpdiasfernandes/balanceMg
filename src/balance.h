#ifndef BALANCEMG_BALANCE_H
#define BALANCEMG_BALANCE_H


typedef struct linkbal {
    float value;
    char *desc;
    struct linkbal *subset;
    struct linkbal *next;
} *LBal, Node;

LBal init_lbal ();
LBal insert_head (LBal l, float value, char *desc, LBal sub);
LBal init_balance (char *desc, float s);
#endif //BALANCEMG_BALANCE_H
