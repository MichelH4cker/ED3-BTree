#ifndef __INDEX_FILE_H__
#define __INDEX_FILE_H__

#define DISK_PAGE_INDEX_SIZE 73
#define HEADER_SIZE 65
#define HEADER_FIELDS_SIZE 17
#define HEADER_GARBAGE_SIZE 48


typedef struct header {
    char status;        // status do arquivo
    int noRaiz;         // RRN do nó raiz
    int nroChavesTotal; // 
    int alturaArvore;   // altura total da árvore
    int RRNproxNo;      // próximo RRN livre para inserção de um novo nó
} header;

#include "main.h"
#include "b-tree.h"

/**
 * @brief Create a Pattern Header Index object para caso não haja registros nenhum
 * 
 * @return header 
 */
header createPatternHeaderIndex();

/**
 * @brief cria um tipo header
 * 
 * @param header header criada
 */
header createHeaderIndex();

/**
 * @brief escreve a struct header passada como parâmetro no arquivo index
 * 
 * @param fp ponteiro para arquivo index
 * @param header struct contendo as informações para novo header
 */
void fwriteHeaderIndex(FILE *fp, header header);

/**
 * @brief lê o cabeçalho de um arquivo
 * 
 * @param fp ponteiro do arquivo a ser lido
 * @return header cabeçalho lido do arquivo
 */
header readHeaderIndex(FILE *fp);

/**
 * @brief recebe uma struct header como parâmetro e mostra no terminal todos os dados contidos nela
 * 
 * @param header struct que guarda o cabeçalho a ser mostrado 
 */
void printHeaderIndex(header header);

/**
 * @brief dado o ponteiro para o arquivo index, essa função retorna o RRN onde ele se encontra
 * 
 * @param fp ponteiro para arquivo index
 * @return int RRN
 */
int returnIndexCurrentRRN(FILE *fp);

/**
 * @brief ponteiro se desloca para o RRN passado no parâmetro 
 * 
 * @param RRN RRN
 * @param fp ponteiro para arquivo index
 */
void goToRRNindex(int RRN, FILE *fp);

/**
 * @brief escreve no arquivo index a struct node passada
 * 
 * @param fp ponteiro para arquivo index
 * @param node struct que guarda todos os valores a serem escritos no arquivo
 */
void fwriteNode(FILE *fp, node node);

/**
 * @brief le um nó/página de disco do arquivo index
 * 
 * @param fp ponteiro para arquivo
 * @return struct node guarda todos os dados lidos
 */
struct node readNode(FILE *fp);

/**
 * @brief mostra no terminal todos os dados da struct transitionNode
 * 
 */
void printBigNode(transitionNode transitionNode);

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
 * @brief função utilizada para debub. mostra o cabeçalho e todas as páginas de discos contidas no arquivo index  
 * 
 * @param fp ponteiro para arquivo index
 */
void showIndexFile(FILE *fp);

#endif