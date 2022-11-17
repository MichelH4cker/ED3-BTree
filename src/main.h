#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdio.h>

#include "funcoesFornecidas.h"
#include "header.h"
#include "readCommand.h"

// SIZE
#define DISK_PAGE_SIZE 72;
#define REGISTER_SIZE 65;

#define M 5

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

struct filter {
    int  type; //tipo de dado
    int  field_key; // inteiro que refere-se ao comando
    int  number;
    char string[22];
};


#endif