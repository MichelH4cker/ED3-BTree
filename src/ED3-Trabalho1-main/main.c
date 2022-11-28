// NOME: Michel Hecker Faria | Guilherme Augusto Moreira
// NUSP: 12609690			 | 12547281

#include "main.h"

int main(int arg, char *argv[]) {
	int command;
	char fileName[50];
	scanf("%d %s", &command, fileName);
	
	if (fileName == NULL)	{
		printf("Falha no processamento do arquivo.\n");
		return 1;
	}

	readCommand(command, fileName);

	return 0;
}