#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SymbolTable.h"



unsigned int hash(const char* key) {
    unsigned int hash = 0;
    for (; *key; key++) {
        hash = hash * 33 + *key;
    }
    return hash % SYMBOL_TABLE_SIZE;
}

void symbolTableInit(SymbolTable* table) {
    memset(table->entries, 0, sizeof(SymbolTableEntry*) * SYMBOL_TABLE_SIZE);
}

SymbolTableEntry* symbolTableInsert(SymbolTable* table, const char* name, SymbolType type, const char* dataType,char* data, const int scopeIdentifier) {
    unsigned int index = hash(name);
    SymbolTableEntry* entry = (SymbolTableEntry*)malloc(sizeof(SymbolTableEntry));
    if (!entry) {
        fprintf(stderr, "Memory allocation failed for symbol table entry.\n");
        exit(1);
    }
    entry->name = _strdup(name);
    entry->type = type;
    entry->dataType = _strdup(dataType);
    entry->data = _strdup(data);
    entry->scopeIdentifier = scopeIdentifier;
    entry->next = table->entries[index];
    table->entries[index] = entry;
    return entry;
}

SymbolTableEntry* symbolTableLookup(SymbolTable* table, const char* name, const int scopeIdentifier) {
    unsigned int index = hash(name);
    SymbolTableEntry* entry = table->entries[index];
    if (entry != NULL) {
        if (strcmp(entry->name, name) == 0 && entry->scopeIdentifier <= scopeIdentifier) {
            return entry; // Found
        }
    }
    for (int  i = 0; i < SYMBOL_TABLE_SIZE; i++)
    {
        if (table->entries[i] != NULL) {
            if (strcmp(table->entries[i]->name, name) == 0 && table->entries[i]->scopeIdentifier <= scopeIdentifier) {
                return entry; // Found
            }
            SymbolTableEntry* temp = table->entries[i]->next;
            while (temp!=NULL)
            {
                if (strcmp(temp->name, name) == 0 && temp->scopeIdentifier <= scopeIdentifier) {
                    return temp; // Found
                }
                temp = temp->next;
            }
        }
    }
    return NULL; // Not found
}

void symbolTableFree(SymbolTable* table) {
    for (int i = 0; i < SYMBOL_TABLE_SIZE; i++) {
        SymbolTableEntry* entry = table->entries[i];
        while (entry) {
            SymbolTableEntry* temp = entry;
            entry = entry->next;
            free(temp->name);
            free(temp->dataType);
            free(temp->data);
            free(temp);
        }
    }
}
void traverseDeclarationNode(ASTNode* node, SymbolTable* table) {
    if (!node) return;

    const char* varName = NULL;
    const char* dataType = NULL;
    const char* data = NULL;

    // Iterate over the children to find the variable name and data type
    for (int i = 0; i < node->childrenCount; i++) {
        ASTNode* child = node->children[i];

        if (strcmp(child->type, "Terminal") == 0 && strcmp(child->value, "ID") == 0) {
            // Next sibling node should be the variable name
            varName = child->data;
        }
        if (strcmp(child->type, "type_specifier") == 0) {
            dataType = child->children[0]->value;
        }
        if (strcmp(child->type, "expression") == 0) {
            // Handle the right side of the expression
            data = traverseExpressionNode(child);
        }
    }

    if (varName && dataType) {
        symbolTableInsert(table, varName, SYMBOL_TYPE_VARIABLE, dataType, data, node->scope);
    }
}

void traverseFunctionDeclarationNode(ASTNode* node, SymbolTable* table) {
    if (!node) return;

    const char* functionName = NULL;
    const char* returnType = NULL;
    SymbolTableEntry* params = NULL;

    // Iterate over the children to find the function name, return type, and parameters
    for (int i = 0; i < node->childrenCount; i++) {
        ASTNode* child = node->children[i];

        if (strcmp(child->type, "Terminal") == 0 && strcmp(child->value, "ID") == 0) {
            // Next sibling node should be the function name
            functionName = child->data;
        }
        if (strcmp(child->type, "type_specifier") == 0) {
            returnType = child->children[0]->value;
        }
        if (strcmp(child->type, "formal_parameters") == 0) {
            params = traverseFormalParametersNode(child,table);
            
        }
    }

    if (functionName && returnType) {
        symbolTableInsert(table, functionName, SYMBOL_TYPE_FUNCTION, returnType, functionName, node->scope);
        if (params != NULL )
            symbolTableSetParams(table, params, functionName, node->scope);
    }
}

char* traverseExpressionNode(ASTNode* node) {
    if (!node) return NULL;

    char* data = NULL;

    // Iterate over the children to traverse the expression
    for (int i = 0; i < node->childrenCount; i++) {
        ASTNode* child = node->children[i];

        for (int j = 0; j < child->childrenCount; j++) {
            ASTNode* paramChild = child->children[j];

            if (strcmp(paramChild->type, "factor") == 0) {
                if (data != NULL) {
                    data = realloc(data, sizeof(char) * (strlen(data) + strlen(paramChild->children[0]->children[0]->data) + 1));
                    strcat(data, paramChild->children[0]->children[0]->data);
                }
                else {
                    data = _strdup(paramChild->children[0]->children[0]->data);
                }
               
            }
            if (strcmp(paramChild->type, "Terminal") == 0) {
                if (data != NULL) {
                    data = realloc(data, sizeof(char) * (strlen(data) + strlen(paramChild->data) + 1));
                    strcat(data, paramChild->data);
                }
                
            }
            if (strcmp(paramChild->type, "term") == 0) {
                if (data != NULL&& paramChild->children[0]->children[0]->children[0]->data) {
                    data = realloc(data, sizeof(char) * (strlen(data) + strlen(paramChild->children[0]->children[0]->children[0]->data) + 1));
                    strcat(data, paramChild->children[0]->children[0]->children[0]->data);
                }
                if(data != NULL && paramChild->children[0]->children[0]->data) {
                    data = realloc(data, sizeof(char) * (strlen(data) + strlen(paramChild->children[0]->children[0]->data) + 1));
                    strcat(data, paramChild->children[0]->children[0]->data);
                }
               
            }
        }
        
    }

    return data;
}

SymbolTableEntry* traverseFormalParametersNode(ASTNode* node,SymbolTable* table) {
    if (!node) return NULL;

    SymbolTableEntry* params = NULL;
    const char* paramName = NULL;
    const char* paramType = NULL;
    // Iterate over the children to handle formal parameters
    for (int i = 0; i < node->childrenCount; i++) {
        ASTNode* child = node->children[i];

        //if (strcmp(child->type, "formal_parameters_tail") == 0) {
            // Handle each formal parameter node
            
            if (strcmp(child->type, "Terminal") == 0 && strcmp(child->value, "ID") == 0) {
                // Next sibling node should be the parameter name
                paramName = child->data;
            }
            if (strcmp(child->type, "type_specifier") == 0) {
                paramType = child->children[0]->value;
            }
            // Iterate over the children of formal parameter node
            for (int j = 0; j < child->childrenCount; j++) {
                ASTNode* paramChild = child->children[j];

                if (strcmp(paramChild->type, "Terminal") == 0 && strcmp(paramChild->value, "ID") == 0) {
                    // Next sibling node should be the parameter name
                    paramName = paramChild->data;
                }
                if (strcmp(paramChild->type, "type_specifier") == 0) {
                    paramType = paramChild->children[0]->value;
                }
            }

            // Insert the formal parameter into symbol table
            if (paramName && paramType &&checkentry(table, paramName,child->scope)==-1) {
                // Assuming SYMBOL_TYPE_PARAMETER is defined appropriately
                //SymbolTableEntry* entry = symbolTableInsert(table, paramName, SYMBOL_TYPE_PARAMETER, paramType, NULL, node->scope);
                // Add the parameter entry to the list of parameters
                // You may need to implement a linked list or array to store the parameter entries
                // Here, we assume adding the entry to a linked list
                unsigned int index = hash(paramName);
                SymbolTableEntry* entry = (SymbolTableEntry*)malloc(sizeof(SymbolTableEntry));
                if (!entry) {
                    fprintf(stderr, "Memory allocation failed for symbol table entry.\n");
                    exit(1);
                }
                entry->name = _strdup(paramName);
                entry->type = SYMBOL_TYPE_PARAMETER;
                entry->dataType = _strdup(paramType);
                entry->data = NULL;
                entry->scopeIdentifier = node->scope;
                entry->next = table->entries[index];
                entry->next = params;
                params = entry;
                paramName = NULL;
                paramType = NULL;
            }
        //}
    }

    return params;
}
void symbolTableSetParams(SymbolTable* table, SymbolTableEntry* params, const char* name, const int scopeIdentifier) {
    SymbolTableEntry* fun = symbolTableLookup(table, name, scopeIdentifier);
    for (int i = 0; i < SYMBOL_TABLE_SIZE; i++)
    {
        if (table->entries[i]&&strcmp(table->entries[i]->name, name) == 0) {
            table->entries[i]->next = params;
        }
    }
}

void traverseASTAndBuildSymbolTable(ASTNode* node, SymbolTable* table) {
    if (!node) return;

    if (strcmp(node->type, "function_declaration") == 0) {
        traverseFunctionDeclarationNode(node, table);
    }
    else if (strcmp(node->type, "declaration") == 0) {
        traverseDeclarationNode(node, table);
    }

    // Continue traversing the tree
    for (int i = 0; i < node->childrenCount; i++) {
        traverseASTAndBuildSymbolTable(node->children[i], table);
    }
}


void buildSymbolTableFromAST(ASTNode* root, SymbolTable* table) {
    traverseASTAndBuildSymbolTable(root, table); // Start the traversal from the root
}
void printSymbolTable(SymbolTable* table) {
    printf("Symbol Table:\n");
    for (int i = 0; i < SYMBOL_TABLE_SIZE; i++) {
        SymbolTableEntry* entry = table->entries[i];
        int j = 0;
        while (entry != NULL) {
            printf("Index: %d, Name: %s, Type: %s, DataType: %s, Data: %s, Scope: %d \n",
                i,
                entry->name,
                entry->type == SYMBOL_TYPE_VARIABLE ? "Variable" : (entry->type == SYMBOL_TYPE_PARAMETER ? "Parameter" : "Function"),
                entry->dataType,
                entry->data,
                entry->scopeIdentifier);
            entry = entry->next;
            
        }
    }
}
int checkentry(SymbolTable* table, char* name,int scope) {
    if (symbolTableLookup(table, name, scope) != NULL)
        return 1;
    return -1;
}

void findsymbols(SymbolTable* table, ASTNode* node) {
    if (node == NULL)
        return;
    const char* varName = NULL;
    const char* dataType = NULL;
    const char* data = NULL;
    if(node->childrenCount==0)
    if (strcmp(node->value, "ID") == 0) {
        // Next sibling node should be the variable name
        varName = node->data;
        dataType = node->type;
        
        if (varName && dataType&&checkentry(table,varName,node->scope)==-1) {
            symbolTableInsert(table, varName, SYMBOL_TYPE_FUNCTION, dataType,varName, node->scope);
        }
    }
    // Iterate over the children to find the variable name and data type
    for (int i = 0; i < node->childrenCount; i++) {
        ASTNode* child = node->children[i];
        //findsymbols(table,child)
        if (strcmp(child->type, "factor_base") == 0) {
            data = child->children[0]->data;
        }
        if (strcmp(child->type, "Terminal") == 0&& strcmp(child->value, "ID") == 0) {
            // Next siblchilding node should be the variable name
            varName = child->data;

        }
        if (strcmp(child->type, "type_specifier") == 0) {

            dataType = child->children[0]->value;
        }
        if (varName && dataType && checkentry(table, varName, node->scope) == -1) {
            symbolTableInsert(table, varName, SYMBOL_TYPE_VARIABLE, dataType,data, node->scope);
        }
    }
}
