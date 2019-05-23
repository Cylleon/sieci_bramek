#ifndef SIECBRAMEK_LOGICAL_CIRCUIT_H
#define SIECBRAMEK_LOGICAL_CIRCUIT_H

#include "node.h"

struct logical_circuit_t {
    int output_id;
    Node* nodes;
};
typedef struct logical_circuit_t Logical_circuit;

struct input_state_t {
    int input_id;
    int input_value;
    struct input_state_t *next;
};
typedef struct input_state_t Input_state;

struct input_state_change_t {
    Input_state *input_state;
    struct input_state_change_t *next;
};
typedef struct input_state_change_t Input_state_change;

struct output_state_t {
    Input_state *input_state;
    int output_id;
    int output_value;
    struct output_state_t *next;
};
typedef struct output_state_t Output_state;

void free_logical_circuit_from_memory(Logical_circuit *logical_circuit);

void free_input_state_from_memory(Input_state *input_state);

void free_input_state_change_from_memory(Input_state_change *input_state_change);

void free_output_state_from_memory(Output_state *output_state);

Logical_circuit* create_empty_logical_circuit();

Input_state* create_empty_input_state();

Input_state_change* create_empty_input_state_change();

void reset_logical_circuit(Logical_circuit *logical_circuit);

Output_state* create_empty_output_state();

void set_input_for_logical_circuit(Logical_circuit *logical_circuit, Input_state *input_state);

Output_state* calculate_output_state(Logical_circuit *logical_circuit, Input_state_change *input_state_change);

void display_output_state_on_console(Output_state *output_state);


#endif