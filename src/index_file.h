#ifndef __INDEX_FILE_H__
#define __INDEX_FILE_H__

struct node;

#define DISK_PAGE_INDEX_SIZE 73
#define HEADER_SIZE 65
#define HEADER_FIELDS_SIZE 17
#define HEADER_GARBAGE_SIZE 48

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

/**
 * @brief escreve no arquivo index a struct node passada
 * 
 * @param fp ponteiro para arquivo index
 * @param node struct que guarda todos os valores a serem escritos no arquivo
 */
void fwriteNode(FILE *fp, struct node node);

/**
 * @brief le um nó / página de disco do arquivo index
 * 
 * @param fp ponteiro para arquivo
 * @return struct node guarda todos os dados lidos
 */
struct node readNode(FILE *fp);

/**
 * @brief mostra todos os dados de uma struct node
 * 
 * @param node struct node contendo todos os dados
 */
void printNode(struct node node);

/**
 * @brief checa posição do ponteiro e retorna qual RRN do arquivo ele se encontra
 * 
 * @param fp ponteiro do arquivo
 * @return int RRN do ponteiro
 */
int returnIndexCurrentRRN(FILE *fp);

/**
 * @brief leva o ponteiro do arquivo para o RRN desejado
 * 
 * @param RRN RRN desejado
 * @param fp pontiero do arquivo 
 */
void goToRRN(int RRN, FILE *fp);


#endif