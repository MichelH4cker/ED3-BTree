#ifndef __B_TREE_H__
#define __B_TREE_H__

#define M 5 // ordem da árvore-b

#define NODE_SIZE 65


enum RETURN_VALUES{PROMOTION, NO_PROMOTION, ERROR};

typedef struct key {
    int key;
    int RRNkey;
} key_type;

typedef struct node {
    char folha; // 1 se for folha e 0 se não for
    int nroChavesNo; // número de keys do node (n < M). 
    int alturaNo;
    int RRNdoNo; 

    int RRNpointers[M]; // RRN dos filhos
    key_type keys[M - 1]; // array de keys. a chave do nó é o campo idConecta
} node;

typedef struct transitionNode {
    int RRNpointers[M + 1];
    key_type keys[M];
} transitionNode;

#include "main.h"

/**
 * @brief lê o registor e retorna se ele está removido logicamente
 * 
 * @param register_bin struct que contém o registro lido no arquivo de dados 
 * @return int 1 para removido e 0 para não removido
 */
int registerHasBenRemoved(register_bin register_bin);

/**
 * @brief configura toda a struct passada para NIL
 * 
 * @param page struct node que deseja-se apagar 
 */
void deletePage(node *page);

/**
 * @brief procura e retorna a posição onde a chave passada como parâmetro ocorre ou deveria ocorrer
 * 
 * @param key_param chave a ser procurada 
 * @param node nó onde a chave será procurada
 * @return int 
 */
int idealKeyPosition(key_type key_param, node node);

/**
 * @brief cria uma struct nó
 * 
 * @param key chave a ser guardada no nó
 * @param leftChild ponteiro para o filho da esquerda
 * @param rightChild ponteiro para o filho da direita
 * @return node nó com as informações passada como parâmetros 
 */
node createNode(int key, int leftChild, int rightChild);

/**
 * @brief insere a chave na posição correta no nó passada como parâmetro
 * 
 * @param position posição a ser inserida
 * @param key_param chave a ser inserida
 * @param page nó onde os dados serem armazenados
 * @param promo_r_child filho direito da chave a ser inserida 
 */
void insertKey(int position, key_type key_param, node *page, int promo_r_child);

/**
 * @brief split b-tree
 * 
 * @param i_key chave a ser inserida
 * @param i_rrn filho a direita do i_key
 * @param page nó cheio que sofrerá split
 * @param promo_key chave a ser promovida 
 * @param promo_r_child filho direito que será promovido
 * @param newPage novo nó causado pelo split 
 */
void split(key_type i_key, int *i_rrn, node *page, key_type *promo_key, int *promo_r_child, node *newPage);

/**
 * @brief função recursive que insere na árvore. essa função segue o livro de referência da professora Cristina
 * 
 * @param currentRRN 
 * @param key_param 
 * @param promo_r_child 
 * @param promo_key 
 * @param fp_index 
 * @return enum RETURN_VALUES 
 */
enum RETURN_VALUES insert(int *currentRRN, key_type key_param, int *promo_r_child, key_type *promo_key, FILE *fp_index);

/**
 * @brief função recursiva que insere no arquivo index. essa função segue o livro de referência da professora Cristina
 * 
 * @param file_bin ponteiro para o arquivo de dados 
 * @param file_index ponteiro para o arquivo index 
 */
void driver(char *file_bin, char *file_index);

#endif