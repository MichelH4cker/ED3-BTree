#ifndef __INDEX_FILE_H__
#define __INDEX_FILE_H__

#include "main.h"

typedef struct header {
    char status;        // status do arquivo
    int noRaiz;         // RRN do nó raiz
    int nroChavesTotal; // 
    int alturaArvore;   // altura total da árvore
    int RRNproxNo;      // próximo RRN livre para inserção de um novo nó
} header;

/**
 * @brief Create a Header object
 * 
 * @param header 
 */
header createHeaderIndex();

/**
 * @brief 
 * 
 * @param fp 
 * @param header 
 */
void fwriteHeaderIndex(FILE *fp, header header);

/**
 * @brief lê o cabeçalho de um arquivo
 * 
 * @param fp ponteiro do arquivo a ser lido
 * 
 * @return header cabeçalho lido do arquivo
 */
header readHeaderIndex(FILE *fp);

/**
 * @brief recebe uma struct header como parâmetro e mostra no terminal todos os dados contidos nelas 
 * 
 * @param header struct que guarda o cabeçalho a ser mostrado 
 */
void printHeaderIndex(header header);

#endif