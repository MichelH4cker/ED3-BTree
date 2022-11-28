// NOME: Michel Hecker Faria | Guilherme Augusto Moreira
// NUSP: 12609690	         | 12547281

#include "compaction.h"

void readRegister(FILE *fp, struct reg reg) {           //leitura do registro no arquivo bin
    fread(&reg.removido, sizeof(char), 1, fp);
    fread(&reg.encadeamento, sizeof(int), 1, fp);
    fread(&reg.idConecta, sizeof(int), 1, fp);
    fread(&reg.siglaPais, sizeof(char), 2, fp);
    fread(&reg.idPoPsConectado, sizeof(int), 1, fp);
    fread(&reg.unidadeMedida, sizeof(char), 1, fp);
    fread(&reg.velocidade, sizeof(int), 1, fp);

    registerVariable(reg.nomePoPs, fp);
    registerVariable(reg.nomePais, fp);
}

void readVariableFieldComp(FILE *fp, char *string){
    int i = 0;
    char c;
    fread(&c, sizeof(char), 1, fp);
    while (c != '|' && i < 22){             //leitura ate chegar em uma "|" ou no limite do array
       string[i] = c;
       fread(&c, sizeof(char), 1, fp);
       i++;
    }
    string[i] = '\0';

}

void compaction(FILE *fp, char *fileName, struct filter filter) {
    struct header header;
    header  = returnCurrentHeader(fp, header);
    
    header.status = '0';        //arquivo inconsistente
    header.qttCompacta++;       //aumenta o numero de compactacoes

    FILE *fpComp = fopen("fpComp.bin", "wb");               //cria um arquivo vazio
    if (fpComp == NULL) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    
    createHeader(fpComp, header);               //cria o cabecalho neste arquivo novo

    fseek(fp, 0, SEEK_END);
	long int f_end = ftell(fp);                 //posicao final do arquivo a ser compactado
    fseek(fp, PAGE_DISC_SIZE, SEEK_SET);

    int byte = 0;
    int pagDiscFpComp = 1;
    struct reg reg;
    int fixPoint;
    while(ftell(fp) < f_end) {                      //loop ate chegar na posicao final do arquivo lido
        fread(&reg.removido, sizeof(char), 1, fp);
        if (reg.removido == '1') {          //se for removido, pula o registro
            fseek(fp, REGISTER_TOTAL_SIZE - REMOVIDO_SIZE, SEEK_CUR); // pula reg vazio
            header.proxRRN--;       //desconsidera o registro para o novo arquivo
            header.nroRegRem--;     //
            continue;
        }
            
        fread(&reg.encadeamento, sizeof(int), 1, fp);       //
        fread(&reg.idConecta, sizeof(int), 1, fp);          //
        fread(reg.siglaPais, sizeof(char), 2, fp);          //leitura dos outros 
        fread(&reg.idPoPsConectado, sizeof(int), 1, fp);    //campos do registro
        fread(&reg.unidadeMedida, sizeof(char), 1, fp);     //
        fread(&reg.velocidade, sizeof(int), 1, fp);         //
            
        fixPoint = ftell(fp);       //armazena ate onde foi a parte de tamanho fixo do registro

        readVariableFieldComp(fp, reg.nomePoPs);        //leitura dos
        readVariableFieldComp(fp, reg.nomePais);        //campos variaveis
    
        fseek(fp, fixPoint + 44, SEEK_SET);     //pula todo campo de tamanho variavel junto do lixo

        byte += REGISTER_TOTAL_SIZE;
        if (byte % PAGE_DISC_SIZE == 0)         //atualiza o numero de pag de disco ocupadas
            pagDiscFpComp++;

        writeFpBin(fpComp, reg, header);        //escreve no novo arquivo
    }

    remove(fileName);                   //remove o arquivo velho
    rename("fpComp.bin", fileName);     //renomeia o arquivo novo com o nome do velho
        
    header.topo = -1;                           //
    header.nroPagDisco = 1 + pagDiscFpComp;     //atualiza os campos
    header.status = '1';                        //do cabecalho e armazena no arquivo
    updateHeader(fpComp, header);               //

    fclose(fpComp);
}