// NOME: Michel Hecker Faria | Guilherme Augusto Moreira
// NUSP: 12609690	        | 12547281

#include "bin_controller.h"

int search(struct reg reg, struct filter *filter){
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

void printTerminal(struct reg reg){
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

void readVariableField(FILE *fp, char *string){
       int i = 0;
       char c;
       fread(&c, sizeof(char), 1, fp);
       while (c != '|'){
              string[i] = c;
              fread(&c, sizeof(char), 1, fp);
              i++;
       }
       string[i] = '\0';
}

void decidesWhatToDo(FILE *fp, int command, struct reg reg, struct filter *filter, int *n_found){
       switch (command){
              case CREATE:
                     break;
              case SELECT:
                     printTerminal(reg);
                     break;
              case WHERE:
                     if (search(reg, &(*filter))){
                            *n_found = *n_found + 1;
                            printTerminal(reg);
                     }
                     break;
              case DELETE:
                     if (search(reg, &(*filter))){
                            *n_found = *n_found + 1;
                            delete_register(&(*fp), reg);
                     }
                     
                     break;
              default:
                     break;
       }
}

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