#include "index_file.h"

// HEADER
header createHeaderIndex(){
    header header;
    header.status = '0';
    header.noRaiz = -1;
    header.nroChavesTotal = 0;
    header.alturaArvore = 0;
    header.RRNproxNo = 0;
    return header;
}

void fwriteHeaderIndex(FILE *fp, header headerIndex){
    fseek(fp, 0, SEEK_SET);
   
    fwrite(&headerIndex.status, sizeof(headerIndex.status), 1, fp);
    fwrite(&headerIndex.noRaiz, sizeof(headerIndex.noRaiz), 1, fp);
    fwrite(&headerIndex.nroChavesTotal, sizeof(headerIndex.nroChavesTotal), 1, fp);
    fwrite(&headerIndex.alturaArvore, sizeof(headerIndex.alturaArvore), 1, fp);
    fwrite(&headerIndex.RRNproxNo, sizeof(headerIndex.RRNproxNo), 1, fp);

    char GARBAGE = '$';
    for (int i = 0; i < DISK_PAGE_INDEX_SIZE - HEADER_SIZE; i++)
        fwrite(&GARBAGE, sizeof(GARBAGE), 1, fp);
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

// NOT HEADER
node readNode(FILE *fp){
    node node;
    fread(&node.folha, sizeof(node.folha), 1, fp);
    fread(&node.nroChavesNo, sizeof(node.nroChavesNo), 1, fp);
    fread(&node.alturaNo, sizeof(node.alturaNo), 1, fp);
    fread(&node.RRNdoNo, sizeof(node.RRNdoNo), 1, fp);
    for (int i = 1; i <= M - 1; i++){
        fread(&node.RRNpointers[i], sizeof(node.RRNpointers[i]), 1, fp);
        fread(&node.keys[i].key, sizeof(node.keys[i].key), 1, fp);
        fread(&node.keys[i].RRNkey, sizeof(node.keys[i].RRNkey), 1, fp);
    }
    fread(&node.RRNpointers[M], sizeof(node.RRNpointers[M]), 1, fp);
    
    return node;
}