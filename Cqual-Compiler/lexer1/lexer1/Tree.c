#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tree.h"




// Create a new Node
ASTNode* createASTNode(const char* type, const char* value,char* data,int scope) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = _strdup(type); // Copy the type
    node->value = value ? _strdup(value) : NULL; // Copy the value, if provided
    node->data = _strdup(data);
    node->children = NULL; // Initially, no children
    node->scope= scope;
    node->childrenCount = 0; // Initially, no children
    return node;
}
void addChild(ASTNode* parent, ASTNode* child) {
    if (!parent || !child) return; // Safety check

    // Resize the children array to accommodate the new child
    parent->childrenCount++;
    parent->children = (ASTNode**)realloc(parent->children, sizeof(ASTNode*) * parent->childrenCount);
    parent->children[parent->childrenCount - 1] = child; // Add the new child
}
void printAST(ASTNode* node, int level) {
    if (!node) return; // Base case

    // Indentation for levels
    for (int i = 0; i < level; i++) {
        printf("  ");
    }

    // Print the current node
    if(node->type)
     printf(" type: %s", node->type);
    if (node->value) {
        printf(" (%s)", node->value);
        printf(" scope: %d ", node->scope);
    }
    printf("\n");

    // Recursively print children
    for (int i = 0; i < node->childrenCount; i++) {
        printAST(node->children[i], level + 1);
    }
}
void freeAST(ASTNode* node) {
    if (!node) return; // Base case

    // Free children recursively
    for (int i = 0; i < node->childrenCount; i++) {
        freeAST(node->children[i]);
    }

    // Free the current node
    free(node->type);
    if (node->value) {
        free(node->value);
    }
    if (node->children) {
        free(node->children);
    }
    free(node);
}