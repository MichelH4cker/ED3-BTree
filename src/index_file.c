#include "index_file.h"

header createHeaderIndex(){
    header header;
    header.status = '0';
    header.noRaiz = 0;
    header.nroChavesTotal = 0;
    header.alturaArvore = 0;
    header.RRNproxNo = 0;
    return header;
}

void fwriteHeaderIndex(FILE *fp, header header){
    fseek(fp, 0, SEEK_SET);
    fwrite(&header.status, sizeof(header.status), 1, fp);
    fwrite(&header.noRaiz, sizeof(header.noRaiz), 1, fp);
    fwrite(&header.nroChavesTotal, sizeof(header.nroChavesTotal), 1, fp);
    fwrite(&header.alturaArvore, sizeof(header.alturaArvore), 1, fp);
    fwrite(&header.RRNproxNo, sizeof(header.RRNproxNo), 1, fp);
}

header readHeaderIndex(FILE *fp){
    header header;

    fseek(fp, 0, SEEK_SET);
    fread(&header.status, sizeof(header.status), 1, fp);
    fread(&header.noRaiz, sizeof(header.noRaiz), 1, fp);
    fread(&header.nroChavesTotal, sizeof(header.nroChavesTotal), 1, fp);
    fread(&header.alturaArvore, sizeof(header.alturaArvore), 1, fp);
    fread(&header.RRNproxNo, sizeof(header.RRNproxNo), 1, fp);

    return header;
}

void printHeaderIndex(header header){
    printf("========================\n");
    printf("        CABEÇALHO       \n");
    printf("- status: %c\n", header.status);
    printf("- noRaiz: %d\n", header.noRaiz);
    printf("- nroChavesTotal: %d\n", header.nroChavesTotal);
    printf("- alturaArvore: %d\n", header.alturaArvore);
    printf("- RRNproxNo: %d\n", header.RRNproxNo);
    printf("========================\n");
}