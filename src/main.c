#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "file_reader.h"
#include "file_writer.h"


int main(int argc, char *argv[]) {
    int i;
    char *circuit_filepath = NULL;
    char *input_filepath = NULL;
    char *output_filepath = NULL;
    int print_output_to_console = 0;
    for (i = 1; i < argc; ++i) {
        char* arg = argv[i];
        if (strcmp(arg, "-u") == 0) {
            circuit_filepath = argv[i + 1];
            i += 1;
        } else if (strcmp(arg, "-i") == 0) {
            input_filepath = argv[i + 1];
            i += 1;
        } else if (strcmp(arg, "-o") == 0) {
            output_filepath = argv[i + 1];
            i += 1;
        } else if (strcmp(arg, "-p") == 0) {
            print_output_to_console = 1;
        } else {
            printf("Nieznany argument '%s'\n", arg);
            return 1;
        }
    }
    if (circuit_filepath == NULL) {
        printf("Nie podano pliku wejscowego z ukladem.\n");
        return 1;
    }
    if (input_filepath == NULL) {
        printf("Nie podano pliku wejscowego ze stanem wejsc.\n");
        return 1;
    }
    if (output_filepath == NULL) {
        printf("Nie podano pliku wyjscowego.\n");
        return 1;
    }

    Logical_circuit *logical_circuit = read_logical_circuit_file(circuit_filepath);
    if (logical_circuit == NULL) {
        return 1;
    }
    Input_state_change *input_state_change = read_input_state_file(input_filepath);
    if (input_state_change == NULL) {
        return 1;
    }

    Output_state *output_state = calculate_output_state(logical_circuit, input_state_change);

    if (print_output_to_console) {
        display_output_state_on_console(output_state);
    }

    write_output_state_to_file(output_filepath, output_state);

    free_logical_circuit_from_memory(logical_circuit);
    free_input_state_change_from_memory(input_state_change);
    free_output_state_from_memory(output_state);
    
    return 0;
}