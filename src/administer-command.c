#include "administer-command.h"

void readCommand(int *command_key, char *file_input_0, char *file_input_1){
    scanf("%d", &(*command_key));
    scanf("%s", file_input_0);
    scanf("%s", file_input_1);

    //printf("os comandos lidos foram: %d --- %s --- %s \n", command_key, file_input_0, file_input_1);
}

void runCommand(){
    int command;
    char file_input_0[20];
    char file_input_1[20];

    readCommand(&command, file_input_0, file_input_1);

    FILE* fp; 
    
    switch (command){
    case 7:
        fp = fopen(file_input_0, "r");
        header header = readHeader(fp);
        printHeader(header);
        fclose(fp);
        break;
    case 8:
        break;
    case 9:

        break;
    case 10:
        break;
    default:
        printf("Comando inválido!\n");
        break;
    }
}