#ifndef __FUNCOESFORNECIDAS_H__
#define __FUNCOESFORNECIDAS_H__

#include "main.h"

/**
 * @brief le uma string do terminal e passa para a string
 * @param string que receberá a linha escrita no terminal
*/
void readline(char* string);

/**
 * @brief lê um arquivo binario e retorna seu valor inteiro correspondente
 * @param nome do arquivo que sera lido
*/
void binarioNaTela(char *nomeArquivoBinario);

/**
 * @brief le uma linha do terminal e retira as " caso tenha, ou entao le como um inteiro, caso seja
 * @param string que armazenara os dados lidos 
*/
void scan_quote_string(char *str);

#endif