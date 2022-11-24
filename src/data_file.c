#include "data_file.h"

void goToRRNbin(int RRN, FILE *fp){
    fseek(fp, DISK_PAGE_BIN_SIZE + RRN * REGISTER_BIN_SIZE, SEEK_SET);
}

int returnBinCurrentRRN(FILE *fp){
       return ceil((ftell(fp) - DISK_PAGE_BIN_SIZE) / REGISTER_BIN_SIZE);
}

header_bin readHeaderBin(FILE *fp){
       header_bin header_bin;

       fseek(fp, 0, SEEK_SET);
       fread(&header_bin.status, sizeof(header_bin.status), 1, fp);
       fread(&header_bin.topo, sizeof(header_bin.topo), 1, fp);
       fread(&header_bin.proxRRN, sizeof(header_bin.proxRRN), 1, fp);
       fread(&header_bin.nroRegRem, sizeof(header_bin.nroRegRem), 1, fp);
       fread(&header_bin.nroPagDisco, sizeof(header_bin.nroPagDisco), 1, fp);
       fread(&header_bin.qttCompacta, sizeof(header_bin.qttCompacta), 1, fp);

       return header_bin;
}

void printHeaderBin(header_bin header_bin){
       printf("========================\n");
       printf("   CABEÇALHO BINÁRIO    \n");
       printf("- status:      %c\n", header_bin.status);
       printf("- topo:        %d\n", header_bin.topo);
       printf("- proxRRN:     %d\n", header_bin.proxRRN);
       printf("- nroRegRem:   %d\n", header_bin.nroRegRem);
       printf("- nroPagDisco: %d\n", header_bin.nroPagDisco);
       printf("- qttCompacta: %d\n", header_bin.qttCompacta);
       printf("========================\n");       
}

void readVariableField(FILE *fp, char *string){
       int i = 0;
       char c;
       fread(&c, sizeof(char), 1, fp);
       while (c != '|'){
              string[i] = c;
              fread(&c, sizeof(char), 1, fp);
              i++;
       }
       string[i] = '\0';
}

register_bin readRegisterBin(FILE *fp){
       register_bin register_bin;
       fread(&register_bin.removido, sizeof(register_bin.removido), 1, fp);
       if (register_bin.removido == '1') {
              return register_bin;
       }
       fread(&register_bin.encadeamento, sizeof(register_bin.encadeamento), 1, fp);
       fread(&register_bin.idConecta, sizeof(register_bin.idConecta), 1, fp);  
       fread(register_bin.siglaPais, 2, 1, fp);
       register_bin.siglaPais[2] = '\0';
       fread(&register_bin.idPoPsConectado, sizeof(register_bin.idPoPsConectado), 1, fp);
       fread(&register_bin.unidadeMedida, sizeof(register_bin.unidadeMedida), 1, fp);
       fread(&register_bin.velocidade, sizeof(register_bin.velocidade), 1, fp);
       readVariableField(fp, register_bin.nomePoPs);
       readVariableField(fp, register_bin.nomePais);
       return register_bin;
}

void printRegisterBin(register_bin register_bin){
    printf("========================\n");
    printf("    REGISTRO BINÁRIO    \n");
    printf("- removido: %c\n", register_bin.removido);
    printf("- encadeamento: %d\n", register_bin.encadeamento);
    printf("- idConecta: %d\n", register_bin.idConecta);
    printf("- siglaPais: %s\n", register_bin.siglaPais);
    printf("- idPoPsConectado: %d\n", register_bin.idPoPsConectado);
    printf("- unidadeMedida: %c\n", register_bin.unidadeMedida);
    printf("- velocidade: %d\n", register_bin.velocidade);    
    printf("- nomePoPs: %s\n", register_bin.nomePoPs);
    printf("- nomePais: %s\n", register_bin.nomePais);
    printf("========================\n");
}