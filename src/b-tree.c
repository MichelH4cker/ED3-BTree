#include "b-tree.h"

int search(int rrn, int target, int found_rrn, int found_pos) {
    if (rrn == -1)
        return 1;       //nao encontrou a chave de busca
    
    node node;
    //acha o node com o rrn passado

    for (int i = 0; i < node.numberOfKeys; i++) {
        if (target == node.keys[i]) {         //encontrou
            printf ("ENCONTROU\n");
            return 0;       //encontrou
        }
        else if (node.folha == '0') {
            if (target < node.keys[i])
                return(search(node.pointers[i]->RRNdoNo, target, found_rrn, found_pos));
            if (i < node.numberOfKeys - 1 && target < node.keys[i + 1])
                return(search(node.pointers[i + 1]->RRNdoNo, target, found_rrn, found_pos));
            else if (i == node.numberOfKeys - 1 && target > node.keys[i])
                return(search(node.pointers[i + 1]->RRNdoNo, target, found_rrn, found_pos));
        }
        else if (i == node.numberOfKeys - 1) {
            printf("Registro inexistente.\n");
            return 1;       // não encontrou
        }
    }
}