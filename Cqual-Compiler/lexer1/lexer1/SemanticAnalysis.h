#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SymbolTable.h"

int checkVariableType(SymbolTable* table, const char* varName, const char* expectedType,  int scope);
void semanticAnalysis(ASTNode* node, SymbolTable* table,  int currentScope);
void perform(ASTNode* root);