#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdio.h>

#include "b-tree.h"
#include "index_file.h"
#include "data_file.h"
#include "where.h"


// SIZE
#define DISK_PAGE_SIZE 72;
#define REGISTER_SIZE 65;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include "data_file.h"
#include "b-tree.h"
#include "index_file.h"
#include "funcoesFornecidas.h"
#include "commands.h"
#include "where.h"

/*
// SIZE
#define HEADER_SIZE 20


#define STATUS_SIZE 1
#define PROX_RRN_SIZE 4
#define REMOVIDO_SIZE 1
#define ENCADEAMENTO_SIZE 4
#define FIX_FIELD_SIZE 20
#define VARIABLE_FIELD_SIZE 44
#define PIPE_SIZE 1

#define VIRGULA_SIZE 44		//valor da VIRGULA_SIZE equivalente a inteiro
*/
#define REGISTER_TOTAL_SIZE 64
#define PAGE_DISC_SIZE 960
#define POS_PAG_DISCO_SIZE 13

// FIELDS KEYS
#define ID_CONECTA 0
#define SIGLA_PAIS 1
#define ID_POPS_CONECTADO 2
#define UNIDADE_MEDIDA 3
#define VELOCIDADE 4
#define NOME_POPS 5
#define NOME_PAIS 6

#define DEBUG -1

void menu();

struct reg {
	char removido;     // 1 byte		//campos
	int encadeamento;  // 4 bytes		//auxiliares
	
	int idConecta;          // 4 bytes
	char siglaPais[3];      // 2 bytes
	int idPoPsConectado;    // 4 bytes
	char unidadeMedida;     // 1 byte
	int velocidade;         // 4 bytes

	char nomePoPs[22];		//campos de tamanho
	char nomePais[22];		//variavel
};


#endif