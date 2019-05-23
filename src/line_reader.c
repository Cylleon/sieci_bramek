#include "line_reader.h"

char* read_one_line_from_file(FILE* file) {
    char *line = NULL;
    char ch;
    int size = 0;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            ch = '\0';
        }
        size += 1;
        char *tmp = NULL;
        if (line != NULL) {
            tmp = line;
        }
        line = (char*) malloc(sizeof(char) * size);
        if (tmp != NULL) {
            int i = 0;
            for (; i < size; i++) {
                line[i] = tmp[i];
            }
            free(tmp);
        }
        line[size - 1] = ch;
        if (ch == '\0') {
            break;
        }
    }
    if (line != NULL) {
        char *tmp = line;
        line = malloc(sizeof(char) + sizeof(char) * size);
        int i = 0;
        for (; i < size; i++) {
            line[i] = tmp[i];
        }
        line[size] = '\0';
        free(tmp);
    }
    return line;
}

Node* create_node_from_line_of_text(char* line) {
    Node* node = create_empty_node();
    Line_phase phase = LOGIC_GATE_TYPE_PHASE;
    char logic_gate_text[5] = "\0\0\0\0\0";
    int i = 0;
    int number_of_char = 0;
    while (line[i] != '\0') {
        if (line[i] == ' ') {
            i += 1;
            continue;
        }
        if (phase == LOGIC_GATE_TYPE_PHASE) {
            logic_gate_text[number_of_char] = line[i];
            number_of_char += 1;
            if (line[i + 1] == ' ' || line[i + 1] == ':') {
                int gate_type = 0;
                for (; gate_type < number_of_gate_types; ++gate_type) {
                    if (strcmp (logic_gate_text, gate_string[gate_type]) == 0) {
                        node->gate = gate_type;
                        break;
                    }
                }
                if (node->gate == NO_GATE) {
                    return NULL;
                }
                phase = FIRST_INPUT_NODE_PHASE;
            }
        } else if (phase == FIRST_INPUT_NODE_PHASE) {
            node ->input_node_id_1 = (line[i] - '0');
            phase = SECOND_INPUT_NODE_PHASE;
        } else if (phase == SECOND_INPUT_NODE_PHASE) {
            if (node->gate == NEG) {
                phase = OUTPUT_NODE_PHASE;
                i += 1;
                continue; // NEG gate doesn't has second input node
            }

            node->input_node_id_2 = (line[i] - '0');
            phase = OUTPUT_NODE_PHASE;
        } else if (phase == OUTPUT_NODE_PHASE) {
            node->output_node_id = (line[i] - '0');
            break;
        }

        i += 1;
    }

    return node;
}

Node* create_input_nodes_from_line_of_text(char *line) {
    Node* node = create_empty_node();
    Node* tmp = node;
    int i = 0;
    while (line[i] != '\0') {
        if (line[i] >= '0' && line[i] <= '9') {
            if (node->output_node_id == -1) {
                node->output_node_id = line[i] - '0';
            } else {
                if (tmp->next == NULL) {
                    tmp->next = create_empty_node();
                }
                tmp->next->output_node_id = line[i] - '0';
                tmp = tmp->next;
            }
        }
        i += 1;
    }

    return node;
}

int read_output_id_from_line_of_text(char *line) {
    int i = 0;
    while(line[i] != '\0') {
        if (line[i] >= '0' && line[i] <= '9') {
            return line[i] - '0';
        }
        i += 1;
    }

    return -1;
}

Input_state* read_input_state_from_line_of_text(char *line) {
    Input_state *input_state = create_empty_input_state();
    Input_state *tmp_input_state = input_state;
    int i = 0;
    while (line[i] != '\0') {
        if (line[i] >= '0' && line[i] <= '9' && line[i+1] == ':') {
            if (input_state->input_id == -1) {
                input_state->input_id = line[i] - '0';
                input_state->input_value = line[i + 2] - '0';
            } else {
                if (tmp_input_state->next == NULL) {
                    tmp_input_state->next = create_empty_input_state();
                }
                tmp_input_state->next->input_id = line[i] - '0';
                tmp_input_state->next->input_value = line[i + 2] - '0';
                tmp_input_state = tmp_input_state->next; 
            }
            
        }
        i += 1;
    }

    return input_state;
}