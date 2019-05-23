#include "file_writer.h"
#include "stdio.h"

void write_output_state_to_file(char *filepath, Output_state *output_state) {
    FILE *file = NULL;
    file = fopen(filepath, "w");
    if (file == NULL) {
        printf("Nie mozna utworzyc pliku %s\n", filepath);
        return;
    }
    Output_state *output_state_tmp = output_state;
    while (output_state_tmp != NULL) {
        fprintf(file, "IN: ");
        Input_state *input_state_tmp = output_state_tmp->input_state;
        while (input_state_tmp != NULL) {
            fprintf(file, "%d:%d ", input_state_tmp->input_id, input_state_tmp->input_value);
            input_state_tmp = input_state_tmp->next;
        }
        fprintf(file, "OUT: %d:%d\n", output_state_tmp->output_id, output_state_tmp->output_value);
        output_state_tmp = output_state_tmp->next;
    }

    fclose(file);
}