#ifndef SIECBRAMEK_FILE_READER_H
#define SIECBRAMEK_FILE_READER_H

#include "logical_circuit.h"

Logical_circuit* read_logical_circuit_file(char* filepath);

Input_state_change* read_input_state_file(char* filepath);

#endif