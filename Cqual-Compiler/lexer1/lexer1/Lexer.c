#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Lexer.h"


char* keywords[] = { "if", "int","string", "while", "for", "return", "double","then", "else"};

void allTheTokens(char str[], int* items, Token alltokens[], int size) {
    int tokens = 0;
    int i, j = 0, a = 0, b = 0;
    int line = 0;
    State current = STATE_INITIAL;

    Token Tokens[100];
    char* keyword;

    for (i = 0; i < size; i++) {
        if (str[i] == '\n') {
            line++;
            b = 0;
            i++;
        }

        current = transition(current, str[i]);

        switch (current) {
        case STATE_IN_STRING:
            keyword = processStringToken(str, &i, &a, &current);
            processStringTokenResult(keyword, Tokens, &j, &tokens, &b, line,&a,&i);
            break;
        case STATE_IN_NUMBER:
            processNumberToken(str, &i, &a, &current, Tokens, &j, &tokens, &b, line);
            break;
        case STATE_IN_OPERATOR:
            processOperatorToken(str, &i, Tokens, &j, &tokens, &b, line, &current);
            break;
        case STATE_IN_SEPARATOR:
            processSeparatorToken(str, &i, Tokens, &j, &tokens, &b, line, &current);
            break;
        case STATE_IN_SEMICOLON:
            processSemicolonToken(str, &i, Tokens, &j, &tokens, &b, line, &current);
            break;
        default:
            break;
        }

        current = STATE_INITIAL;
    }

    

    printTokens(Tokens, tokens);

    *items = tokens;
    copyTokens(alltokens, Tokens, tokens);
}

/// <summary>
/// 
/// </summary>
/// <param name="str"></param>
/// <param name="i"></param>
/// <param name="a"></param>
/// <param name="current"></param>
/// <returns></returns>
char* processStringToken(char str[], int* i, int* a, State* current) {
    char* keyword = NULL;
    
    while (*current == STATE_IN_STRING) {
        keyword = (char*)realloc(keyword, sizeof(char) * ((*a)+1));
        keyword[*a+1] = '\0';
        keyword[*a] = str[*i];
        (*a)++;
        (*i)++;
        *current = transition(*current, str[*i]);
    }

    return keyword;
}
State transition(State currentState, char input) {
    int index,  startCondition,  endCondition;
    State nextState;
    static const State transitions[][128] = {
        [STATE_INITIAL] = { STATE_IN_STRING, STATE_IN_NUMBER, STATE_IN_OPERATOR, STATE_INITIAL, STATE_IN_SEMICOLON,STATE_IN_SEPARATOR },
        [STATE_IN_STRING] = { STATE_IN_STRING, STATE_INITIAL },
        [STATE_IN_NUMBER] = { STATE_IN_NUMBER, STATE_IN_DOUBLE, STATE_INITIAL },
        [STATE_IN_DOUBLE] = { STATE_IN_DOUBLE, STATE_INITIAL },
        [STATE_IN_OPERATOR] = { STATE_INITIAL },
        [STATE_IN_SEPARATOR] = { STATE_INITIAL },
        [STATE_IN_SEMICOLON] = { STATE_INITIAL },
    };

    static const int charConditions[][3] = {
        { 'A', 'Z', STATE_IN_STRING },
        { 'a', 'z', STATE_IN_STRING },
        { '0', '9', STATE_IN_NUMBER },
        { '.', '.', STATE_IN_DOUBLE },
        { ';', ';', STATE_IN_SEMICOLON },
        { '=', '=', STATE_IN_OPERATOR },
        { '<', '<', STATE_IN_OPERATOR },
        { '>', '>', STATE_IN_OPERATOR },
        { '!', '!', STATE_IN_OPERATOR },
        { '+', '+', STATE_IN_OPERATOR },
        { '-', '-', STATE_IN_OPERATOR },
        { '*', '*', STATE_IN_OPERATOR },
        { '/', '/', STATE_IN_OPERATOR },
        { '{', '{', STATE_IN_SEPARATOR },
        { '}', '}', STATE_IN_SEPARATOR },
        { '(', '(', STATE_IN_SEPARATOR },
        { ')', ')', STATE_IN_SEPARATOR },
        { '\'', '\'', STATE_IN_STRING },
        { '"', '"', STATE_IN_STRING },
        { ',', ',', STATE_IN_SEPARATOR },
    };

     index = (unsigned char)input;

    for (int j = 0; j < sizeof(charConditions) / sizeof(charConditions[0]); ++j) {
        startCondition = charConditions[j][0];
        endCondition = charConditions[j][1];
        nextState = (State)charConditions[j][2];

        if (index >= startCondition && index <= endCondition) {
            return nextState;
        }
    }

    return transitions[currentState][index];
}
void processStringTokenResult(char* keyword, Token Tokens[], int* j, int* tokens, int* b, int line,int* a,int *i) {
    Tokens[*j].data = malloc(sizeof(char) * (*a));
    strcpy(Tokens[*j].data, keyword);

    if (strcmp(Tokens[*j].data,"end")==0) {
        Tokens[*j].wordnum = ++(*b);
        Tokens[*j].linenum = line;
        Tokens[*j].type = EPSILON;
        (*j)++;
        (*tokens)++;
    }

    else if (isKeyword(keyword)!=-1) {
        Tokens[*j].wordnum = ++(*b);
        Tokens[*j].linenum = line;
        Tokens[*j].type = IF +isKeyword(keyword);
        (*j)++;
        (*tokens)++;
    }
    else if (keyword[0] == '"') {
        Tokens[*j].wordnum = ++(*b);
        Tokens[*j].linenum = line;
        Tokens[*j].type = STRING;
        (*j)++;
        (*tokens)++;
    }
    else {
        Tokens[*j].wordnum = ++(*b);
        Tokens[*j].linenum = line;
        Tokens[*j].type = ID;
        (*j)++;
        (*tokens)++;
    }

    if (*a >= 1)
        (*i)--;
    *a = 0;
}

void processNumberToken(char str[], int* i, int* a, State* current, Token Tokens[], int* j, int* tokens, int* b, int line) {
    int check = 0;
    int flag = 0;
    Tokens[*j].data = NULL;
    while (*current == STATE_IN_NUMBER) {
        Tokens[*j].data = (char*)realloc(Tokens[*j].data, sizeof(char) * (check + 1) + 1);
        Tokens[*j].data[check + 1] = '\0';
        Tokens[*j].data[check] = str[*i];
        (*i)++;
        check++;
        *current = transition(*current, str[*i]);
        flag++;
    }

    if (str[*i] == '.') {
        Tokens[*j].data[check++] = str[*i];
        *current = transition(*current, str[++(*i)]);
        flag = 0;
        while (*current == STATE_IN_DOUBLE) {
            Tokens[*j].data = (char*)realloc(Tokens[*j].data, sizeof(char) * (check + 1) + 1);
            Tokens[*j].data[check] = str[*i];
            Tokens[*j].data[check + 1] = '\0';
            (*i)++;
            check++;
            flag++;
            *current = transition(*current, str[*i + 1]);
        }
    }
   
    Tokens[*j].type = NUMBER;
    if (flag >= 1)
        (*i)--;

    Tokens[*j].wordnum = ++(*b);
    Tokens[*j].linenum = line;

    (*j)++;
    (*tokens)++;
    *current = transition(*current, str[*i]);
}

void processOperatorToken(char str[], int* i, Token Tokens[], int* j, int* tokens, int* b, int line, State* current) {
    Tokens[*j].data = NULL;
    Tokens[*j].data = (char*)realloc(Tokens[*j].data, sizeof(char) * 2 );
    Tokens[*j].data[0] = str[*i];
    Tokens[*j].data[1] = '\0';
    Tokens[*j].wordnum = ++(*b);
    Tokens[*j].linenum = line;
    Tokens[*j].type = NEQ + posOp(Tokens[*j].data);
    (*j)++;
    (*tokens)++;
    *current = transition(*current, str[*i]);
}

void processSeparatorToken(char str[], int* i, Token Tokens[], int* j, int* tokens, int* b, int line, State* current) {
    Tokens[*j].data = NULL;
    Tokens[*j].data = (char*)realloc(Tokens[*j].data, sizeof(char) * 2);
    Tokens[*j].wordnum = ++(*b);
    Tokens[*j].data[0] = str[*i];
    Tokens[*j].data[1] = '\0';
    Tokens[*j].linenum = line;
    Tokens[*j].type = LPAREN+posSep(Tokens[*j].data);

    (*j)++;
    (*tokens)++;
    *current = transition(*current, str[*i]);
}

void processSemicolonToken(char str[], int* i, Token Tokens[], int* j, int* tokens, int* b, int line, State* current) {
    Tokens[*j].data = NULL;
    Tokens[*j].data = (char*)realloc(Tokens[*j].data, sizeof(char) * 2);
    Tokens[*j].wordnum = ++(*b);
    Tokens[*j].data[0] = str[*i];
    Tokens[*j].data[1] = '\0';
    Tokens[*j].linenum = line;
    Tokens[*j].type = SEMICOLON;
    (*j)++;
    (*tokens)++;
    *current = transition(*current, str[*i]);
}

void printTokens(Token Tokens[], int tokens) {
    int i;
    for (i = 0; i < tokens; i++) {
        printf("Token %d: %s , State: %d\n", i + 1, Tokens[i].data, Tokens[i].type);
    }
}

int isKeyword(char* str) {
    int i;
    for ( i = 0; i < sizeof(keywords)/sizeof(keywords[0]); i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return i;
        }
    }
    return -1;
}
int posSep(char* str) {
    static char* sep[] = { "(",")","{","}",","};
    int i;
    for (i = 0; i < sizeof(sep) / sizeof(sep[0]); i++) {
        if (strcmp(str, sep[i]) == 0) {
            return i;
        }
    }
    return -1;
}

int posOp(char* str) {
    int i;
    static char* ops[] = { "!=",
     ">",
     "<",
     ">=",
     "<=",
     "==",
     "=","+","-","*","/"};
    for (i = 0; i < sizeof(ops)/sizeof(ops[0]); i++) {
        if (strcmp(str, ops[i]) == 0) {
            return i;
        }
    }
    return -1;
}

void copyTokens(Token destination[], Token source[], int tokens) {
    int i;
    for ( i = 0; i < tokens; i++) {
        destination[i] = source[i];
    }
}