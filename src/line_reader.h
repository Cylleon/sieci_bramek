#ifndef SIECBRAMEK_LINE_READER_H
#define SIECBRAMEK_LINE_READER_H
#include <stdio.h>
#include "logical_circuit.h"

typedef enum line_phase_t {
    LOGIC_GATE_TYPE_PHASE,
    FIRST_INPUT_NODE_PHASE,
    SECOND_INPUT_NODE_PHASE,
    OUTPUT_NODE_PHASE,
} Line_phase;

char* read_one_line_from_file(FILE *file);

Node* create_node_from_line_of_text(char *line);

Node* create_input_nodes_from_line_of_text(char *line);

int read_output_id_from_line_of_text(char *line);

Input_state* read_input_state_from_line_of_text(char *line);

#endif