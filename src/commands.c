/**
 * @file commands.c
 * @author guilherme augusto moreira (12547281)
 * @author Michel Hecker Faria (12609690)
 * @brief funções necessárias para execução dos comandos solicitados para desenvolvimento
 * @version 0.1
 * @date 2022-11-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */
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

void insertInto(char *file_input_data, char *file_input_index, int n){
    // ABRE ARQUIVO
    FILE *fp_data = fopen(file_input_data, "rb+");
    if(fp_data == NULL){
        printf("Erro no processamento do arquivo!\n");
        return;
    } 
    
	// LÊ HEADER DO ARQUIVO DE DADOS
    header_bin header_var = readHeaderBin(fp_data);
    header_var.status = '0';
    fwriteHeaderBin(fp_data, header_var);

	// PREPARA E LÊ NOVOS REGISTROS
    register_bin array_reg_bin[n];
    for (int i = 0; i < n; i++){
        array_reg_bin[i].removido = '0';
        array_reg_bin[i].encadeamento = -1;
        array_reg_bin[i] = readInput(array_reg_bin[i]);
    }


    // INSERÇÃO NO ARQUIVO DE DADOS
    for (int i = 0; i < n; i++) {
		if (header_var.topo == -1) {
			goToRRNbin(header_var.proxRRN, fp_data);
			header_var.proxRRN++;
		} else {
            searchRegisterBinRemoved(fp_data, &header_var);
			header_var.nroRegRem--;
		}

        fwriteRegisterBin(fp_data, array_reg_bin[i]);
	}

    // ATUALIZAÇÃO DO HEADER
    header_var.status = '1';
    fwriteHeaderBin(fp_data, header_var);

	fclose(fp_data);

	// CRIAÇÃO DO INDEX
	driver(file_input_data, file_input_index);
}