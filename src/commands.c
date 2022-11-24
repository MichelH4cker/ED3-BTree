#include "commands.h"

register_bin readInput(register_bin register_bin) {
    char TRASH = '$';

    char siglaPais[4];
    char idPoPsConectado[4];
    char unidadeMedida[4];
    char velocidade[4];

    // LẼ ENTRADAS
	scanf("%d", &register_bin.idConecta);				
	scan_quote_string(register_bin.nomePoPs);				
	scan_quote_string(register_bin.nomePais);			
	scan_quote_string(siglaPais);			
	scan_quote_string(idPoPsConectado);
	scan_quote_string(unidadeMedida);		
	scanf("%s\n", velocidade);
    
    // COMPLETA COM LIXO SE O CAMPO É NULO CASO CONTRÁRIO GUARDA O INPUT DIGITADO NO REGISTRO
  	if (strcmp(register_bin.nomePoPs, "NULO") == 0){
		for (int i = 0; i < VARIABLE_FIELD_SIZE; register_bin.nomePoPs[i] = TRASH, i++);
    }

	if (strcmp(register_bin.nomePais, "NULO") == 0){
		for (int i = 0; i < VARIABLE_FIELD_SIZE; register_bin.nomePais[i] = TRASH, i++);
    }
	
	if (strcmp(register_bin.siglaPais, "NULO") == 0){
		strcpy(register_bin.siglaPais, "$$");
    } else {
		register_bin.siglaPais[0] = siglaPais[0];
		register_bin.siglaPais[1] = siglaPais[1];
	}

	if (strcmp(idPoPsConectado, "NULO") == 0) {
		register_bin.idPoPsConectado = -1;
    } else {
		register_bin.idPoPsConectado = atoi(idPoPsConectado);
    }

	if (strcmp(unidadeMedida, "NULO") == 0){
		register_bin.unidadeMedida = TRASH;
    } else {
		register_bin.unidadeMedida = unidadeMedida[0];
    }

	if (strcmp(velocidade, "NULO") == 0){
		register_bin.velocidade = -1;
    } else {
		register_bin.velocidade = atoi(velocidade);
    } 

	return register_bin;
}

