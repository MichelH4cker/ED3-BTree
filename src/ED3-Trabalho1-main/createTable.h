#ifndef __CREATETABLE_H__
#define __CREATETABLE_H__

#include "main.h"

/**
 * @brief Escreve no arquivo binario um registro e atualiza a struct de cabecalho
 * 
 * @param fpBin
 * @param regis
 * @param header
 */
void writeFpBin(FILE *fpBin, struct reg regis, struct header header);

/**
 *  @brief Leitura de um campo de tamanho variavel do registro
 * 
 *  @param str
 *  @param fp
 */
void registerVariable(char str[22], FILE *fp);

/**
 * @brief Create a Table object
 * 
 * @param fp 
 */
void createTable(FILE *fp);

#endif
