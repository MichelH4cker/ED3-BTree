#include "main.h"

/**
 * @authors Michel Hecker Faria (12609690) && Guilherme Augusto Moreira (SEI LÁ O NUSP DESSE MERDA)
 * @brief responsável por controlar todo o funcionamento do programa,
 * apenas chamando as funções principais e cuidando do input do usuário
 * @return int retorna se o programa funcionou com êxito ou não 
 */
int main (){
    int commandKey;
    scanf("%d", &commandKey);

    readCommand(commandKey);

    return 0;
}