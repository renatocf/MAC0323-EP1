#include<stdlib.h>
#include<stdio.h>
#include<math.h>

#include "getopt.h"
#include "queue.h"
#include "Point.h"

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
int check_connectivity(point *Points, int N, float d, int verb_mode);
float calc_normalized_critical_density(point *Points, int N, int M, int verb_mode);

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
        int func_err;
        int i /*, j */;
        int verb_mode = 0;
        point *Points;
        point a;
        float d;
        
        /* Struct com argumentos da linha de comando */
        Options args = { 0, 0, 0, 314159265, 0, 0 }; 

    /** ARGUMENTOS ****************************************************/
        func_err = receive_arguments(argc, argv, &args);
        if(func_err) return EXIT_FAILURE;
        
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
        
        verb_mode = args.v + args.V;
    
    /** PONTOS ALEATÓRIOS *********************************************/
        set_seed(args.s);
        a = r_point();
        printf("teste semente: %f %f\n", a.x, a.y);
        
        /* Gera vetor com pontos aleatórios */
        Points = (point *) malloc(args.N * sizeof(*Points));
        for(i = 0; i < args.N; i++) 
        {
            Points[i] = r_point();
            if(verb_mode) 
                printf("%d: %f %f\n", i, Points[i].x, Points[i].y);
        }
        
    /** MODO 1: CONEXIDADE ********************************************/
        if(args.d != 0) 
        {
            func_err = 
                check_connectivity(Points, args.N, args.d, verb_mode);
            if(func_err)
                printf("Grafo não é conexo para d = %g\n", args.d);
            else 
                printf("Grafo é conexo para d = %g\n", args.d);
        }
        
    /** MODO 2: DENSIDADE NORMALIZADA CRÍTICA *************************/
        if(args.M != 0)
        {
            d = calc_normalized_critical_density(Points, args.N, args.M, verb_mode);
            printf("Densidade normalizada crítica d = %f", d);
        }
    
    printf("\n");
    for(i = 0; i < argc; i++)
        printf("%s ", argv[i]);
    printf("\n");
    
    return 0;
}

float calc_normalized_critical_density(point *Points, int N, int M, int verb_mode)
{
    int i, j;
    float dist = 0;
    float smaller = 0;
    int smaller_p = 0;
    float largest = 0;
    
    for(i = 0; i < N; i++)
    {
        if(verb_mode) printf("\n");
        dist = 0; smaller = sqrt(2);
        for(j = i+1; j < N; j++)
        {
            dist = distance(Points[i], Points[j]);
            if(verb_mode) printf("%g ", dist);
            if(dist < smaller) 
            {
                smaller = dist;
                smaller_p = j;
            }
        }
        if(verb_mode) printf("\n");
        if(verb_mode) printf("* smaller_p: %d\n", smaller_p);
        if(verb_mode) printf("* smaller: %g\n", smaller);
        if(verb_mode) printf("* largest: %g\n", largest);
        for(j = i; j > 0; j--)
        {
            dist = distance(Points[smaller_p], Points[j]);
            if(verb_mode) printf("%g ", dist);
            if(dist < smaller)
            {
                smaller = dist;
                smaller_p = j;
            }
        }
        if(verb_mode) printf("\n");
        if(verb_mode) printf("* smaller_p: %d\n", smaller_p);
        if(verb_mode) printf("* smaller: %g\n", smaller);
        if(verb_mode) printf("* largest: %g\n", largest);
        if(smaller > largest) largest = smaller;
    }
    return largest;
}

int check_connectivity(point *Points, int N, float d, int verb_mode)
{
    Queue border;
    char *connected;
    int i, calc, n_con = 0, q_size = 0;
    point query;
    
    connected = (char *) malloc(N * sizeof(*connected));
    border = queueInit();
    
    queuePut(border, Points[0]);
    connected[0] = 1;
    q_size = 1;
    
    while(!queueEmpty(border))
    {
        query = queueGet(border); calc = 0; q_size--;
        for(i = 0; i < N; i++)
        {
            if(connected[i] == 1) {
                continue;/* CUIDADO COM O LIXO! */
            }
            calc = 1;
            if(distance(query, Points[i]) < d)
            {
                /* printf("Mais um conexo!\n"); */
                n_con++;
                queuePut(border, Points[i]); q_size++;
                connected[i] = 1;
            }
            if(verb_mode) printf("q_size: %d n_con: %d\n", q_size, n_con);
        }
        if(calc == 0) return EXIT_SUCCESS;
        /* if(n_con % 10 == 0) printf("rodada de 10\n"); */
    }
    
    queueFree(border); free(connected);
    
    return EXIT_FAILURE;
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
