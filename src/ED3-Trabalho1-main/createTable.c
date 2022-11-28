// NOME: Michel Hecker Faria | Guilherme Augusto Moreira
// NUSP: 12609690			 | 12547281

#include "createTable.h"

int contBytes = 0;		//contas quantos bytes foram escritos no arquivo .bin

int auxWriteFpBin(FILE *fpBin, char *str) {				//escreve regs variaveis no arquivo binario
	int bytesReg = 0;
	int i = 0;
    char c = str[i];
    while (c != '\0' && c != '|' && i < 21) {				//
		i++;												//
        fwrite(&c, sizeof(char), 1, fpBin);					//escreve char por char no
        c = str[i];											//arquivo .bin
		bytesReg++;		//atualiza os bytes escritos		//
	}														//

	return bytesReg;
}

void writeFpBin(FILE *fpBin, struct reg regis, struct header header) {			//escreve o registro no arquivo binario
	fwrite(&regis.removido, sizeof(char), 1, fpBin);		//1 byte
	fwrite(&regis.encadeamento, sizeof(int), 1, fpBin);		//4 bytes
	fwrite(&regis.idConecta, sizeof(int), 1, fpBin);		//4 bytes
	fwrite(regis.siglaPais, sizeof(char), 2, fpBin);		//2 bytes
	fwrite(&regis.idPoPsConectado, sizeof(int), 1, fpBin);	//4 bytes
	fwrite(&regis.unidadeMedida, sizeof(char), 1, fpBin);	//1 byte
	fwrite(&regis.velocidade, sizeof(int), 1, fpBin);		//4 bytes

	int bytesReg = 0;
	bytesReg += 20;										//atualiza com a parte de tamanho fixo do registro

	char bar = '|';
	bytesReg += auxWriteFpBin(fpBin, regis.nomePoPs);
	fwrite(&bar, sizeof(char), 1, fpBin);
	bytesReg += auxWriteFpBin(fpBin, regis.nomePais);
	fwrite(&bar, sizeof(char), 1, fpBin);

	int trashAmount = REGISTER_TOTAL_SIZE - bytesReg - 2;			//registro total - a parte preenchida e as barras verticais
	char trash = '$';

	for (int i = 0; i < trashAmount; i++)
		fwrite(&trash, sizeof(char), 1, fpBin);
}

void registerVariable(char str[21], FILE *fp) {		//le um campo com tamanho variado
	char c;
	int i = 0;
	
	fread(&c, sizeof(char), 1, fp);
	while (c != ',' && c != '\n' && c != '\0') {		//
		str[i] = c;										//le char por char e armazena ate
		i++;											//chegar numa ',' ou final de string
		fread(&c, sizeof(char), 1, fp);					//
	}													//

	if (str == NULL)									//
		for (int i = 0; i < 21; i++)					//se for vazia, preenche com lixo
			str[i] = '$';								//
	else
		str[i] = '\0';									//coloca marcador no final

	int final = 0;
	while(final < 21 && str[final] != '\0')			//encontra o tamanho da string
		final++;
	
	if (str[0] != ' ' && str[final - 1] != ' ')			//nao tem necessidade de tirar espacos inicial ou final da string
		return;

	if (str[final - 1] == ' ')
		str[final - 1] = '\0';
	if (str[0] == ' ')
		for (int i = 0; i <= final; i++)
			str[i] = str[i + 1];
}

void readFp(FILE *fp, char str[21]) {
	char c;
	str[0] = '$';		//coloca o primeiro caracter como - e 1, dando -1, para saber e ocorreu a leitura ou nao
	int i = 0;
	
	fread(&c, sizeof(char), 1, fp);							//
	while (c != ',' && c != '\n' && c != '\0') {			//
		str[i] = c;											//le char por char do arquivo
		fread(&c, sizeof(char), 1, fp);						//e verifica se e ',' ou nao
		i++;												//
	}														//

	if (str[0] == '$')						//
		for(int i = 0; i < 21; i++)			//se o inicio for 0, 
			str[i] = '$';					//torna a string lida como lixo
}											//

void createTable(FILE *fp) {	//funcao principal para a criacao de uma tabela
    char fileName[50];
	scanf("%s", fileName);
	FILE *fpBin = fopen(fileName, "wb");				//cria o arquivo bin
	if (fpBin == NULL) {
		printf("Falha no processamento do arquivo.\n");
	}

	fseek(fp, 0, SEEK_END);
	long int f_end = ftell(fp);			//armazena a ultima posicao do arquivo a ser lido

	fseek(fp, 79, SEEK_SET);

    struct header header;
	header.status = '0';            //arquivo aberto para escrita       //
    header.topo = -1;                                                   //inicializa os
    header.proxRRN = 0;                                                 //dados de entrada
    header.nroRegRem = 0;                                               //do cabecalho
    header.nroPagDisco = 1;                                             //
    header.qttCompacta = 0;  
	createHeader(fpBin, header);		//chama funcao que cria o cabecalho

	struct reg reg;
	char readForAll[22];		//string que vai ler as entradas do terminal
	int byte = 0;

	while(ftell(fp) < f_end) {			//loop ate chegar na ultima posicao do arquivo
		if (byte == 0)
			header.nroPagDisco++;
		
		readFp(fp, readForAll);										
		reg.idConecta = atoi(readForAll);		//converte a string lida num int
				
		registerVariable(reg.nomePoPs, fp);		//leitura dos campos de
		registerVariable(reg.nomePais, fp);		//tamanho variavel

		strcpy(readForAll, "$$$$$$$$$$$$$$$$$$$$");			//torna a string cheia de lixo para nao alterar as proximas entradas

		readFp(fp, readForAll);										//le o arquivo e retorna uma string
		for(int i = 0; i < 2; i++)
			reg.siglaPais[i] = readForAll[i];						//preenche com os dois primeiros chars lidos
		
		strcpy(readForAll, "$$$$$$$$$$$$$$$$$$$$");		//torna a string cheia de lixo para nao alterar as proximas entradas

		readFp(fp, readForAll);										//le o arquivo e retorna uma string
		reg.idPoPsConectado = atoi(readForAll);					//converte a string lida num inteiro
		if (readForAll[0] == '$')								//se for 0, torna lixo
			reg.idPoPsConectado = -1;								//
		
		strcpy(readForAll, "$$$$$$$$$$$$$$$$$$$$");		//torna a string cheia de lixo para nao alterar as proximas entradas

		readFp(fp, readForAll);										//le o arquivo e retorna uma string
		reg.unidadeMedida = readForAll[0];						//preenche com o primeiro char lido

		strcpy(readForAll, "$$$$$$$$$$$$$$$$$$$$");		//torna a string cheia de lixo para nao alterar as proximas entradas

		readFp(fp, readForAll);										//le o arquivo e retorna uma string
		reg.velocidade = atoi(readForAll);							//converte a string lida num inteiro
		if (readForAll[0] == '$')									//se for 0, torna lixo
			reg.velocidade = -1;									//

		reg.removido = '0';			//torna os campos auxiliares
		reg.encadeamento = -1;		//em entradas padrao

		byte += REGISTER_TOTAL_SIZE;
        if (byte % PAGE_DISC_SIZE == 0)         //atualiza o numero de pag de disco ocupadas
            header.nroPagDisco++;

		strcpy(readForAll, "$$$$$$$$$$$$$$$$$$$$");	//torna a string lixo so para nao prejudicar futuras leituras
		writeFpBin(fpBin, reg, header);				//escreve o reg no .bin
		header.proxRRN++;			//atualiza o prox RRN disponivel
	}
	header.status = '1';			//vai fechar o arquivo
	updateHeader(fpBin, header);		//atualiza o cabecalho

	fclose(fpBin);

	binarioNaTela(fileName);
}