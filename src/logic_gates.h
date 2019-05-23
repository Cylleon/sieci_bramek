//
// Created by pmielanczyk on 30.03.19.
//

#ifndef SIECBRAMEK_LOGIC_GATES_H
#define SIECBRAMEK_LOGIC_GATES_H

enum gate_t {
    AND = 0, NAND = 1, OR = 2, NOR = 3, XOR = 4, XNOR = 5, NEG = 6, NO_GATE = 7
};
typedef enum gate_t Gate;
static const char *gate_string[] = {
        "AND", "NAND", "OR", "NOR", "XOR", "XNOR", "NEG", "NO_GATE"
};
static const char number_of_gate_types = 7;



int and(int input_1, int input_2);

int nand(int input_1, int input_2);

int or(int input_1, int input_2);

int nor(int input_1, int input_2);

int xor(int input_1, int intput_2);

int xnor(int input_1, int input_2);

int neg(int input_1);

#endif //SIECBRAMEK_LOGIC_GATES_H
