#ifndef __DATA_FILE_H__
#define __DATA_FILE_H__

#define REGISTER_BIN_SIZE 64
#define DISK_PAGE_BIN_SIZE 960
#define FIX_FIELD_SIZE 20
#define VARIABLE_FIELD_SIZE 22
#define PIPE_SIZE 1

typedef struct
{
	char status;	 // 1 btye
	int topo;		 // 4 btyes
	int proxRRN;	 // 4 bytes
	int nroRegRem;	 // 4 bytes
	int nroPagDisco; // 4 bytes
	int qttCompacta; // 4 bytes
					 // total: 21
} header_bin;

typedef struct
{
	char removido;	  // 1 byte		//campos
	int encadeamento; // 4 bytes		//auxiliares

	int idConecta;		 // 4 bytes
	char siglaPais[3];	 // 2 bytes
	int idPoPsConectado; // 4 bytes
	char unidadeMedida;	 // 1 byte
	int velocidade;		 // 4 bytes

	char nomePoPs[22]; // campos de tamanho
	char nomePais[22]; // variavel
} register_bin;

#include "main.h"

/**
 * @brief lê o registro e retorna se ele está removido logicamente
 * 
 * @param register_bin struct que contém o registro lido no arquivo de dados 
 * @return int 1 para removido e 0 para não removido
 */
int registerHasBenRemoved(register_bin register_bin);

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
 * @brief escreve no arquivo de dados o header passado como parâmetro
 *
 * @param fp ponteiro para arquivo de dados
 * @param header_param header contendo as novas informações a serem escritas
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
 * @brief lê o registro do arquivo de dados
 *
 * @param fp ponteiro para arquivo
 * @return register_bin armazena o registro
 */
register_bin readRegisterBin(FILE *fp);

/**
 * @brief escreve os campos de tamanho variável no arquivo de dados
 *
 * @param fp ponteiro para o arquivo de dados
 * @param string campo de tamanho variável
 * @return int número de bytes escritos 
 */
void fwriteVariableField(FILE *fp, char *string);

/**
 * @brief escreve um registro no arquivo de dados
 *
 * @param fp ponteiro para o arquivo de dados
 * @param register_bin registro a ser escrito no arquivo de dados
 */
void fwriteRegisterBin(FILE *fp, register_bin register_bin);

/**
 * @brief mostra no terminal a struct register_bin. essa função é usada apenas para debug
 *
 * @param register_bin registro a ser mostrado no terminal
 */
void printRegisterBin(register_bin register_bin);

/**
 * @brief vai até o RRN do registro removido armazenado no cabeçalho
 *
 * @param fp ponteiro para arquivo de dados
 * @param header cabeçalho do arquivo de dados, utilizado para coleta de informações
 */
void searchRegisterBinRemoved(FILE *fp, header_bin *header_param);

/**
 * @brief mostra no terminal o cabeçalho e todos os registro contidos no arquivo de dados. essa função é utilizada somente para debug, não sendo necessária para o desempenho dos comandos solicitados
 *
 * @param fp ponteiro para o arquivo de dados
 */
void showBinFile(FILE *fp);

#endif
