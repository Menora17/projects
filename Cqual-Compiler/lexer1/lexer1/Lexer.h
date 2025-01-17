#pragma once


typedef enum
{
    EPSILON, // ε
    ID,
    LPAREN, // (
    RPAREN, // )
    LBRACE, // {
    RBRACE, // }
    COMMA, // ,
    IF,
    INT,
    String,
    WHILE,
    FOR,
    RETURN,
    DOUBLE,
    THEN,
    ELSE,
    NUMBER,
    STRING,
    NEQ, // !=
    GT, // >
    LT, // <
    GTE, // >=
    LTE, // <=
    EQ, // ==
    ASSIGN, // =
    PLUS, // +
    MINUS, // -
    STAR, // *
    SLASH, // /
    SEMICOLON, // ;
    END_OF_INPUT // $
}TokensType;

typedef enum {
    STATE_INITIAL,
    STATE_IN_STRING,
    STATE_IN_KEYWORD,
    STATE_IN_IDENTIFIER,
    STATE_IN_NUMBER,
    STATE_IN_DOUBLE,
    STATE_IN_OPERATOR,
    STATE_IN_SEPARATOR,
    STATE_IN_SEMICOLON
} State;


typedef struct {
    TokensType type;
    char* data;
    int linenum;
    int wordnum;
}Token;
void allTheTokens(char str[], int* items, Token alltokens[], int size);
State transition(State currentState, char input);
int isKeyword(char* str);

// Constants
#define NUM_KEYWORDS 8



// Token processing functions
char* processStringToken(char str[], int* i, int* a, State* current);
void processStringTokenResult(char* keyword, Token Tokens[], int* j, int* tokens, int* b, int line, int* a, int* i);
void processNumberToken(char str[], int* i, int* a, State* current, Token Tokens[], int* j, int* tokens, int* b, int line);
void processOperatorToken(char str[], int* i, Token Tokens[], int* j, int* tokens, int* b, int line, State* current);
void processSeparatorToken(char str[], int* i, Token Tokens[], int* j, int* tokens, int* b, int line, State* current);
void processSemicolonToken(char str[], int* i, Token Tokens[], int* j, int* tokens, int* b, int line, State* current);

// Print functions
void printTokens(Token Tokens[], int tokens);

int posOp(char* str);

// Copy tokens from source to destination
void copyTokens(Token destination[], Token source[], int tokens);
