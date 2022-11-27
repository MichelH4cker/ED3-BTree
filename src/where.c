#include "where.h"

int search_data(char *field_in, char *str_in, register_bin _register) {
    if (strcmp(field_in, "idPopsConectado") == 0)
        if (atoi(str_in) ==_register.idPoPsConectado)
            return 1;
    else if (strcmp(field_in, "velocidade") == 0)
        if (atoi(str_in) == _register.velocidade)
            return 1;
    
    else if (strcmp(field_in, "siglaPais") == 0)
        if (strcmp(str_in, _register.siglaPais) == 0)
            return 1;
    else if (strcmp(field_in, "unidadeMedida") == 0)
        if (str_in[0] == _register.unidadeMedida)
            return 1;
    else if (strcmp(field_in, "nomePops") == 0)
        if (strcmp(str_in, _register.nomePoPs) == 0)
            return 1;
    else if (strcmp(field_in, "nomePais") == 0)
        if (strcmp(str_in, _register.nomePais) == 0)
            return 1; 
    return 0;
}

void printTerminal(register_bin reg){
       if (reg.idConecta != -1)
              printf("Identificador do ponto: %d\n", reg.idConecta);
       if (strlen(reg.nomePoPs) != 0)        
              printf("Nome do ponto: %s\n", reg.nomePoPs);
       if (strlen(reg.nomePais) != 0)         
              printf("Pais de localizacao: %s\n", reg.nomePais);
       if (reg.siglaPais[0] != '$')         
              printf("Sigla do pais: %s\n", reg.siglaPais);
       if (reg.idPoPsConectado != -1)         
              printf("Identificador do ponto conectado: %d\n", reg.idPoPsConectado);
       if (reg.velocidade != -1)         
              printf("Velocidade de transmissao: %d %cbps\n", reg.velocidade, reg.unidadeMedida);
       printf("\n");
}

void readFile(FILE *fp){
    fseek(fp, POS_PAG_DISCO_SIZE, SEEK_SET);
    int numeroPagDiscos;
    fread(&numeroPagDiscos, sizeof(int), 1, fp);

    fseek(fp, 0, SEEK_END);
    long int f_end = ftell(fp);

    fseek(fp, PAGE_DISC_SIZE, SEEK_SET); // pula cabeçalho

    char string[22];
      
    register_bin reg;

    int n_found = 0;
    while (ftell(fp) < f_end){
        fread(&reg.removido, sizeof(reg.removido), 1, fp);
        if (reg.removido == '1') {
            fseek(fp, REGISTER_TOTAL_SIZE - 1, SEEK_CUR); // pula reg vazio
            continue;
        }
              
        fread(&reg.encadeamento, sizeof(reg.encadeamento), 1, fp);
        fread(&reg.idConecta, sizeof(reg.idConecta), 1, fp);  
        fread(reg.siglaPais, 2, 1, fp);
        reg.siglaPais[2] = '\0';
        fread(&reg.idPoPsConectado, sizeof(reg.idPoPsConectado), 1, fp);
        fread(&reg.unidadeMedida, sizeof(reg.unidadeMedida), 1, fp);
        fread(&reg.velocidade, sizeof(reg.velocidade), 1, fp);

        readVariableField(fp, reg.nomePoPs);
        readVariableField(fp, reg.nomePais);

        //decidesWhatToDo(&(*fp), command, reg, filter, &n_found);
             
        fseek(fp, VARIABLE_FIELD_SIZE - (strlen(reg.nomePoPs) + strlen(reg.nomePais) + (2 * PIPE_SIZE)), SEEK_CUR);
    }

    printf("Numero de paginas de disco: %d\n", numeroPagDiscos);
}

void where(char *index, char *data){
    //ABRE OS ARQUIVOS
    FILE *fp_data = fopen(data, "rb+");
    if(fp_data == NULL){
        printf("Erro no processamento do arquivo!\n");
        printf("%s\n", data);
        return;
    }
    FILE *fp_index = fopen(index, "rb+");
    if(fp_data == NULL){
        printf("Erro no processamento do arquivo!\n");
        printf("%s\n", index);
        return;
    } 

    int n;
    scanf("%d", &n);

    printf("INICIO DE TUDO\n");
    node node;
    header header_index = readHeaderIndex(fp_index);
    //leitura do node com o header.noRaiz

    printf("antes de tudo ;-;\n");
    typedef struct target {
        int key;
        int found_rrn;
        int found_pos;
    
        char field_in[20];
        char str_in[20];
    } target;
    
    register_bin _register;
    int find;
    target *inputs = malloc(sizeof(target) * n);

    fseek(fp_data, 65, SEEK_SET);
    printf("CHEGUEI AQUI\n");
    for (int i = 0; i < n; i++) {
        scan_quote_string(inputs[i].field_in);
        if (strcmp(inputs[i].field_in, "idConecta") == 0)
            scanf(" %d", &inputs[i].key);
        else
            scan_quote_string(inputs[i].str_in);
    }
    //printf("PASSSEI PELO LOOP DE ENTRADA --- %d\n", inputs[0]);
    for (int i = 0; i < n; i++) {
        printf("hmm\n");
        _register = readRegisterBin(fp_data);
        printf("ESTOU AQUI 0.O\n");
        if (strcmp(inputs[i].field_in, "idConecta") == 0) {
            find = search(fp_index, fp_data, 65, inputs[i].key, inputs[i].found_rrn, inputs[i].found_pos);
            if (find) {
                printf("Busca %d\n", i);
                printf("Identificador do ponto: %d\n", inputs[i].found_pos);
                printTerminal(_register);
            }
            printf("JA FOI O IF DA ARVRE\n");
        }
        else {
            if(search_data(inputs[i].field_in, inputs[i].str_in, _register)) 
                printTerminal(_register);
        }
        printf("CHEGEUI NA VERIFICAÇÃO SE ENCONTROU OU NAO\n");
        if (!find)
            printf("Registro inexistente.\n");

    }
    printf("SAI DO LOOP DE BUSCA\n");
    free(inputs);
    //header_index.status = '1';
    //fwriteHeaderIndex(fp_index, header_index);

    fclose(fp_data);
    fclose(fp_index);
}