// NOME: Michel Hecker Faria | Guilherme Augusto Moreira
// NUSP: 12609690	         | 12547281

#include "insertInto.h"

void searchDeleted (FILE *fp, struct header *header) {
    int proxRem = header->topo;
    int posFile = REGISTER_TOTAL_SIZE * proxRem + PAGE_DISC_SIZE;	//posicao onde o resgitro no arquivo
    fseek(fp, posFile, SEEK_SET);
    char c;
    fread(&c, sizeof(char), 1, fp);
    fread(&header->topo, sizeof(int), 1, fp);	//atualiza o topo para o proximo registro removido disponivel
    fseek(fp, ftell(fp) - 5, SEEK_SET);
}

struct reg readInput(struct reg reg) {
	struct reg_str {					//
		char siglaPais[4];				//
		char idPoPsConectado[4];		//struct com campos strings
		char unidadeMedida[4];			//para leitura correta da entrada
		char velocidade[4];				//
	};									//

    struct reg_str reg_str;

	scanf("%d", &reg.idConecta);					//
													//
	scan_quote_string(reg.nomePoPs);				//
	scan_quote_string(reg.nomePais);				//leitura das
													//entradas
	scan_quote_string(reg_str.siglaPais);			//
	scan_quote_string(reg_str.idPoPsConectado);		//
	scan_quote_string(reg_str.unidadeMedida);		//
	scanf("%s\n", reg_str.velocidade);				//
	
	if (strcmp(reg.nomePoPs, "NULO") == 0)			//converte entradas "NULO" para lixo
		for (int i = 0; i < 22; i++)
			reg.nomePoPs[i] = '$';
	if (strcmp(reg.nomePais, "NULO") == 0)			//converte entradas "NULO" para lixo
		for (int i = 0; i < 22; i++)
			reg.nomePais[i] = '$';
	
	if (strcmp(reg_str.siglaPais, "NULO") == 0)		//converte entradas "NULO" para lixo
		strcpy(reg.siglaPais, "$$");
	else {
		reg.siglaPais[0] = reg_str.siglaPais[0];
		reg.siglaPais[1] = reg_str.siglaPais[1];
	}
	if (strcmp(reg_str.idPoPsConectado, "NULO") == 0)			//converte entradas "NULO" para lixo
		reg.idPoPsConectado = -1;
	else
		reg.idPoPsConectado = atoi(reg_str.idPoPsConectado);	//transforma a entrada string em int
	if (strcmp(reg_str.unidadeMedida, "NULO") == 0)				//converte entradas "NULO" para lixo
		reg.unidadeMedida = '$';
	else
		reg.unidadeMedida = reg_str.unidadeMedida[0];
	if (strcmp(reg_str.velocidade, "NULO") == 0)				//converte entradas "NULO" para lixo
		reg.velocidade = -1;
	else 
		reg.velocidade = atoi(reg_str.velocidade);				//transforma a entrada string em int
	
	return reg;
}

void insertInto(FILE *fp, char *fileName) {
	int numInserts;
	scanf("%d\n", &numInserts);				//leitura do numero de insercoes
	
	struct header header;
	header = returnCurrentHeader(fp, header);		//
	header.status = '0';							//leitura e atualizacao do cabecalho, esta inconsistente
	updateHeader(fp, header);						//

	struct reg array_reg[numInserts];			//array com os registros a serem inseridos
    for (int i = 0; i < numInserts; i++)	{
        array_reg[i] = readInput(array_reg[i]);		//
		array_reg[i].removido = '0';				//leitura dos registros armazenados no array
		array_reg[i].encadeamento = -1;				//
	}
	for (int i = 0; i < numInserts; i++) {
		
		if (header.topo == -1) {					//insercao com nenhum registro removido
			fseek(fp, 0, SEEK_END);					//insere no final do arquivo
			header.proxRRN++;						//atualiza o prox RRN disponivel
		}
        else {
            searchDeleted(fp, &header);				//insercao no lugar de algum registro removido
			header.nroRegRem--;						//atuailiza o numero de registros removidos
		}
        writeFpBin(fp, array_reg[i], header);
	}

	header.status = '1';			//arquivo consistente novamente
	updateHeader(fp, header);		//atualiza cabecalho
}