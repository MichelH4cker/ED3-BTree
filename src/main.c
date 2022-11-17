/**
 * @authors Michel Hecker Faria (12609690) && Guilherme Augusto Moreira (SEI LÁ O NUSP DESSE MERDA)
 * @brief responsável por controlar todo o funcionamento do programa,
 * apenas chamando as funções principais e cuidando do input do usuário
 * @return int retorna se o programa funcionou com êxito ou não 
 */
#include "main.h"

void readCommand(int *command_key, char *file_input_0, char *file_input_1){
    scanf("%d", &(*command_key));
    scanf("%s", file_input_0);
    scanf("%s", file_input_1);

    //printf("os comandos lidos foram: %d --- %s --- %s \n", command_key, file_input_0, file_input_1);
}

void menu(){
    int command;
    char file_input_0[20];
    char file_input_1[20];

    readCommand(&command, file_input_0, file_input_1);

    FILE* fp_0, fp_1; 
    
    switch (command){
    case 7:
        fp_0 = fopen(file_input_0, "r");
        header header = readHeaderIndex(fp_0);
        printHeaderIndex(header);
        fclose(fp_0);
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

int main (){
    menu();
    return 0;
}
