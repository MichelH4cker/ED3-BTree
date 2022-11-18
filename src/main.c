/**
 * @authors Michel Hecker Faria (12609690) && Guilherme Augusto Moreira (SEI LÁ O NUSP DESSE MERDA)
 * @brief responsável por controlar todo o funcionamento do programa,
 * apenas chamando as funções principais e cuidando do input do usuário
 * @return int retorna se o programa funcionou com êxito ou não 
 */
#include "main.h"

void menu(){
    int command;
    char file_input_data[40];
    char file_input_index[40];

    scanf("%d", &command);
    scanf("%s", file_input_data);
    scanf("%s", file_input_index);

    char path_data[] = "arquivos/antes/";

    strcat(path_data, file_input_data);

    switch (command){
    case 7:
        driver(path_data, file_input_index);
        binarioNaTela(file_input_index);
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