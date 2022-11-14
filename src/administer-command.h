#ifndef __COMMAND_H__
#define __COMMAND_H__

#include "main.h"

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

#endif