#include<stdio.h>
#include<stdlib.h>

#include "getopt.h"
#include "queue.h"

typedef struct options {
    int N;   /* Número de pontos */
    int M;   /* Número de testes */
    float d; /* Distância entre pontos */
    int s;   /* Semente de números aleatórios */
    int v;   /* Verbosidade nível 1 */
    int V;   /* Verbosidade nível 2 */
    int h;   /* Ajuda */
} Options;

char usage[] = "Uso: EP1 -N [-d] [-M] [-s] [-v] [-V]\n"
               "Digite -h para mais informações \n";
char error[] = "Erro: número de pontos requerido como argumento\n";
char help[]  = "LIMIAR DE CONEXIDADE PARA CERTOS GRAFOS GEOMÉTRICOS\n"
               "\n"
               "Lista de opções:\n"
               "* -N: número de pontos;\n"
               "* -d: distância para verificar conexidade (modo 1);\n"
               "* -M: número de rodadas para cálculo da 'densidade\n"
               "      normalizada crítica para conexidade' (modo 2);\n"
               "* -s: semente de números aleatórios;\n"
               "* -v: verbosidade 1 - imprime números gerados (modo\n"
               "      1) ou densidade normalizada crítica (modo 2);\n"
               "* -V: verbosidade 2 - imprime números gerados e a\n"
               "      densidade normalizada crítica (modo 2);\n";

int receive_arguments(int argc, char **argv, Options *args);

/*
////////////////////////////////////////////////////////////////////////
-----------------------------------------------------------------------
                                  MAIN
-----------------------------------------------------------------------
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/
int main(int argc, char **argv)
{
    /** VARIÁVEIS *****************************************************/
        Queue teste, teste2;
        int result;
        int i, j; Link aux;
        
        /* Struct com argumentos da linha de comando */
        Options args = { 0, 0, 0, 314159265, 0, 0 }; 

    /** ARGUMENTOS ****************************************************/
        result = receive_arguments(argc, argv, &args);
        if(result == EXIT_FAILURE) return EXIT_FAILURE;
        
        if(args.h == 1)
        {
            printf("\n%s\n", help);
            return EXIT_SUCCESS;
        }
        
        if(args.N == 0) 
        {
            printf("\n%s%s\n", error, usage);
            return EXIT_FAILURE;
        }
    
    teste = queueInit();
    teste2 = queueInit();
    
    if(teste == NULL) printf("teste NULL\n");
    else printf("teste NOT NULL\n");
    for(i = 0; i < args.N; i++) {
        queuePut(teste, i);
        queuePut(teste2, i+args.N);
    }
    if(teste->init == NULL) printf("NULL init\n");
    
    /* aux = teste->init; if(aux->next != NULL) printf("ops"); */
    /* else printf("no ops"); */
    
    /* Percorre a fila (final para começo) */
    for(aux = teste->end; aux != NULL; aux = aux->next)
        printf("%d ", aux->item);
    printf("\n");
    for(aux = teste2->end; aux != NULL; aux = aux->next)
        printf("%d ", aux->item);
    printf("\n");
    /* for(aux = teste2->end; aux != NULL; aux = aux->next) */
    /*     printf("%d ", aux->item); */
    /* printf("\n"); */
    
    /* for(i = 0; i < 10; i++) */
    /* { */
    /*     j = queueGet(teste); */
    /*     #<{(| printf("%d\n", j); |)}># */
    /*     for(aux = teste->end; aux != NULL; aux = aux->next) */
    /*         printf("%d ", aux->item); */
    /*     printf("\n"); */
    /* } */
    if(teste->init->next == NULL) printf("NULL init next\n");
    
    queueFree(teste);
    /* while(!queueEmpty(teste)) */
    /* { */
    /*     aux = teste->end; */
    /*     teste->end = aux->next; */
    /*     for(aux = teste->end; aux != NULL; aux = aux->next) */
    /*         printf("%d ", aux->item); */
    /*     printf("\n"); */
    /* }  */
    if(queueEmpty(teste)) printf("queue empty\n");
    else printf("queue not empty\n");
    for(aux = teste->end; aux != NULL; aux = aux->next)
        printf("%d ", aux->item);
    
    for(i = 0; i < argc; i++)
        printf("%s ", argv[i]);
    printf("\n");
    
    return 0;
}

int receive_arguments(int argc, char **argv, Options *args)
    /* Recebe os argumentos da linha de comando e os 
     * armazena na struct correspondente */
{
    char opt; /* int i = 0; */
    while((opt = getopt(argc, argv, "N:M:s:d:vVh")) != NONE)
    {
        /* for(i = 0; i < argc; i++) */
        /*     printf("%s ", argv[i]); */
        /* printf("\n"); */
        
        /* printf("option: %c\n", opt); */
        /* printf("optarg: %s\n", optarg); */
        /* printf("optopt: %c\n", optopt); */
        /* printf("optind: %d\n", optind); */
        
        switch(opt)
        {
            case 'N':
                args->N = atoi(optarg); break;
            case 'M':
                args->M = atoi(optarg); break;
            case 'd':
                args->d = atof(optarg); break;
            case 's':
                args->s = atoi(optarg); break;
            case 'v':
                args->v = 1; break;
            case 'V':
                args->V = 1; break;
            case 'h':
                args->h = 1; break;
            case '?':
                printf("Argumento -%c desconhecido\n", optopt);
                return EXIT_FAILURE;
        }
    } /* while */
    return EXIT_SUCCESS;
}
