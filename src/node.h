//
// Created by pmielanczyk on 31.03.19.
//

#ifndef SIECBRAMEK_NODE_H
#define SIECBRAMEK_NODE_H

#include <stdlib.h>
#include "logic_gates.h"

struct node_t {
    int input_node_id_1;
    int input_node_id_2;
    Gate gate;
    int output_node_id;
    int output_value;
    struct node_t *next;
};
typedef struct node_t Node;

int simulate_node(Node* nodes, int output_node_id);

Node* create_empty_node();


#endif //SIECBRAMEK_NODE_H
