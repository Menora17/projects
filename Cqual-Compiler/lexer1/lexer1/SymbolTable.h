#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tree.h"
typedef enum {
    SYMBOL_TYPE_VARIABLE,    // For variable declarations
    SYMBOL_TYPE_FUNCTION,    // For function declarations
    SYMBOL_TYPE_TYPE_SPECIFIER, // For type specifiers like int, String, double
    SYMBOL_TYPE_PARAMETER,   // For formal function parameters
    SYMBOL_TYPE_EXPRESSION,  // For generic expressions
    SYMBOL_TYPE_TERM,        // For terms within expressions
    SYMBOL_TYPE_FACTOR,      // For factors within terms
    SYMBOL_TYPE_CONDITION,   // For conditions in if, while, and for statements
    SYMBOL_TYPE_BLOCK,       // For blocks of statements
    SYMBOL_TYPE_STATEMENT,   // For generic statements (if applicable)
    SYMBOL_TYPE_IF_STATEMENT,// For if statements
    SYMBOL_TYPE_FOR_STATEMENT, // For for loops
    SYMBOL_TYPE_WHILE_STATEMENT, // For while loops
    SYMBOL_TYPE_FUNCTION_CALL, // For function call expressions
    SYMBOL_TYPE_RETURN_STATEMENT, // For return statements
    SYMBOL_TYPE_ASSIGNMENT, // For assignment statements
    SYMBOL_TYPE_DECLARATION // For declarations (variables and possibly functions)
} SymbolType;

typedef struct SymbolTableEntry {
    char* name;
    SymbolType type;
    char* dataType;
    char* scopeIdentifier; // String to represent the scope
    char* data;
    struct SymbolTableEntry* next;
} SymbolTableEntry;

#define SYMBOL_TABLE_SIZE 100

typedef struct SymbolTable {
    SymbolTableEntry* entries[SYMBOL_TABLE_SIZE];
} SymbolTable;

unsigned int hash(const char* key);
void symbolTableInit(SymbolTable* table);
SymbolTableEntry* symbolTableInsert(SymbolTable* table, const char* name, SymbolType type, const char* dataType,char* data, const int scopeIdentifier);
SymbolTableEntry* symbolTableLookup(SymbolTable* table, const char* name, const int scopeIdentifier);
void symbolTableSetParams(SymbolTable* table, SymbolTableEntry* params, const char* name, const int scopeIdentifier);
void symbolTableFree(SymbolTable* table);
void traverseASTAndBuildSymbolTable(ASTNode* node, SymbolTable* table);
void buildSymbolTableFromAST(ASTNode* root, SymbolTable* table);
void printSymbolTable(SymbolTable* table);
int checkentry(SymbolTable* table, char* name, int scope);
void findsymbols(SymbolTable* table, ASTNode* node);
char* traverseExpressionNode(ASTNode* node);
SymbolTableEntry* traverseFormalParametersNode(ASTNode* node);
SymbolTableEntry* findparams(SymbolTable* table, ASTNode* node);