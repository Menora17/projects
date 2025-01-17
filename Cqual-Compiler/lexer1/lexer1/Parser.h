#pragma once
#include "Lexer.h"
#include "stack.h"
#include "SymbolTable.h"


typedef struct {
    char type[4]; // 'r' for strings starting with 'r', 's' for strings starting with 's', 'i' for integers

} MatrixCell;
typedef struct {
    int row;
    int col;
    char data[5];
}insert;
typedef struct {
    const char* non_terminal;
    int reduction_number;
} ReductionRule;

stack s;
SymbolTable st;
int input_pos;
int current_state;
char action[10]; // Increase size if necessary for your actions
char* scope;
char** scopes;
int numscopes;


int pos_terminal(char* str);
int pos_nonterminal(char* str);
int  funShift(Token* tokens, int input_size, char* token);
int funReduce(Token* tokens, int input_size, char* token);
int funAccept(Token* tokens, int input_size, char* token);
int funError(Token* tokens, int input_size, char* token);
void lr_parse(Token* tokens , int input_size);
void init();