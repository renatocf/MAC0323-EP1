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
    
    while((opt = getopt(argc, argv, "v:")) != -1)
    {
        for(i = 0; i < argc; i++)
            printf("%s ", argv[i]);
        printf("\n");
        
        printf("opt: %c", opt);
    }
    
    return 0;
}
