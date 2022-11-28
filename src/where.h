#ifndef __WHERE_H__
#define __WHERE_H__

#include "main.h"
#include "funcoesFornecidas.h"
#include "index_file.h"

typedef struct target {
    int key;
    int found_rrn;
    int found_pos;

    char field_in[20];
    char str_in[20];
} target;

struct filter {
	int  type; //tipo de dado
	int  field_key; // inteiro que refere-se ao comando
	int  number;
	char string[22];
};

/**
 * 
*/
int search(register_bin reg, struct filter *filter);

/**
 * 
*/
void printTerminal(register_bin reg);

/**
 * @brief faz o comando "where"
 * @param fp_index arquivo em que ocorrerá a busca
 * @param fp_data arquivo de dados
*/
void where(char *fp_index, char *fp_data);

#endif