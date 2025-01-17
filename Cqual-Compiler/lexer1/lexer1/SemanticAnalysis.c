#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "SymbolTable.h"
#include "SemanticAnalysis.h"
#include "Tree.h"



// Function to check the type of a variable
int checkVariableType(SymbolTable* table, const char* varName, const char* expectedType, int scope) {
    SymbolTableEntry* entry = symbolTableLookup(table, varName, scope);
    if (entry != NULL) {
        if(strcmp(entry->dataType, expectedType) == 0)
            return 1;
    }
    return 0;
}
int checkassigntment(SymbolTable* table, const char* varName, int scope) {
    SymbolTableEntry* entry = symbolTableLookup(table, varName, scope);
    if (strcmp(entry->dataType, "INT") == 0) {
        if (entry->data != NULL) {
            for (int i = 0; i < strlen(entry->data); i++)
            {
                if (!((entry->data[i] - '0') >= 0 && (entry->data[i] - '0') <= 9)) {
                    return 0;
                }
            }
        }
        return 1;
        if (entry->data == NULL)
            return 1;
    }
    if (strcmp(entry->dataType, "String") == 0 && entry->data[0] =='"') {
        
            if (entry->data[0] != '"'&& entry->data[strlen(entry->data)-1] != '"') {
                return 0;
            }
        
    }
    return 1;
}


void semanticAnalysis(ASTNode* node, SymbolTable* table,  int currentScope) {
    if (!node) return;

    if (strcmp(node->value, "ID")==0&&node->data) {
        SymbolTableEntry* entry = symbolTableLookup(table, node->data, currentScope);
        if (!entry) {
            printf("Semantic Error0: Variable %s is not declared in the current scope %d.\n", node->data, currentScope);
            return;
        }
        if (entry->type == SYMBOL_TYPE_VARIABLE) {
            // Additional checks for the variable can go here (type checks, etc.)
            if (checkVariableType(table, node->data,entry->dataType, node->scope) == 0) {
                printf("Semantic Error1: Variable %s is not the correct type in the current scope %d.\n", node->data, currentScope);
            }
            else if (checkassigntment(table, node->data,node->scope) == 0) {
                printf("Semantic Error2: Variable %s is not the correct type in the current scope %d.\n", node->data, currentScope);
            }
        }
        if (entry->type == SYMBOL_TYPE_FUNCTION) {
            SymbolTableEntry* entry = symbolTableLookup(table, node->data, currentScope);
            if (!entry) {
                printf("Semantic Error: function %s is not declared.\n", node->data);
            }
        }
    }
    if (strcmp(node->type, "function_call") == 0) {
        int j = 0,a=0;
        SymbolTableEntry* entry = symbolTableLookup(table, node->children[node->childrenCount-1]->data, currentScope);
        int count = 0;
        if (!entry) {
            printf("Semantic Error: function %s is not declared.\n", node->children[node->childrenCount - 1]->data);
        }
        while (a+1<node->childrenCount) 
        {    
            a++;
            if (strcmp(node->children[a]->type, "parameters") == 0) {
                j = a;
            }

        }
        a = 0;
        while (a + 1 < node->children[j]->childrenCount)
        {
            a++;
            if (strcmp(node->children[j]->children[a]->type, "expression") == 0) {
                count++;
            }

        }
        for (int i = 0; i < node->children[j]->childrenCount; i++)
        {
            
                ASTNode* child = node->children[j]->children[i];
                /*for (int j = 0; j < child->childrenCount; j++)
                {
                    child = child->children[j];*/
                    if (strcmp(child->type, "expression") == 0) {
                        count++;
                    }
               // }
                    
           
        }
        while (entry->next!=NULL)
        {
            count--;
            entry = entry->next;
        }
        if (count != 0) {
            printf("Semantic Error: not the correct amount of parameters in the function %s.\n", node->children[node->childrenCount - 1]->data);
        }
    }
    // Recursively analyze children nodes
    for (int i = 0; i < node->childrenCount; i++) {
        semanticAnalysis(node->children[i], table, node->children[i]->scope);
    }
}
// Main function to kick off the analysis
void perform(ASTNode* root) {
    SymbolTable table;
    symbolTableInit(&table);
    buildSymbolTableFromAST(root, &table);
    printSymbolTable(&table);
    semanticAnalysis(root, &table, 0); // Start analysis from the root with global scope
    symbolTableFree(&table);
}
