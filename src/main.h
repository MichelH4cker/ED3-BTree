#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdio.h>

#include "b-tree.h"
#include "index_file.h"
#include "data_file.h"


// SIZE
#define DISK_PAGE_SIZE 72;
#define REGISTER_SIZE 65;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


/**
 * @brief lê os inputs digitados pelo usuário
 * @param command_key inteiro que representa a funcionalidade desejada
 * @param file_input_0 primeiro arquivo do input
 * @param file_input_1 segundo arquivo do input
 */
void readCommand(int *command_key, char *file_input_0, char *file_input_1);

/**
 * @brief roda a funcionalidade desejada pelo usuário
 */
void runCommand();

struct filter {
    int  type; //tipo de dado
    int  field_key; // inteiro que refere-se ao comando
    int  number;
    char string[22];
};


#endif