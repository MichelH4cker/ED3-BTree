#ifndef __COMPACTION_H__
#define __COMPACTION_H__

#include "main.h"
#include "header.h"
#include "createTable.h"

/**
 * retira os registros removidos de um arquivo
 * */
void compaction(FILE *fp, char *fileName, struct filter filter);

#endif