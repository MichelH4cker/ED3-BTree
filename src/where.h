#ifndef __WHERE_H__
#define __WHERE_H__

#include "main.h"
#include "funcoesFornecidas.h"
#include "index_file.h"

/**
 * @brief faz o comando "where"
 * @param fp_index arquivo em que ocorrerá a busca
 * @param fp_data arquivo de dados
*/
void where(FILE *fp_index, FILE *fp_data);

#endif