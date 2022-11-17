#include "where_b.h"



void readFile(FILE *fp, int command, struct filter *filter, int n){
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

              decidesWhatToDo(&(*fp), command, reg, filter, &n_found);

              fseek(fp, VARIABLE_FIELD_SIZE - (strlen(reg.nomePoPs) + strlen(reg.nomePais) +
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

void where_b (FILE *fp) {
    int n;
    scanf("%d", &n);

    struct filter filter;
    struct filter array_filter[n];

    char fieldName[22];
    char fieldValueChar[22];

    int fieldValueInt;
    int field_key;

    set_array_filters(array_filter, n);

    for (int i = 0; i < n; i++){
        printf("Busca %d\n", i + 1);
        readFile(&(*fp), WHERE, &array_filter[i], n);
        if(i + 1 != n){
            printf("\n");
        }
    }

}