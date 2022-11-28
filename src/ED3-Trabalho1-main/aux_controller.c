// NOME: Michel Hecker Faria | Guilherme Augusto Moreira
// NUSP: 12609690	         | 12547281

#include "aux_controller.h"

void filterConstructor(struct filter filter){
    filter.type = -1;
    filter.field_key = -1;
    filter.number = -1;
    strcpy(filter.string, " ");
}

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

void set_array_filters(struct filter array_filter[], int n){
    char fieldName[22];
    char fieldValueChar[22];
    
    int fieldValueInt;
    int field_key;

    struct filter filter;
    for (int i = 0; i < n; i++){
        scanf("%s", fieldName);

        field_key = selectFieldKey(fieldName);
        int type = itsInteger(field_key);

        if (type == INTEGER){
            scanf("%d", &fieldValueInt);
            filter.number = fieldValueInt;
        } else if (type == CHAR){
            scan_quote_string(fieldValueChar);
            strcpy(filter.string, fieldValueChar);
        } else {
            printf("Nome do campo inexistente!\n");
            return;
        }

        filter.type = type;
        filter.field_key = field_key;

        array_filter[i] = filter;
    }
}