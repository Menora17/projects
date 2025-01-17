#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lexer.h"
#include "Parser.h"
char* read_file(int* size)
{
    FILE* file;
    char filename[256];
    scanf("%s", filename);

    file = fopen(filename, "r");
    if (file == NULL) return NULL;
    fseek(file, 0, SEEK_END);
    int length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* string = malloc(sizeof(char) * (length + 1));
    char c;
    int i = 0;
    while ((c = fgetc(file)) != EOF)
    {
        string[i] = c;
        i++;
    }
    string[i] = '\0';
    *size = i;
    fclose(file);
    return string;
}
Token* t = NULL;

int place = 0;
int main(){
    t = malloc(sizeof(Token) * 100);
    init();
    int i,j=0;
    int a;
    
    char* str = read_file(&j);
    allTheTokens(str,&a,t,j);
    for (i = 0; i < a; i++)
    {
        printf("%s ", t[i].data);
    }
    lr_parse(t, a);
	return 0;
}
