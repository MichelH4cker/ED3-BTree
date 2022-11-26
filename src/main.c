/**
 * @authors Michel Hecker Faria (12609690) && Guilherme Augusto Moreira (12547281)
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

    // LOCAL
    char path_data[] = "arquivos/antes/";
    strcat(path_data, file_input_data);

    FILE *fp;
    int n;
    switch (command){
    case 7:
        // RUN CODES
        //driver(file_input_data, file_input_index);
        
        // LOCAL
        driver(path_data, file_input_index);

        binarioNaTela(file_input_index);
        break;
    case 8:
        where(path_data, file_input_index);
        break;
    case 9:
        scanf("%d", &n);
        // RUN CODES
        insertInto(file_input_data, file_input_index, n);
        binarioNaTela(file_input_data);
        binarioNaTela(file_input_index);
        
        // LOCAL
        //insertInto(path_data, file_input_index, n);
        //binarioNaTela(path_data);
        //binarioNaTela(file_input_index);
        break;
    case 10:
        break;
    case DEBUG:
        // LOCAL
        //fp = fopen(path_data, "rb+");
        //showBinFile(fp);
        //fclose(fp);
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
