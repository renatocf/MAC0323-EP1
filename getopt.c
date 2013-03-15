#include<stdio.h>
#include<string.h>
#include "getopt.h"

#define NONE -1 
/* Retorno padrão para argumento não encontrado */

int nextopt = 1;
    /* Variável para armazenar a primeira posição
     * ainda não checada do argv. */

extern char *optarg = NULL;

char getopt(int argc, char **argv, char *optstring)
{
    /** VARIÁVEIS *****************************************************/
        char *aux;         /* Auxiliar para trocar posição de args   */
        int i, j, k;       /* Contadores auxiliares                  */
        char option = '?'; /* Caracter da opção da linha de comando. */
        
        int arg_position = NONE; 
        /* Se existir, troca-se o padrão (NONE) pela posição do argu-
         * mento na linha de comando */
    
    /** PRÉ-PROCESSAMENTO *********************************************/
        /* Analisa o argv buscando por opções iniciadas por '-' */
        for(i = nextopt; i < argc; i++)
        {
            if(argv[i][0] == '-')
            {
                printf("Achei um argumento\n");
                for(j = 0; optstring[j] != '\0'; j++) 
                {
                    printf("%c\n", optstring[j]);
                    if(argv[i][1] != optstring[j]) break;
                    
                    option = optstring[j];
                    printf("%c\n", option);
                    
                    if(optstring[j+1] == ':')
                    {
                        j++;
                        if(argv[i][2] != '\0')
                            optarg = &argv[i][2];
                        else if(argv[i+1] == NULL
                             || argv[i+1][0] == '-') 
                        {
                            option = '?';
                        }
                        else
                        {
                            optarg = argv[i+1];
                            arg_position = i+1;
                        }
                    }
                }
                
                aux = argv[i];
                for(k = i; k > nextopt; k--)
                {
                    printf("argv[%d]: %s ", i, argv[k]);
                    printf("argv[%d-1]: %s ", i, argv[k-1]);
                    printf("\n");
                    argv[k] = argv[k-1];
                }
                argv[nextopt] = aux;
                nextopt++;
                
                if(arg_position != -1)
                {
                    aux = argv[i+1];
                    for(k = arg_position; k > nextopt; k--)
                    {
                        printf("argv[%d]: %s ", i+1, argv[k]);
                        printf("argv[%d-1]: %s ", i+1, argv[k-1]);
                        printf("\n");
                        argv[k] = argv[k-1];
                    }
                    argv[nextopt] = aux;
                }
                
                nextopt++;
                
                if(option == '?') 
                    return '?';
                return option;
            }
        }
    
    return -1;
}
