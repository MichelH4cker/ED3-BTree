#include "header.h"

header readHeader(FILE *fp){
    header header;

    fseek(fp, 0, SEEK_SET);
    fread(&header.status, sizeof(header.status), 1, fp);
    fread(&header.noRaiz, sizeof(header.noRaiz), 1, fp);
    fread(&header.nroChavesTotal, sizeof(header.nroChavesTotal), 1, fp);
    fread(&header.alturaArvore, sizeof(header.alturaArvore), 1, fp);
    fread(&header.RRNproxNo, sizeof(header.RRNproxNo), 1, fp);

    return header;
}

void printHeader(header header){
    printf("========================\n");
    printf("        CABEÇALHO       \n");
    printf("- status: %c\n", header.status);
    printf("- noRaiz: %d\n", header.noRaiz);
    printf("- nroChavesTotal: %d\n", header.nroChavesTotal);
    printf("- alturaArvore: %d\n", header.alturaArvore);
    printf("- RRNproxNo: %d\n", header.RRNproxNo);
    printf("========================\n");
}