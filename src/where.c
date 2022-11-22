#include "where.h"

void where(FILE *fp){
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

    for (int i = 0; i < n; i++) {
        scan_quote_string(field_in);
        if (strcmp(field_in, "idConecta") == 0) {
            scanf(" %d", &target.key);
            search(header.noRaiz, target.key, target.found_rrn, target.found_pos);
        }
        else {
            scan_quote_string(str_in);
            //abre a funcao do comando 3
        }

    }
}