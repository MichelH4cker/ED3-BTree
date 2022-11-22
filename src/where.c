#include "where.h"

int search_data(char *filed_in, char *str_in) {
    int output = 0;

    if (filter->type == INTEGER){
        switch (filter->field_key){
            case ID_CONECTA:
                output = (reg.idConecta == filter->number) ? 1 : 0;
                if (output) return output;
                break;
            case ID_POPS_CONECTADO:
                output = (reg.idPoPsConectado == filter->number) ? 1 : 0;
                if (output) return output;
                break; 
            case VELOCIDADE:
                output = (reg.velocidade == filter->number) ? 1 : 0;
                if (output) return output;
                break;
            default:
                break;
        }
    } else { //é char
        switch (filter->field_key){
            case SIGLA_PAIS:
                output = (!strcmp(reg.siglaPais, filter->string)) ? 1 : 0; 
                if (output) return output;
                break;
            case UNIDADE_MEDIDA:
                output =  ((reg.unidadeMedida == filter->string[0]) && (strlen(filter->string) == 1)) ? 1 : 0; 
                if (output) return output;
                break;
            case NOME_POPS:
                output = (!strcmp(reg.nomePoPs, filter->string)) ? 1 : 0; 
                if (output) return output;
                break;
            case NOME_PAIS:
                output = (!strcmp(reg.nomePais, filter->string)) ? 1 : 0; 
                if (output) return output;
                break;
            default:
                break;
        }
    } 
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
      
    struct reg reg;

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

void where(FILE *fp, FILE *fp_data){
    int n;
    scanf("%d", &n);

    node node;
    header header;

    header = readHeaderIndex(fp);
    //leitura do node com o header.noRaiz

    struct target {
        int key;
        int found_rrn;
        int found_pos;
    } target;
    char field_in[20];
    char str_in[20];
    register_bin _register;
    int find;

    fseek(fp_data, 65, SEEK_SET);
    for (int i = 0; i < n; i++) {
        scan_quote_string(field_in);
        _register = readRegisterBin(fp_data);
        if (strcmp(field_in, "idConecta") == 0) {
            scanf(" %d", &target.key);
            find = search(header.noRaiz, target.key, target.found_rrn, target.found_pos);
            if (find)
                printTerminal(_register);
        }
        else {
            scan_quote_string(str_in);
            if(search_data(field_in, str_in)) 
                printTerminal(_register);
        }

        if (!find)
            printf("Registro inexistente.\n");

    }
}