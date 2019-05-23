#include <stdio.h>
#include <string.h>
#include "file_reader.h"
#include "line_reader.h"

enum file_phase_t {
    INPUT_PHASE,
    OUTPUT_PHASE,
    NODES_PHASE
};
typedef enum file_phase_t File_phase;

Logical_circuit* read_logical_circuit_file(char* filepath) {
    FILE *file;
    File_phase file_phase = INPUT_PHASE;
    file = fopen(filepath, "r");
    if (file == NULL) {
        printf("Nie można otworzyć pliku %s.\n", filepath);
        return NULL;
    }
    Logical_circuit* logical_circuit = create_empty_logical_circuit();
    Node *tmp_node = NULL;
    char *line;
    int failed = 0;
    
    do {
        line = read_one_line_from_file(file);
        if (line != NULL) {
            if (file_phase == INPUT_PHASE) {
                logical_circuit->nodes = create_input_nodes_from_line_of_text(line);
                if (logical_circuit->nodes == NULL) {
                   failed = 1;
                }
                file_phase = OUTPUT_PHASE;
            } else if (file_phase == OUTPUT_PHASE) {
                logical_circuit->output_id = read_output_id_from_line_of_text(line);
                if (logical_circuit->output_id == -1) {
                    failed = 1;
                    break;
                }
                file_phase = NODES_PHASE;
            } else if (file_phase == NODES_PHASE) {
                 if (tmp_node == NULL) {
                    tmp_node = logical_circuit->nodes;
                }
                while (tmp_node->next != NULL) {
                    tmp_node = tmp_node->next;
                }
                tmp_node->next = create_node_from_line_of_text(line);
                if (tmp_node->next == NULL) {
                    failed = 1;
                    break;
                }
                tmp_node = tmp_node->next;    
            }
        } else {
            break;
        }
    } while (line != NULL);

    fclose(file);

    if (failed) {
        printf("Wystapil problem z przeczytaniem lini - '%s' z pliku '%s'", line, filepath);
        free_logical_circuit_from_memory(logical_circuit);
        return NULL;
    }

    return logical_circuit;
}

Input_state_change* read_input_state_file(char* filepath) {
    FILE *file;
    file = fopen(filepath, "r");
    if (file == NULL) {
        printf("Nie można otworzyć pliku %s.\n", filepath);
        return NULL;
    }
    Input_state_change *input_state_change = create_empty_input_state_change();
    Input_state_change *tmp_input_state_change = input_state_change;
    char *line;
    int failed = 0;

    do {
        line = read_one_line_from_file(file);
        if (line == NULL) {
            break;
        }
        
        if (input_state_change->input_state == NULL) {
            input_state_change->input_state = read_input_state_from_line_of_text(line);
            if (input_state_change->input_state == NULL) {
                failed = 1;
                break;
            }
        } else {
            if (tmp_input_state_change->next == NULL) {
                tmp_input_state_change->next = create_empty_input_state_change();
            }
            tmp_input_state_change->next->input_state = read_input_state_from_line_of_text(line);
            if (tmp_input_state_change->next->input_state == NULL) {
                failed = 1;
                break;
            }
            tmp_input_state_change = tmp_input_state_change->next;
        }
    } while (line != NULL);
    
    fclose(file);

    if (failed) {
        printf("Wystapil problem z przeczytaniem lini - '%s' z pliku '%s'", line, filepath);
        free_input_state_change_from_memory(input_state_change);
        return NULL;
    }

    return input_state_change;
}