#ifndef __COMMANDS_H__
#define __COMMANDS_H__

#include "main.h"

/**
 * @brief lê entradas digitadas pela linha de comando. realiza tratamento das mesmas, tirando aspas e fazendo configurações iniciais caso alguns campos sejam nulos
 * 
 * @param register_bin registro onde as informações digitas pelo usuário serão armazenadas
 * @return register_bin registro com as informações já armazenadas
 */
register_bin readInput(register_bin register_bin);

/**
 * @brief função insertInto, semalhante àquela utilizada na linguagem de programação para banco de dados: SQL. obs: ver especificações no pdf
 * 
 * @param file_input_data string que contém qual é o arquivo de dados a ser manipulado
 * @param file_input_index string que contém qual é o arquivo index a ser manipulado 
 * @param n quantidade de entradas digitadas pelo usuário
 */
void insertInto(char *file_input_data, char *file_input_index, int n);

#endif