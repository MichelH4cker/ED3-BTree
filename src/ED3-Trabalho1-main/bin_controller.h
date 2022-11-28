#ifndef __BIN_CONTROLLER_H__
#define __BIN_CONTROLLER_H__

#include "main.h"

void readVariableField(FILE *fp, char *string);

int search(struct reg reg, struct filter *filter);

void readFile(FILE *fp, int command, struct filter *filter, int n);

#endif
