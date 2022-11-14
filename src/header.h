#ifndef __HEADER_H__
#define __HEADER_H__

#include "main.h"

typedef struct header {
    char status;        // 1 byte
    int noRaiz;         // 4 bytes
    int nroChavesTotal; // 4 bytes
    int alturaArvore;   // 4 bytes
    int RRNproxNo;      // 4 bytes
} header;

/**
 * @brief lê o cabeçalho de um arquivo
 * 
 * @param fp ponteiro do arquivo a ser lido
 * 
 * @return header cabeçalho lido do arquivo
 */
header readHeader(FILE *fp);

/**
 * @brief recebe uma struct header como parâmetro e mostra no terminal todos os dados contidos nelas 
 * 
 * @param header struct que guarda o cabeçalho a ser mostrado 
 */
void printHeader(header header);

#endif