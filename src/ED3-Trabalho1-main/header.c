// NOME: Michel Hecker Faria | Guilherme Augusto Moreira
// NUSP: 12609690			 | 12547281

#include "header.h"

struct header returnCurrentHeader(FILE *fp, struct header current_header){
    fseek(fp, 0, SEEK_SET); // vai para começo do arquivo
    
    fread(&current_header.status, sizeof(current_header.status), 1, fp);                //
    fread(&current_header.topo, sizeof(current_header.topo), 1, fp);                    //
    fread(&current_header.proxRRN, sizeof(current_header.proxRRN), 1, fp);              //leitura dos campos
    fread(&current_header.nroRegRem, sizeof(current_header.nroRegRem), 1, fp);          //do cabecalho do arquivo
    fread(&current_header.nroPagDisco, sizeof(current_header.nroPagDisco), 1, fp);      //
    fread(&current_header.qttCompacta, sizeof(current_header.qttCompacta), 1, fp);      //

    return current_header;
}

void updateHeader(FILE *fp, struct header header) {		//atualiza o cabecalho
	fseek(fp, 0, SEEK_SET);         //coloca o ponteiro no inicio do arquivo
    fwrite(&header.status, sizeof(char), 1, fp);            //
    fwrite(&header.topo, sizeof(int), 1, fp);               //
    fwrite(&header.proxRRN, sizeof(int), 1, fp);            //escreve no arquivo
    fwrite(&header.nroRegRem, sizeof(int), 1, fp);          //os dados do cabecalho
    fwrite(&header.nroPagDisco, sizeof(int), 1, fp);        //
    fwrite(&header.qttCompacta, sizeof(int), 1, fp);        //
}

void createHeader(FILE *fp, struct header header) {		//cria o arquivo cabecalho
	header.status = '0';            //arquivo aberto para escrita       //
    header.topo = -1;                                                   //inicializa os
    header.proxRRN = 0;                                                 //dados de entrada
    header.nroRegRem = 0;                                               //do cabecalho
    header.nroPagDisco = 0;                                             //
    header.qttCompacta = 0;                                             //

	fseek(fp, 0, SEEK_SET);			//coloca o ponteiro no inicio do arquivo
	fwrite(&header.status, sizeof(char), 1, fp);			//
	fwrite(&header.topo, sizeof(int), 1, fp);				//
	fwrite(&header.proxRRN, sizeof(int), 1, fp);			//escreve no arquivo
	fwrite(&header.nroRegRem, sizeof(int), 1, fp);			//os dados do cabecalho
	fwrite(&header.nroPagDisco, sizeof(int), 1, fp);		//
	fwrite(&header.qttCompacta, sizeof(int), 1, fp);		//

	//printf("O CABECALHO: %c %d %d %d %d %d\n", header.status, header.topo, header.proxRRN, header.nroRegRem, header.nroPagDisco, header.qttCompacta);

	char trash = '$';										//
	for(int i = 0; i < PAGE_DISC_SIZE - HEADER_SIZE - 1; i++)				//preenche o resto da pagina com lixo
		fwrite(&trash, sizeof(char), 1, fp);				//
}