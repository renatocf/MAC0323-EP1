#include<stdio.h>
#include<stdlib.h>

#include "getopt.h"

int main(int argc, char **argv)
{
    char opt;
    int i = 0;
    
    for(i = 0; i < argc; i++)
        printf("%s ", argv[i]);
    printf("\n");
    
    while((opt = getopt(argc, argv, "v:ak::")) != NONE)
    {
        for(i = 0; i < argc; i++)
            printf("%s ", argv[i]);
        printf("\n");
        
        printf("option: %c\n", opt);
        printf("optarg: %s\n", optarg);
        printf("optopt: %c\n", optopt);
    }
    
    return 0;
}
