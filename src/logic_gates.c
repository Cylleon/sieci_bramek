//
// Created by pmielanczyk on 30.03.19.
//
#include "logic_gates.h"

int and(int input_1, int input_2) {
    if (input_1 && input_2)
        return 1;
    else
        return 0;
}

int nand(int input_1, int input_2) {
    return !and(input_1, input_2);
}

int or(int input_1, int input_2) {
    if (input_1 || input_2)
        return 1;
    else
        return 0;
}

int nor(int input_1, int input_2) {
    return !or(input_1, input_2);
}

int xor(int input_1, int input_2) {
    if ((input_1 && !input_2) || (!input_1 && input_2))
        return 1;
    else
        return 0;
}

int xnor(int input_1, int input_2) {
    if (input_1 == input_2)
        return 1;
    else
        return 0;
}

int neg(int input_1) {
    return !input_1;
}