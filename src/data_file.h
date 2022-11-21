#ifndef __DATA_FILE_H__
#define __DATA_FILE_H__

#define REGISTER_BIN_SIZE 64
#define DISK_PAGE_BIN_SIZE 960
#define VARIABLE_FIELD_SIZE 44
#define PIPE_SIZE 1

#include "main.h"

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
	char siglaPais[2];   // 2 bytes
	int idPoPsConectado; // 4 bytes
	char unidadeMedida;  // 1 byte
	int velocidade;      // 4 bytes

	char nomePoPs[22];		//campos de tamanho
	char nomePais[22];		//variavel
} register_bin;


header_bin readHeaderBin(FILE *fp);

void readvariableField(FILE *fp, char *string);

register_bin readRegisterBin(FILE *fp);

#endif