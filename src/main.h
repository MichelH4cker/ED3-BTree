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


//PARTE DO TRABALHO 1 PARA UTILIZAR O COMANDO 3


#define CREATE  1
#define SELECT  2
#define WHERE   3
#define DELETE  4

#define CHAR 0
#define INTEGER 1


#endif