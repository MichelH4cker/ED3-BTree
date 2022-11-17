#include "data_file.h"

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
       register_bin reg;
    
       fread(&reg.removido, sizeof(reg.removido), 1, fp);
       fread(&reg.encadeamento, sizeof(reg.encadeamento), 1, fp);
       fread(&reg.idConecta, sizeof(reg.idConecta), 1, fp);  
       fread(reg.siglaPais, 2, 1, fp);
       reg.siglaPais[2] = '\0';
       fread(&reg.idPoPsConectado, sizeof(reg.idPoPsConectado), 1, fp);
       fread(&reg.unidadeMedida, sizeof(reg.unidadeMedida), 1, fp);
       fread(&reg.velocidade, sizeof(reg.velocidade), 1, fp);
       readVariableField(fp, reg.nomePoPs);
       readVariableField(fp, reg.nomePais);

       fseek(fp, VARIABLE_FIELD_SIZE - (strlen(reg.nomePoPs) + strlen(reg.nomePais) + (2 * PIPE_SIZE)), SEEK_CUR);
}