#include<stdlib.h>
#include<stdio.h>
#include<math.h>

#include "getopt.h"
#include "queue.h"
#include "Point.h"

#include "grid.h"
#include "kruskal.h"

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
    Grid teste;
    point *p = Points;
    /* point p[] = {{0.1,0.1},{0.2,0.2}}; */
    Grid_p *aux, *q, *aux1, *aux2;
    int i, j, k, l, n_squares, count = 0, scount = 0;
    
    teste = grid_init(d, 1, N, NO_M);
    grid_construct(teste, p, N, 1);
    
    n_squares = get_grid_n_squares(teste);
   
    for(i = 0; i < n_squares; i++)
        for(j = 0; j < n_squares; j++) 
        {
            printf("%d %d: ", i, j);
            /* aux = teste->g[i][j]; */
            /* if(aux == NULL) printf("problem!"); */
            
            for(aux = get_grid_square(teste, i, j); 
                    aux != NULL; aux = aux->next) 
            {
                for(aux1 = aux->next; aux1 != NULL; aux1 = aux1->next)
                    if(distance(aux->p, aux1->p) < d) count++;
                printf("count: %d\n", count);
                for(k = i-1; k <= i+1; k++)
                {
                    if(k < 0) continue; if(k > n_squares) break;
                    for(l = j-1; l <= j+1; l++)
                    {
                        if(l < 0) continue; if(l > n_squares) break;
                        for(aux1 = get_grid_square(teste, k, l), q = aux1;
                            aux1 != NULL; q = aux1, aux1 = aux1->next) {
                            scount = 0;
                            /* printf("get point x:%f y:%f", aux1->p.x,  */
                                    /* aux1->p.y); */
                            if(distance(aux->p, aux1->p) < d) 
                            {
                                scount++; 
                                q->next = aux1->next; aux1 = q;
                                printf("Retirando pontos:\n");
                                for(aux2 = aux; aux2 != NULL;
                                        aux2 = aux2->next)
                                    printf("p: %f %f\n", aux2->p.x,
                                            aux2->p.y);
                                printf("\n");
                            }
                            if(scount == 0) 
                            {
                                printf("count: %d\n", count);  
                                return EXIT_FAILURE; 
                            }
                            else count += scount;
                        }
                    }
                }
                printf("entrou \n");
                printf("x:%f y:%f\n", aux->p.x, aux->p.y);
            }
            printf("\n");
        }
    
    printf("count: %d\n", count);
    
    /* Grid p; int i, j, n_squares; int count; */
    /* Grid_p *aux1, *aux2; */
    /*  */
    /* p = grid_init(d, 1, N, NO_M); */
    /* grid_construct(p, Points, N, 1); */
    /*  */
    /* #<{(| Número de quadrados do grid |)}># */
    /* n_squares = get_grid_n_squares(p); */
    /*  */
    /* for(i = 0; i < n_squares; i++) */
    /*     for(j = 0; j < n_squares; j++) */
    /*         printf("[%d][%d]:", i, j); */
    /*         for(aux1 = get_grid_square(p, i, j); aux1 != NULL; aux1 = aux1->next) */
    /*             printf("[%d][%d] x:%f y:%f\n", i, j, aux1->p.x, aux1->p.y); */
    /*         pr */
    
    /* for(i = 0; i < n_squares; i++) */
    /*     for(j = 0; j < n_squares; j++) */
    /*     { */
    /*         for(aux1 = get_grid_square(p, i, j);  */
    /*             aux1 != NULL; aux1 = aux1->next) */
    /*         { */
    /*             printf("point[%d][%d] %f %f", i, j, aux1->p.x, */
    /*                     aux1->p.y); */
    /*             for(aux2 = aux1->next; aux2 != NULL; aux2 = aux2->next) */
    /*                 if(distance(aux1->p, aux2->p) < d) count++; */
                /* if((i+1) != get_grid_n_squares(p)) */
                /*     for(aux2 = get_grid_square(p, i+1, j); aux2 != NULL; aux2 = aux2->next) */
                /*         if(distance(aux1->p, aux2->p) < d) count++; */
                /* if((j+1) != get_grid_n_squares(p)) */
                /*     for(aux2 = get_grid_square(p, i, j+1); aux2 != NULL; aux2 = aux2->next) */
                /*         if(distance(aux1->p, aux2->p) < d) count++; */
                /* if((i+1) != get_grid_n_squares(p)  */
                /* && (j+1) != get_grid_n_squares(p)) */
                /*     for(aux2 = get_grid_square(p, i+1, j+1); aux2 != NULL; aux2 = aux2->next) */
                /*         if(distance(aux1->p, aux2->p) < d) count++; */
        /*     } */
        /*     if(count == N-1) return EXIT_SUCCESS; */
        /* } */
    
    return EXIT_FAILURE;
    /* Queue border; */
    /* char *connected; */
    /* int i, calc, n_con = 0, q_size = 0; */
    /* point query; */
    /*  */
    /* connected = (char *) malloc(N * sizeof(*connected)); */
    /* border = queueInit(); */
    /*  */
    /* queuePut(border, Points[0]); */
    /* connected[0] = 1; */
    /* q_size = 1; */
    /*  */
    /* while(!queueEmpty(border)) */
    /* { */
    /*     query = queueGet(border); calc = 0; q_size--; */
    /*     for(i = 0; i < N; i++) */
    /*     { */
    /*         if(connected[i] == 1) { */
    /*             continue;#<{(| CUIDADO COM O LIXO! |)}># */
    /*         } */
    /*         calc = 1; */
    /*         if(distance(query, Points[i]) < d) */
    /*         { */
    /*             #<{(| printf("Mais um conexo!\n"); |)}># */
    /*             n_con++; */
    /*             queuePut(border, Points[i]); q_size++; */
    /*             connected[i] = 1; */
    /*         } */
    /*         if(verb_mode) printf("q_size: %d n_con: %d\n", q_size, n_con); */
    /*     } */
    /*     if(calc == 0) return EXIT_SUCCESS; */
    /*     #<{(| if(n_con % 10 == 0) printf("rodada de 10\n"); |)}># */
    /* } */
    /*  */
    /* queueFree(border); free(connected); */
    /*  */
    /* return EXIT_FAILURE; */
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
