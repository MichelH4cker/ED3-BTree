#include "where.h"
#include "main.h"

//============== FUNCOES UTILIZADAS NO COMANDO 3 NO TRABALHO 1 ===================================
int itsInteger(int field_key){
    if (field_key == ID_CONECTA || field_key == ID_POPS_CONECTADO || field_key == VELOCIDADE){
        return INTEGER;
    }
    return CHAR;
}

int selectFieldKey(char fieldName[]){
    const char* dicionary[] = {"idConecta", "siglaPais", "idPoPsConectado", "unidadeMedida", "velocidade", "nomePoPs", "nomePais"};
    int dicionary_len = 7;
    for (int i = 0; i < dicionary_len; i++){
        if (!strcmp(dicionary[i], fieldName)){
            return i;
        }
    }   
    return -1;
}

void set_array_filters(struct filter array_filter[], int n, target inputs){
    char fieldName[22];
    char fieldValueChar[22];
    
    int fieldValueInt;
    int field_key;

    struct filter filter;
    for (int i = 0; i < n; i++){
        field_key = selectFieldKey(inputs.field_in);
        int type = itsInteger(field_key);

        if (type == INTEGER){
            filter.number = inputs.key ;
        } else if (type == CHAR){
            //scan_quote_string(fieldValueChar);
            strcpy(filter.string, inputs.str_in);
        } else {
            printf("Nome do campo inexistente!\n");
            return;
        }

        filter.type = type;
        filter.field_key = field_key;

        array_filter[i] = filter;
    }
}

int search(register_bin reg, struct filter *filter){
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

void readFile(FILE *fp, int command, struct filter *filter, int n){
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
        reg = readRegisterBin(fp);

        if (search(reg, &(*filter))){
            n_found = n_found + 1;
            printTerminal(reg);
        }
       
        fseek(fp, VARIABLE_FIELD_SIZE - (strlen(reg.nomePoPs) + strlen(reg.nomePais) + (2 * PIPE_SIZE)), SEEK_CUR);
    }
    if (n_found == 0 && command != SELECT && command != DELETE) {
           printf("Registro inexistente.\n\n");
    }
    if (command == SELECT){
           printf("Numero de paginas de disco: %d\n\n", numeroPagDiscos);
    } else if (command == WHERE){
           printf("Numero de paginas de disco: %d\n", numeroPagDiscos);
    }
}

//=============== INICIO DAS FUNCOES NOVAS PARA A BUSCA =============================
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

    int numeroPagDiscos;
    fread(&numeroPagDiscos, sizeof(int), 1, fp_data);

    node node;
    header header_index = readHeaderIndex(fp_index);
    //leitura do node com o header.noRaiz
    
    register_bin _register;
    int find;
    target *inputs = malloc(sizeof(target) * n);

    goToRRNbin(0, fp_data);
    for (int i = 0; i < n; i++) {
        scan_quote_string(inputs[i].field_in);
        if (strcmp(inputs[i].field_in, "idConecta") == 0)
            scanf(" %d", &inputs[i].key);
        else
            scan_quote_string(inputs[i].str_in);
    }
    for (int i = 0; i < n; i++) {
        printf("ESTOU AQUI 0.O\n");
        //BUSCA NA ARVORE B
        if (strcmp(inputs[i].field_in, "idConecta") == 0) {
            find = search_btree(fp_index, fp_data, header_index.noRaiz, inputs[i].key, inputs[i].found_rrn, inputs[i].found_pos);
            if (find) {
                printf("Busca %d\n", i);
                printf("Identificador do ponto: %d\n", inputs[i].found_pos);
                printTerminal(_register);
                printf("Numero de paginas de disco: %d\n\n", numeroPagDiscos);
            }
            printf("JA FOI O IF DA ARVRE\n");
        }
        // UTILIZA O COMANDO 3 DO TRABALHO PASSADO
        else {
            printf("VAMO DE BUSCA NORMAL\n");
            struct filter filter;
            struct filter array_filter[n];

            char fieldName[22];
            char fieldValueChar[22];

            int fieldValueInt;
            int field_key;

            set_array_filters(array_filter, n, inputs[i]);

            for (int i = 0; i < n; i++){
                printf("Busca %d\n", i + 1);
                readFile(&(*fp_data), WHERE, &array_filter[i], n);
                if(i + 1 != n){
                    printf("\n");
                } 
            }
        }
        printf("CHEGEUI NA VERIFICAÇÃO SE ENCONTROU OU NAO\n");
        if (!find)
            printf("Registro inexistente.\n");

    }
    printf("SAI DO LOOP DE BUSCA\n");
    free(inputs);

    fclose(fp_data);
    fclose(fp_index);
}