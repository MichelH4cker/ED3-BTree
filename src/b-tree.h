#ifndef __B_TREE_H__
#define __B_TREE_H__

#define M 5

#include "index_file.h"

/**
 * @brief nó da árvore-B. 
 * A ordem da árvore é 5 (m = 5). Dessa forma, um nó (página) terá 4 chaves de busca e 5 descendentes. 
 * A chave de busca da árvore é o campo idConecta. 
 */
typedef struct node {
    char folha;      // 1 byte
    int nroChavesNo; // 4 bytes
    int alturaNo;    // 4 bytes
    int RRNdoNo;     // 4 bytes

    int numberOfKeys; // número de keys do node (n < M). A chave do nó é o campo idConecta
    int keys[M - 1]; // array de keys
    struct node *pointers[M]; // M ponteiros para filhos
} node;

/**
 * @brief faz busca na árvore B
 * @param rrn rrn da página a ser pesquisada
 * @param target chave que está sendo procurada
 * @param found_rrn página que contém a chave procurada
 * @param found_pos posição da chave na página
*/
void search(int rrn, int target, int found_rrn, int found_pos);

#endif