#pragma once
typedef struct ASTNode {
    char* type; // Type of node (e.g., "Expression", "Statement")
    char* data;
    char* value; // Literal value, for nodes representing literals or identifiers
    int scope;
    struct ASTNode** children; // Array of pointers to child nodes
    int childrenCount; // Number of children
} ASTNode;

ASTNode* createASTNode(const char* type, const char* value,char* data,int scope);
void addChild(ASTNode* parent, ASTNode* child);
void printAST(ASTNode* node, int level);
void freeAST(ASTNode* node);