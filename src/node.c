//
// Created by pmielanczyk on 31.03.19.
//

#include "node.h"
#include "logic_gates.h"

int simulate_node(Node* nodes, int output_node_id) {
    Node *tmp = nodes;
    while (tmp->next != NULL)
    {
        if (tmp->output_node_id == output_node_id) {
            break;
        }
        tmp = tmp->next;
    }
    
    switch (tmp->gate) {
        case AND:
            return and(simulate_node(nodes, tmp->input_node_id_1),
                    simulate_node(nodes, tmp->input_node_id_2));
        case NAND:
            return nand(simulate_node(nodes, tmp->input_node_id_1),
                        simulate_node(nodes, tmp->input_node_id_2));
        case OR:
            return or(simulate_node(nodes, tmp->input_node_id_1),
                        simulate_node(nodes, tmp->input_node_id_2));
        case NOR:
            return nor(simulate_node(nodes, tmp->input_node_id_1),
                        simulate_node(nodes, tmp->input_node_id_2));
        case XOR:
            return xor(simulate_node(nodes, tmp->input_node_id_1),
                        simulate_node(nodes, tmp->input_node_id_2));
        case XNOR:
            return xnor(simulate_node(nodes, tmp->input_node_id_1),
                        simulate_node(nodes, tmp->input_node_id_2));
        case NEG:
            return neg(simulate_node(nodes, tmp->input_node_id_1));
        case NO_GATE:
            return tmp->output_value;
        default:
            return 0;
    }
}

Node* create_empty_node() {
    Node *node = (Node*) malloc(sizeof(Node));

    node->input_node_id_1 = -1;
    node->input_node_id_2 = -1;
    node->gate = NO_GATE;
    node->output_node_id = -1;
    node->output_value = -1;
    node->next = NULL;

    return node;
}
