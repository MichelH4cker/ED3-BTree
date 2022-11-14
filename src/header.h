#ifndef __HEADER_H__
#define __HEADER_H__

typedef struct header {
    char status;        // 1 byte
    int noRaiz;         // 4 bytes
    int nroChavesTotal; // 4 bytes
    int alturaArvore;   // 4 bytes
    int RRNproxNo;      // 4 bytes
} header;

#endif