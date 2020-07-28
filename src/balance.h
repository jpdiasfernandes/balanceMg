#ifndef BALANCEMG_BALANCE_H
#define BALANCEMG_BALANCE_H


typedef struct state {
    float value;
    char *desc;
    struct state *subset;
    struct state *next;
} *State, Node;

State init_state ();
void insert_head (State *l, float value, char *desc, State sub);
State init_balance (char *desc, float value);
float update_values (State *state);
State add_balance (State state, char **path, float value, int *flag, char *mode);
State delete_entry (State state, char **path, int *flag);
#endif //BALANCEMG_BALANCE_H
