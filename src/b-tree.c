#include "b-tree.h"

void search(struct node node, int target) {
    for (int i = 0; i < node.numberOfKeys; i++) {
        if (target == node.keys[i]) {         //encontrou
            printf ("ENCONTROU\n");
            break;
        }
        else if (node.folha == '0') {
            if (target < node.keys[i]) {
                search(*node.pointers[i], target);
                break;
            }
            if (i < node.numberOfKeys - 1 && target < node.keys[i + 1])
                search(*node.pointers[i + 1], target);
            else if (i == node.numberOfKeys - 1 && target > node.keys[i])
                search(*node.pointers[i + 1], target);
        }
        else if (i == node.numberOfKeys - 1)
            printf("Registro inexistente.\n");
    }
}