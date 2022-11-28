// NOME: Michel Hecker Faria | Guilherme Augusto Moreira
// NUSP: 12609690	         | 12547281

#include "delete.h"

void delete_register(FILE *fp, struct reg reg){
    int RRN = truncl((ftell(fp) - PAGE_DISC_SIZE) / REGISTER_TOTAL_SIZE);
    
    struct header current_header;
    current_header = returnCurrentHeader(fp, current_header);

    fseek(fp, PAGE_DISC_SIZE + RRN * REGISTER_TOTAL_SIZE, SEEK_SET); // vai para o início do reg
    
    char removido = '1';
    fwrite(&removido, sizeof(char), 1, fp); // set removido
    fwrite(&current_header.topo, sizeof(int), 1, fp);      // set encadeamento

    char trash = '$'; 
    int amountOfTrash = (REGISTER_TOTAL_SIZE - REMOVIDO_SIZE - ENCADEAMENTO_SIZE);
    for (int i = 0; i < amountOfTrash; i++){
        fwrite(&trash, sizeof(char), 1, fp);
    }

    struct header new_header;
    new_header.status = current_header.status;            
    new_header.topo = RRN;                                        
    new_header.proxRRN = current_header.proxRRN;                                                
    new_header.nroRegRem = ++current_header.nroRegRem;                                    
    new_header.nroPagDisco = current_header.nroPagDisco;                                            
    new_header.qttCompacta = current_header.qttCompacta; 

    updateHeader(fp, new_header);
    
    fseek(fp, PAGE_DISC_SIZE + (RRN * REGISTER_TOTAL_SIZE) + FIX_FIELD_SIZE + strlen(reg.nomePoPs) + strlen(reg.nomePais) + 2 * PIPE_SIZE, SEEK_SET);
}

void delete_controller(FILE *fp){
    int n;
    scanf("%d", &n);

    struct filter array_filter[n];
    
    set_array_filters(array_filter, n);
    for (int i = 0; i < n; readFile(fp, DELETE, &array_filter[i], n), i++);
}