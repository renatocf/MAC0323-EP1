#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* Tamanho para a matriz de entrada/saída */
#define MAX_HEIGHT 100
#define MAX_WIDTH 5

/* Tamanho para a tabela de comandos */
#define W_SIZE 4
#define G_SIZE 19

/* Comandos do HIPO */
#define LDA 0
#define STA 1
#define ADD 2
#define SUB 3 
#define MUL 4
#define DIV 5
#define REM 6
#define REV 7
#define INN 8
#define PRN 9
#define NOP 10
#define JMP 11
#define JLE 12
#define JDZ 13
#define JGT 14 
#define JEQ 15
#define JLT 16
#define JGE 17
#define STP 18

/* Constantes, linha em branco e erros */
#define POS_NUMBER '+'
#define NEG_NUMBER '-'
#define BLANK_LINE -1
#define SYNTAX_ERROR -2

char **analyse_convert(char **i_matrix);
int check_syntax(char *line, char grammar[G_SIZE][W_SIZE]);
char * make_output_line(int line, int command, char **matrix);

int main(int argc, char **argv)
{
    char **teste; int i; /* char *ch; char a = 'a'; */
    teste = (char **) malloc(MAX_HEIGHT * sizeof(char *));
    for(i = 0; i < MAX_HEIGHT; i++)
    {
        teste[i] = (char *) malloc(MAX_WIDTH * sizeof(char));
    }
    
    teste[0] = "INN20";
    teste[1] = "ADD20";
    teste[2] = "+2020";
    teste[3] = "\n";
    teste[4] = "-2020";
    
    analyse_convert(teste);
    
    printf("After conversion:\n");
    for(i = 0; i < MAX_HEIGHT-80; i++)
        printf("%2.d %s\n", i, teste[i]);
    
    return 0;
}

char **analyse_convert(char **i_matrix)
{
    int i, result;
    char grammar[G_SIZE][W_SIZE] = 
    {
        "LDA", "STA", "ADD", "SUB", "MUL", "DIV", "REM", "REV", 
        "INN", "PRN", "NOP", "JMP", "JLE", "JDZ", "JGT", "JEQ", 
        "JLT", "JGE", "STP"
    };
    
    for(i = 0; i < MAX_HEIGHT; i++)
    {
        result = check_syntax(i_matrix[i], grammar);
        switch(result)
        {
            case SYNTAX_ERROR:
                return NULL; break;
            case BLANK_LINE:
                break;
            default:
                i_matrix[i] = make_output_line(i, result, i_matrix);
        }
        printf("linha i=%d ", i);
        printf("%c", i_matrix[i][0]);
        printf("%c", i_matrix[i][1]);
        printf("%c", i_matrix[i][2]);
        printf("%c", i_matrix[i][3]);
        printf("%c\n", i_matrix[i][4]);
    }
    return i_matrix;
}

int check_syntax(char *line, char grammar[G_SIZE][W_SIZE])
{
    int i = 0;
    switch(line[0])
    {
        case '+':
            return POS_NUMBER;
        case '-':
            return NEG_NUMBER;
        case '\n':
            return BLANK_LINE;
        default:
            for(i = 0; i < G_SIZE; i++)
                if(strncmp(line, grammar[i], 3) == 0) return i;
    }
    return SYNTAX_ERROR;
}

char * make_output_line(int line, int command, char **matrix)
{
    char *out = (char *) malloc (W_SIZE * sizeof(*out));
    out[0] = '+'; 
    out[3] = matrix[line][3]; 
    out[4] = matrix[line][4]; 
    
    switch(command)
    {
        case LDA: /*11*/
            out[1] = '1'; out[2] = '1';
            break;
        case STA: /*12*/
            out[1] = '1'; out[2] = '2';
            break;
        case ADD: /*21*/
            out[1] = '2'; out[2] = '1';
            break;
        case SUB: /*22*/
            out[1] = '2'; out[2] = '2';
            break; 
        case MUL: /*23*/
            out[1] = '2'; out[2] = '3';
            break;
        case DIV: /*24*/
            out[1] = '2'; out[2] = '4';
            break;
        case REM: /*25*/
            out[1] = '2'; out[2] = '5';
            break;
        case REV: /*29*/
            out[1] = '2'; out[2] = '9';
            break;
        case INN: /*31*/
            out[1] = '3'; out[2] = '1';
            break;
        case PRN: /*41*/
            out[1] = '4'; out[2] = '1';
            break;
        case NOP: /*50*/
            out[1] = '5'; out[2] = '0';
            break;
        case JMP: /*51*/
            out[1] = '5'; out[2] = '1';
            break;
        case JLE: /*52*/
            out[1] = '5'; out[2] = '2';
            break;
        case JDZ: /*53*/
            out[1] = '5'; out[2] = '3';
            break;
        case JGT: /*54*/
            out[1] = '5'; out[2] = '4';
            break;
        case JEQ: /*55*/
            out[1] = '5'; out[2] = '5';
            break;
        case JLT: /*56*/
            out[1] = '5'; out[2] = '6';
            break;
        case JGE: /*57*/
            out[1] = '5'; out[2] = '7';
            break;
        case STP: /*70*/
            out[1] = '7'; out[2] = '0';
            break;
        case NEG_NUMBER:
            out[0] = '-'; 
        case POS_NUMBER:
            out[1] = matrix[line][1]; 
            out[2] = matrix[line][2]; 
    }
    return out;
}