#ifndef __DATA_FILE_H__
#define __DATA_FILE_H__

#define REGISTER_BIN_SIZE 64
#define DISK_PAGE_BIN_SIZE 960
#define VARIABLE_FIELD_SIZE 44
#define PIPE_SIZE 1

typedef struct {
	char status;     // 1 btye
	int topo;        // 4 btyes
	int proxRRN;     // 4 bytes
	int nroRegRem;   // 4 bytes
	int nroPagDisco; // 4 bytes
	int qttCompacta; // 4 bytes
	// total: 21
} header_bin;

typedef struct {
	char removido;       // 1 byte		//campos
	int encadeamento;    // 4 bytes		//auxiliares
	
	int idConecta;       // 4 bytes
	char siglaPais[3];   // 2 bytes
	int idPoPsConectado; // 4 bytes
	char unidadeMedida;  // 1 byte
	int velocidade;      // 4 bytes

	char nomePoPs[22];		//campos de tamanho
	char nomePais[22];		//variavel
} register_bin;

#include "main.h"

/**
 * @brief dado um RRN, o ponteiro vai até ele
 * 
 * @param RRN RRN
 * @param fp ponteiro para arquivo
 */
void goToRRNbin(int RRN, FILE *fp);

/**
 * @brief retorna um inteiro que guarda o valor do RRN atual do ponteiro
 * 
 * @param fp ponteiro do arquivo 
 * @return int RRN atual do ponteiro
 */
int returnBinCurrentRRN(FILE *fp);

/**
 * @brief lê arquivo e retorna struct do cabeçalho contendo todos os campos
 * 
 * @param fp ponteiro para arquivo
 * @return header_bin armazena campos do cabeçalho
 */
header_bin readHeaderBin(FILE *fp);

/**
 * @brief
 *
 * @param fp
 * @param header_param
 */
void fwriteHeaderBin(FILE *fp, header_bin header_param);

/**
 * @brief mostra no terminal a struct header_bin. essa função é usada apenas para debug
 * 
 * @param header_bin cabeçalho a ser mostrado no terminal
 */
void printHeaderBin(header_bin header_bin);

/**
 * @brief lê no arquivo os campos de tamanho variável 
 * 
 * @param fp ponteiro para o arquivo
 * @param string string a ser lida 
 */
void readVariableField(FILE *fp, char *string);

/**
 * @brief lê o registro do arquivo
 * 
 * @param fp ponteiro para arquivo
 * @return register_bin armazena o registro
 */
register_bin readRegisterBin(FILE *fp);

/**
 * @brief mostra no terminal a struct register_bin. essa função é usada apenas para debug
 * 
 * @param register_bin registro a ser mostrado no terminal
 */
void printRegisterBin(register_bin register_bin);

#endif