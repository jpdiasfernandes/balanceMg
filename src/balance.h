#ifndef BALANCEMG_BALANCE_H
#define BALANCEMG_BALANCE_H


typedef struct state {
    float value;
    char *desc;
    struct state *subset;
    struct state *next;
} *State, Node;

State init_state ();
State insert_head (State l, float value, char *desc, State sub);
State init_balance (char *desc, float s);
#endif //BALANCEMG_BALANCE_H
