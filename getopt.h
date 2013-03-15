#define NONE -1 
/* Retorno padrão para argumento não encontrado */

extern char *optarg;
extern int optind, optopt;

char getopt(int argc, char **argv, char *optstring);
