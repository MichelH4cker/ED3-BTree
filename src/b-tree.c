/**
 * @file b-tree.c
 * @author michel hecker faria (12609690)
 * @brief arquivo responsável por sintetizar todas as funções necessárias para o funcionamento da estrutura de dados entitulada de árvore-b. 
 * a ordem da árvore é de 5. 
 * @version 0.1
 * @date 2022-11-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "b-tree.h"

void deletePage(node *page){
    for (int i = 0; i < M - 1; page->keys[i].key = -1, page->keys[i].RRNkey = -1, i++);

    for (int i = 0; i < M; page->RRNpointers[i] = -1, i++);    
}

int idealKeyPosition(key_type key_param, node node){
    int position = M - 1;
    int key = key_param.key;
    for (int i = 0; i < M - 1; i++){
        if (key < node.keys[i].key || node.keys[i].key == -1){
            position = i;
            break;
        }
    }
    return position;
}

node createNode(int key, int leftChild, int rightChild){
    node node;
    for (int i = 0; i < M - 1; node.keys[i].key = -1, node.keys[i].RRNkey = -1, i++);
    for (int i = 0; i < M; node.RRNpointers[i] = -1, i++);

    node.folha = '1';
    node.nroChavesNo = 1;
    node.alturaNo = 1;
    node.RRNdoNo = -1;
    node.keys[0].key = key;
    node.RRNpointers[0] = leftChild;
    node.RRNpointers[1] = rightChild;

    return node;
}

void insertKey(int position, key_type key_param, node *page, int promo_r_child){
    for (int i = M - 2; i >= position; i--){
        if (i != position) page->RRNpointers[i + 1] = page->RRNpointers[i];

        if (i != M - 2) page->keys[i + 1] = page->keys[i];
    }
    
    page->keys[position] = key_param;
    page->RRNpointers[position + 1] = promo_r_child;
    page->nroChavesNo += 1;
}

void split(key_type i_key, int *i_rrn, node *page, key_type *promo_key, int *promo_r_child, node *newPage){
    struct transitionNode bigNode;

    // COPIA CHAVES PARA BIG NODE
    for (int i = 0; i < M - 1; i++){
        bigNode.keys[i] = page->keys[i];
    }

    // COPIA POINTERS PARA BIG NODE
    for (int i = 0; i < M; i++){
        bigNode.RRNpointers[i] = page->RRNpointers[i];
    }

    // INSERE I_KEY E I_RRN NO BIG NODE
    bigNode.keys[M - 1] = i_key;
    bigNode.RRNpointers[M] = *i_rrn;

    // ENCONTRA A POSIÇÃO
    int position = M - 1;
    for (int i = 0; i < M; i++){
        if (i_key.key < bigNode.keys[i].key || bigNode.keys[i].key == -1){
            position = i;
            break;
        }
    }

    // SHIFT (ordenar)
    for (int i = M - 1; i >= position; i--){
        if (i != position){
            bigNode.RRNpointers[i + 1] = page->RRNpointers[i];
        }

        if (i != M - 1){
            bigNode.keys[i + 1] = page->keys[i];
        }
    }
    
    // INSERE I_KEY E I_RRN NO LOCAL APROPRIADO
    bigNode.keys[position] = i_key;
    bigNode.RRNpointers[position + 1] = *i_rrn;

    int middleKeyPosition = 2;

    // SETA PROMO_KEY AND PROMO_R_CHILD
    *promo_key = bigNode.keys[middleKeyPosition];
    *promo_r_child = newPage->RRNdoNo;

    // SETA PAGE
    deletePage(&(*page));
    for (int i = 0; i < middleKeyPosition; i++){
        page->keys[i] = bigNode.keys[i];
        page->RRNpointers[i] = bigNode.RRNpointers[i];
    }
    page->RRNpointers[middleKeyPosition] = bigNode.RRNpointers[middleKeyPosition];

    // SETA NEWPAGE
    for (int i = 0; i < middleKeyPosition; i++){
        newPage->keys[i] = bigNode.keys[i + 1 + middleKeyPosition];
        newPage->RRNpointers[i] = bigNode.RRNpointers[i + 1 + middleKeyPosition];
    }
    newPage->RRNpointers[middleKeyPosition] = bigNode.RRNpointers[M];

    // AUMENTA NÚMERO DE CHAVES
    page->nroChavesNo = 2;
    newPage->nroChavesNo = 2;
}

enum RETURN_VALUES insert(int *currentRRN, key_type key_param, int *promo_r_child, key_type *promo_key, FILE *fp_index){
    int p_b_rrn;
    key_type p_b_key;
    if (*currentRRN == -1){ // RRN INEXISTENTE, VOLTA 1 ANDAR DA RECURSÃO 
        *promo_key = key_param;
        *promo_r_child = -1;
        return PROMOTION;
    } else { //  NÃO É UMA FOLHA => RECURSÃO ATÉ SER FOLHA
        // LÊ O NÓ ATUAL E VERIFICA A POSIÇÃO ONDE A CHAVE OCORRE OU DEVERIA OCORRER
        goToRRNindex(*currentRRN, fp_index);
        node page = readNode(fp_index);
        int position = idealKeyPosition(key_param, page);

        // VERIFICA SE EXISTE CHAVE REPETIDA 
        // (esse caso, com as especificações do trabalho, nunca ocorre. no entanto, como no livro utilizado como referência o autor faz essa verificação, achei interessante fazer mesmo assim)
        if (key_param.key == page.keys[position].key) return ERROR;

        // CHAMADA RECURSIVA
        int RETURN_VALUE = insert(&page.RRNpointers[position], key_param, &(p_b_rrn), &(p_b_key), fp_index);

        // NÃO HÁ PROMOÇÃO E NEM É ERRO => PROGRAMA SÓ VAI SUBINDO OS ANDARES DA RECURSÃO
        if (RETURN_VALUE == NO_PROMOTION || RETURN_VALUE == ERROR){
            return RETURN_VALUE;
        } else if (page.nroChavesNo < M - 1){ // EXISTE ESPAÇO NO NÓ => INSERIR
            // INSERE CHAVE E ESCREVE NO ARQUIVO
            insertKey(position, p_b_key, &page, p_b_rrn);
            goToRRNindex(*currentRRN, fp_index);
            fwriteNode(fp_index, page);

            // ATUALIZA HEADER
            header new_header = readHeaderIndex(fp_index);
            new_header.nroChavesTotal += 1;
            fwriteHeaderIndex(fp_index, new_header);

            return NO_PROMOTION;
        } else { // NÃO EXISTE ESPAÇO PARA INSERÇÃO => SPLIT
            // LÊ HEADER
            header newHeader = readHeaderIndex(fp_index);
            
            // CONFIGURA NEW NODE 
            node newNode = createNode(-1, -1, -1);  
            newNode.RRNdoNo = newHeader.RRNproxNo;
            newNode.alturaNo = page.alturaNo;
            newNode.folha = page.folha;
            
            // ATUALIZA HEADER
            newHeader.RRNproxNo += 1;
            fwriteHeaderIndex(fp_index, newHeader);

            // SPLIT    
            split(p_b_key, &p_b_rrn, &page, &(*promo_key), &(*promo_r_child), &newNode);

            // ESCREVE NÓS NO ARQUIVO
            goToRRNindex(*currentRRN, fp_index);
            fwriteNode(fp_index, page);
            goToRRNindex(newNode.RRNdoNo, fp_index);
            fwriteNode(fp_index, newNode);

            return PROMOTION;
        } 
    }
}

void driver(char *file_bin, char *file_index){
    key_type myKey;
    register_bin register_bin;
    
    // ABRE ARQUIVOS
    FILE *fp_data = fopen(file_bin, "rb+");
    if(fp_data == NULL){
        printf("Erro no processamento do arquivo!\n");
        return;
    } 

    FILE *fp_index = fopen(file_index, "wb+");
    if(fp_index == NULL) {
        printf("Erro no processamento do arquivo!\n");
        return;
    }

    // CRIA HEADER COM CONFIGURAÇÕES INICIAIS
    header headerIndex = createHeaderIndex();
    fwriteHeaderIndex(fp_index, headerIndex);

    // LIMITE DE LEITURA DO ARQUIVO DE DADOS
    header_bin header_bin = readHeaderBin(fp_data);
    int RRNlimit = header_bin.proxRRN;

    // CONFIGURAÇÃO INICIAL DA PRIMEIRA ROOT
    // pula para o primeiro registro
    fseek(fp_data, DISK_PAGE_BIN_SIZE, SEEK_SET); 
    register_bin = readRegisterBin(fp_data);
    myKey.RRNkey = 0;
    myKey.key = register_bin.idConecta;

    node root = createNode(myKey.key, -1, -1);
    root.RRNdoNo = 0;
    root.keys[0].RRNkey = myKey.RRNkey;

    fwriteNode(fp_index, root);

    int currentRRN = 1;
    while (currentRRN < RRNlimit){
        // LÊ NO ARQUIVO DE DADOS A CHAVE E O RRN DELA
        goToRRNbin(currentRRN, fp_data);
        myKey.RRNkey = currentRRN;
        register_bin = readRegisterBin(fp_data);
        myKey.key = register_bin.idConecta;

        // REGISTRO REMOVIDO => PRÓXIMA ITERAÇÃO
        if (registerHasBenRemoved(register_bin)){
            currentRRN++;
            continue;
        } 

        key_type promo_key;
        int promo_r_child;
        if (insert(&root.RRNdoNo, myKey, &promo_r_child, &promo_key, fp_index) == PROMOTION){
            // LÊ O HEADER
            header newHeader = readHeaderIndex(fp_index);
            
            // CRIA NOVA ROOT
            node new_root = createNode(promo_key.key, root.RRNdoNo, promo_r_child);  
            new_root.keys[0].RRNkey = promo_key.RRNkey;
            new_root.RRNdoNo = newHeader.RRNproxNo;
            new_root.folha = '0';
            new_root.alturaNo = root.alturaNo + 1;

            // ESCREVE NO ARQUIVO A NOVA ROOT
            root = new_root;
            goToRRNindex(newHeader.RRNproxNo, fp_index);
            fwriteNode(fp_index, root);

            // ATUALIZA HEADER
            newHeader.alturaArvore += 1;
            newHeader.nroChavesTotal += 1;
            newHeader.RRNproxNo += 1;
            newHeader.noRaiz = root.RRNdoNo;
            fwriteHeaderIndex(fp_index, newHeader);
        }

        currentRRN++;
    }
    // CONFIGURAÇÃO FINAL DO HEADER
    header newHeader = readHeaderIndex(fp_index);
    newHeader.status = '1';
    fwriteHeaderIndex(fp_index, newHeader);
    
    // FECHA OS DOIS ARQUIVOS
    fclose(fp_data);
    fclose(fp_index);
}