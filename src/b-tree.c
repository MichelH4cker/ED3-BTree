#include "b-tree.h"

void search(int rrn, int target, int found_rrn, int found_pos) {
    node node;
    //acha o node com o rrn passado

    for (int i = 0; i < node.numberOfKeys; i++) {
        if (target == node.keys[i]) {         //encontrou
            printf ("ENCONTROU\n");
            break;
        }
        else if (node.folha == '0') {
            if (target < node.keys[i]) {
                search(node.pointers[i]->RRNdoNo, target, found_rrn, found_pos);
                break;
            }
            if (i < node.numberOfKeys - 1 && target < node.keys[i + 1])
                search(node.pointers[i + 1]->RRNdoNo, target, found_rrn, found_pos);
            else if (i == node.numberOfKeys - 1 && target > node.keys[i])
                search(node.pointers[i + 1]->RRNdoNo, target, found_rrn, found_pos);
        }
        else if (i == node.numberOfKeys - 1)
            printf("Registro inexistente.\n");
    }
}