#include "logical_circuit.h"
#include <stdio.h>

void free_logical_circuit_from_memory(Logical_circuit *logical_circuit) {
    Node *current_tmp = logical_circuit->nodes;
    Node *next_tmp;
    while (current_tmp != NULL) {
        next_tmp = current_tmp->next;
        free(current_tmp);
        current_tmp = next_tmp;
    }

    free(logical_circuit);
}

void free_input_state_from_memory(Input_state *input_state) {
    Input_state *current_tmp = input_state;
    Input_state *next_tmp = NULL;
    while (current_tmp != NULL) {
        next_tmp = current_tmp->next;
        free(current_tmp);
        current_tmp = next_tmp;
    }
}

void free_input_state_change_from_memory(Input_state_change *input_state_change) {
    Input_state_change *current_tmp = input_state_change;
    Input_state_change *next_tmp = NULL;
    while (current_tmp != NULL) {
        next_tmp = current_tmp->next;
        free_input_state_from_memory(current_tmp->input_state);
        free(current_tmp);
        current_tmp = next_tmp;
    }
}

void free_output_state_from_memory(Output_state *output_state) {
    Output_state *current_tmp = output_state;
    Output_state *next_tmp = NULL;
    while (current_tmp != NULL) {
        next_tmp = current_tmp->next;
        free(current_tmp);
        current_tmp = next_tmp;
    }
}

Logical_circuit* create_empty_logical_circuit() {
    Logical_circuit *logical_circuit = (Logical_circuit*) malloc(sizeof(Logical_circuit));

    logical_circuit->output_id = -1;
    logical_circuit->nodes = NULL;

    return logical_circuit;
}

Input_state* create_empty_input_state() {
    Input_state *input_state = (Input_state*) malloc(sizeof(Input_state));
    
    input_state->input_id = -1;
    input_state->input_value = -1;
    input_state->next = NULL;

    return input_state;
}

Input_state_change* create_empty_input_state_change() {
    Input_state_change *input_state_change = (Input_state_change*) malloc(sizeof(Input_state_change));

    input_state_change->input_state = NULL;
    input_state_change->next = NULL;

    return input_state_change;
}

void reset_logical_circuit(Logical_circuit *logical_circuit) {
    Node* tmp = logical_circuit->nodes;
    while (tmp != NULL) {
        tmp->output_value = -1;
        tmp = tmp->next;
    }
}

Output_state* create_empty_output_state() {
    Output_state *output_state = (Output_state*) malloc(sizeof(Output_state));

    output_state->input_state = NULL;
    output_state->output_id = -1;
    output_state->output_value = -1;
    output_state->next = NULL;

    return output_state;
}

void set_input_for_logical_circuit(Logical_circuit *logical_circuit, Input_state *input_state) {
    Input_state* input_state_tmp = input_state;
    while (input_state_tmp != NULL) {
        Node *node_tmp = logical_circuit->nodes;
        while (node_tmp != NULL)
        {
            if (node_tmp->output_node_id == input_state_tmp->input_id) {
                node_tmp->output_value = input_state_tmp->input_value;
            }
            node_tmp = node_tmp->next;
        }
        input_state_tmp = input_state_tmp->next;
    }
}

Output_state* calculate_output_state(Logical_circuit *logical_circuit, Input_state_change *input_state_change) {
    Output_state *output_state = NULL;
    Output_state *output_state_tmp = NULL;
    Input_state_change *tmp = input_state_change;

    while (tmp != NULL) {
        if (output_state == NULL) {
            output_state = create_empty_output_state();
            output_state->input_state = tmp->input_state;
            reset_logical_circuit(logical_circuit);
            set_input_for_logical_circuit(logical_circuit, tmp->input_state);
            output_state->output_id = logical_circuit->output_id;
            output_state->output_value = simulate_node(logical_circuit->nodes, logical_circuit->output_id);
            output_state_tmp = output_state;
        } else {
            if (output_state_tmp->next == NULL) {
                output_state_tmp->next = create_empty_output_state();
            }
            output_state_tmp->next->input_state = tmp->input_state;
            reset_logical_circuit(logical_circuit);
            set_input_for_logical_circuit(logical_circuit, tmp->input_state);
            output_state_tmp->next->output_id = logical_circuit->output_id;
            output_state_tmp->next->output_value = simulate_node(logical_circuit->nodes, logical_circuit->output_id);

            output_state_tmp = output_state_tmp->next;
        }

        tmp = tmp->next;
    }
    
    return output_state;
}

void display_output_state_on_console(Output_state *output_state) {
    
    Output_state *output_state_tmp = output_state;
    while (output_state_tmp != NULL) {
        printf("IN: ");
        Input_state *input_state_tmp = output_state_tmp->input_state;
        while (input_state_tmp != NULL) {
            printf("%d:%d ", input_state_tmp->input_id, input_state_tmp->input_value);
            input_state_tmp = input_state_tmp->next;
        }
        printf("OUT: %d:%d\n", output_state_tmp->output_id, output_state_tmp->output_value);
        output_state_tmp = output_state_tmp->next;
    }
}