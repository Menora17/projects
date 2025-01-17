#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

#define ROWS 105
#define COLS 30

// Structure to hold the matrix data

MatrixCell matrix[ROWS][COLS];
int goto_table[ROWS][23];

ReductionRule reduction_rules[] = {
    {"S'", 1},
 {"S'", 0},
 {"statement_list", 2},
 {"statement_list", 1},
 {"function_declaration", 6},
 {"formal_parameters", 3},
 {"formal_parameters_tail", 4},
 {"formal_parameters_tail", 1},
 {"parameters", 2},
 {"parameters_tail", 3},
 {"parameters_tail", 1},
 {"block", 3},
 {"statement", 1},
 {"statement", 1},
 {"statement", 1},
 {"statement", 1},
 {"statement", 1},
 {"statement", 1},
 {"statement", 1},
 {"statement", 1},
 {"statement", 1},
 {"declaration", 3},
 {"declaration", 5},
 {"assignment", 4},
 {"function_call", 4},
 {"if_statement", 4},
 {"for_statement", 9},
 {"while_statement", 5},
 {"return_statement", 3},
 {"expression", 3},
 {"expression", 3},
 {"expression", 1},
 {"term", 3},
 {"term", 3},
 {"term", 1},
 {"factor", 1},
 {"factor", 3},
 {"factor", 1},
 {"factor_base", 1},
 {"factor_base", 1},
 {"type_specifier", 1},
 {"type_specifier", 1},
 {"type_specifier", 1},
 {"condition", 3},
 {"condition", 3},
 {"condition", 3},
 {"condition", 3},
 {"condition", 3},
 {"condition", 3},
 {"expression_statement", 2} };
int pos_terminal(char* str) {
    static char* terminals_ordered[] = {
        "ε",        // Empty string (often used to represent an empty production)
    "ID",       // Identifier
    "(",        // Open parenthesis
    ")",        // Close parenthesis
    ",",        // Comma
    "{",        // Open curly brace
    "}",        // Close curly brace
    ";",        // Semicolon
    "=",        // Assignment operator
    "IF",       // 'if' keyword
    "THEN",     // 'then' keyword, though not typically used in C-like languages
    "FOR",      // 'for' keyword
    "WHILE",    // 'while' keyword
    "RETURN",   // 'return' keyword
    "+",        // Addition operator
    "-",        // Subtraction operator
    "*",        // Multiplication operator
    "/",        // Division operator
    "number",   // Numeric literal
    "string",   // String literal
    "INT",      // 'int' keyword for integer type specifier
    "String",   // 'String' type specifier, though in C typically 'char*' is used
    "double",   // 'double' keyword for double-precision floating-point type specifier
    "==",       // Equality comparison operator
    "!=",       // Inequality comparison operator
    ">",        // Greater than operator
    "<",        // Less than operator
    ">=",       // Greater than or equal to operator
    "<=",       // Less than or equal to operator
    "$"         // End of input symbol
    };
    for (int i = 0; i < sizeof(terminals_ordered) / sizeof(terminals_ordered[0]); i++)
    {
        if (strcmp(str, terminals_ordered[i]) == 0)
            return i;
    }
    return -1;
}
int pos_nonterminal(char* str) {
    static const char* non_terminals[] = {
    "S'",
        "statement_list",
        "function_declaration",
        "formal_parameters",
        "formal_parameters_tail",
        "parameters",
        "parameters_tail",
        "block",
        "statement",
        "declaration",
        "assignment",
        "function_call",
        "if_statement",
        "for_statement",
        "while_statement",
        "return_statement",
        "expression",
        "term",
        "factor",
        "factor_base",
        "type_specifier",
        "condition",
        "expression_statement"
    };
    for (int i = 0; i < sizeof(non_terminals) / sizeof(non_terminals[0]); i++)
    {
        if (strcmp(str, non_terminals[i]) == 0)
            return i;
    }
    return -1;
}
char* symbols[] = {  "ε",
    "ID",
     "(",
     ")",
     "{",
     "}",
     ",",
    "IF",
    "INT",
    "String",
    "WHILE",
    "FOR",
    "RETURN",
    "DOUBLE",
    "THEN",
    "ELSE",
    "number",
    "string",
     "!=",
     ">",
    "<",
    ">=",
    "<=",
    "==",
    "=",
    "+",
     "-",
     "*",
    "/",
    ";",
    "$" };

/// <summary>
/// 
/// </summary>
/// <param name="tokens"></param>
/// <param name="input_size"></param>
/// <param name="token"></param>
/// <returns></returns>
int  funShift(Token* tokens, int input_size, char* token) { // Shift
    int nextState = atoi(action + 1);
    if (strcmp(token, "WHILE") == 0 || strcmp(token, "FOR") == 0)
        scope = _strdup(token);
    if (strcmp(token, "{") == 0) {
        numscopes++;

    }
    if (strcmp(token, "(") == 0) {
        int temp = stack_pop(&s);
        scope = _strdup(((ASTNode*)stack_top(&s))->data);
        stack_push(&s, temp);
        numscopes++;

    }
    ASTNode* newNode;
    if (input_pos < input_size)
        newNode = createASTNode("Terminal", token, tokens[input_pos].data, numscopes - 1);
    else
        newNode = createASTNode("Terminal", token, token, numscopes - 1);
    stack_push(&s, newNode);
    //printAST(newNode, 0);

    stack_push(&s, nextState); // Push next state
    input_pos++;
    current_state = nextState;
    return 1;
}
 
int funReduce(Token* tokens, int input_size, char* token) {  // Reduce
    int ruleIndex = atoi(action + 1);
    int popCount = reduction_rules[ruleIndex].reduction_number; // Assuming each entry in the stack is a state-symbol pair
    if (strcmp(token, "}") == 0 && numscopes > 1) {
         numscopes--;
    }

    ASTNode* reducedNode = createASTNode(reduction_rules[ruleIndex].non_terminal, token, NULL, numscopes-1);
    // Pop states and symbols from the stack as per the reduction rule
    for (int i = 0; i < popCount; i++) {
        stack_pop(&s);
        ASTNode* Node = (ASTNode*)stack_pop(&s);
        addChild(reducedNode, Node);
    }
    int topState;
    // Peek the new top state after popping

    topState = stack_top(&s);
    //printf("%s", stack_top(&s));


    // Use the goto_table to find the next state based on the non-terminal and top state
    int nextState = goto_table[topState][pos_nonterminal(reducedNode->type)];

    stack_push(&s, reducedNode); // Push the non-terminal resulted from reduction

    //printAST(reducedNode, 0);
    stack_push(&s, nextState); // Push the state obtained from goto_table
    //printf("%s", stack_top(&s));
    current_state = nextState; // Update current state
    return 1;
}

int funAccept(Token* tokens, int input_size, char* token) {
    printf("\nParsing successful\n");
    stack_pop(&s);
    printAST(stack_top(&s), 0);
    
    perform(stack_top(&s));
    return 0;
}

int funError(Token* tokens, int input_size, char* token) {
    fprintf(stderr, "\nSyntax error\n");
    return 0;
}

void lr_parse(Token* tokens, int input_size) {
    numscopes = 1;
    
   
    scopes = malloc(sizeof(char*));
    symbolTableInit(&st);
    stack_init(&s);
    

    typedef int (*pFun)(Token* , int , char* );
    char possibales[] = "sraE";
    pFun arFun[] = { funShift, funReduce, funAccept, funError };
    int flagRun = 1;
    while (flagRun) {
        char* token = (input_pos < input_size) ? symbols[tokens[input_pos].type] : "$";
        
        strcpy(action, matrix[current_state][pos_terminal(token)].type);
        
        char* pos = strchr(possibales, action[0]);
        flagRun =  arFun[pos - possibales](tokens, input_size, token);
    }
}

/// <summary>
/// 
/// </summary>
void init() {
    // Initialize the matrix with default values


    insert insert2[][1] = { {0,0,"s3"},
            {0,1,"s14"},
            {0,2,"s25"},
            {0,9,"s15"},
            {0,11,"s16"},
            {0,12,"s17"},
            {0,13,"s18"},
            {0,18,"s27"},
            {0,19,"s28"},
            {0,20,"s20"},
            {0,21,"s21"},
            {0,22,"s22"},
            {1,29,"acc"},
            {2,0,"s3"},
            {2,1,"s14"},
            {2,2,"s25"},
            {2,9,"s15"},
            {2,11,"s16"},
            {2,12,"s17"},
            {2,13,"s18"},
            {2,18,"s27"},
            {2,19,"s28"},
            {2,20,"s20"},
            {2,21,"s21"},
            {2,22,"s22"},
            {13,1,"s30"},
            {14,2,"s32"},
            {14,8,"s31"},
            {15,1,"s35"},
            {15,2,"s25"},
            {15,18,"s27"},
            {15,19,"s28"},
            {16,2,"s36"},
            {17,2,"s37"},
            {18,1,"s35"},
            {18,2,"s25"},
            {18,18,"s27"},
            {18,19,"s28"},
            {19,7,"s39"},
            {19,14,"s40"},
            {19,15,"s41"},
            {23,16,"s42"},
            {23,17,"s43"},
            {25,1,"s35"},
            {25,2,"s25"},
            {25,18,"s27"},
            {25,19,"s28"},
            {30,2,"s45"},
            {30,7,"s46"},
            {30,8,"s47"},
            {31,1,"s35"},
            {31,2,"s25"},
            {31,18,"s27"},
            {31,19,"s28"},
            {32,1,"s35"},
            {32,2,"s25"},
            {32,18,"s27"},
            {32,19,"s28"},
            {33,10,"s51"},
            {34,14,"s40"},
            {34,15,"s41"},
            {34,23,"s52"},
            {34,24,"s53"},
            {34,25,"s54"},
            {34,26,"s55"},
            {34,27,"s56"},
            {34,28,"s57"},
            {36,1,"s59"},
            {37,1,"s35"},
            {37,2,"s25"},
            {37,18,"s27"},
            {37,19,"s28"},
            {38,7,"s61"},
            {38,14,"s40"},
            {38,15,"s41"},
            {40,1,"s35"},
            {40,2,"s25"},
            {40,18,"s27"},
            {40,19,"s28"},
            {41,1,"s35"},
            {41,2,"s25"},
            {41,18,"s27"},
            {41,19,"s28"},
            {42,1,"s35"},
            {42,2,"s25"},
            {42,18,"s27"},
            {42,19,"s28"},
            {43,1,"s35"},
            {43,2,"s25"},
            {43,18,"s27"},
            {43,19,"s28"},
            {44,3,"s66"},
            {44,14,"s40"},
            {44,15,"s41"},
            {45,20,"s20"},
            {45,21,"s21"},
            {45,22,"s22"},
            {47,1,"s35"},
            {47,2,"s25"},
            {47,18,"s27"},
            {47,19,"s28"},
            {48,7,"s70"},
            {48,14,"s40"},
            {48,15,"s41"},
            {49,3,"s71"},
            {50,0,"s74"},
            {50,4,"s73"},
            {50,14,"s40"},
            {50,15,"s41"},
            {51,1,"s14"},
            {51,2,"s25"},
            {51,9,"s15"},
            {51,11,"s16"},
            {51,12,"s17"},
            {51,13,"s18"},
            {51,18,"s27"},
            {51,19,"s28"},
            {51,20,"s20"},
            {51,21,"s21"},
            {51,22,"s22"},
            {52,1,"s35"},
            {52,2,"s25"},
            {52,18,"s27"},
            {52,19,"s28"},
            {53,1,"s35"},
            {53,2,"s25"},
            {53,18,"s27"},
            {53,19,"s28"},
            {54,1,"s35"},
            {54,2,"s25"},
            {54,18,"s27"},
            {54,19,"s28"},
            {55,1,"s35"},
            {55,2,"s25"},
            {55,18,"s27"},
            {55,19,"s28"},
            {56,1,"s35"},
            {56,2,"s25"},
            {56,18,"s27"},
            {56,19,"s28"},
            {57,1,"s35"},
            {57,2,"s25"},
            {57,18,"s27"},
            {57,19,"s28"},
            {58,7,"s82"},
            {59,8,"s31"},
            {60,3,"s83"},
            {62,16,"s42"},
            {62,17,"s43"},
            {63,16,"s42"},
            {63,17,"s43"},
            {67,3,"s84"},
            {68,1,"s85"},
            {69,7,"s86"},
            {69,14,"s40"},
            {69,15,"s41"},
            {73,1,"s35"},
            {73,2,"s25"},
            {73,18,"s27"},
            {73,19,"s28"},
            {76,14,"s40"},
            {76,15,"s41"},
            {77,14,"s40"},
            {77,15,"s41"},
            {78,14,"s40"},
            {78,15,"s41"},
            {79,14,"s40"},
            {79,15,"s41"},
            {80,14,"s40"},
            {80,15,"s41"},
            {81,14,"s40"},
            {81,15,"s41"},
            {82,1,"s35"},
            {82,2,"s25"},
            {82,18,"s27"},
            {82,19,"s28"},
            {83,5,"s90"},
            {84,5,"s90"},
            {85,0,"s94"},
            {85,4,"s93"},
            {87,0,"s74"},
            {87,4,"s73"},
            {87,14,"s40"},
            {87,15,"s41"},
            {88,7,"s96"},
            {90,0,"s3"},
            {90,1,"s14"},
            {90,2,"s25"},
            {90,9,"s15"},
            {90,11,"s16"},
            {90,12,"s17"},
            {90,13,"s18"},
            {90,18,"s27"},
            {90,19,"s28"},
            {90,20,"s20"},
            {90,21,"s21"},
            {90,22,"s22"},
            {93,20,"s20"},
            {93,21,"s21"},
            {93,22,"s22"},
            {96,1,"s35"},
            {96,2,"s25"},
            {96,18,"s27"},
            {96,19,"s28"},
            {97,6,"s100"},
            {98,1,"s101"},
            {99,3,"s102"},
            {99,14,"s40"},
            {99,15,"s41"},
            {101,0,"s94"},
            {101,4,"s93"},
            {102,5,"s90"} };
                insert insert3[][1] = {
                 {3,6,"r3"},
                {3,29,"r3"},
                {4,0,"r12"},
                {4,1,"r12"},
                {4,2,"r12"},
                {4,9,"r12"},
                {4,11,"r12"},
                {4,12,"r12"},
                {4,13,"r12"},
                {4,18,"r12"},
                {4,19,"r12"},
                {4,20,"r12"},
                {4,21,"r12"},
                {4,22,"r12"},
                {5,0,"r13"},
                {5,1,"r13"},
                {5,2,"r13"},
                {5,9,"r13"},
                {5,11,"r13"},
                {5,12,"r13"},
                {5,13,"r13"},
                {5,18,"r13"},
                {5,19,"r13"},
                {5,20,"r13"},
                {5,21,"r13"},
                {5,22,"r13"},
                {6,0,"r14"},
                {6,1,"r14"},
                {6,2,"r14"},
                {6,9,"r14"},
                {6,11,"r14"},
                {6,12,"r14"},
                {6,13,"r14"},
                {6,18,"r14"},
                {6,19,"r14"},
                {6,20,"r14"},
                {6,21,"r14"},
                {6,22,"r14"},
                {7,0,"r15"},
                {7,1,"r15"},
                {7,2,"r15"},
                {7,9,"r15"},
                {7,11,"r15"},
                {7,12,"r15"},
                {7,13,"r15"},
                {7,18,"r15"},
                {7,19,"r15"},
                {7,20,"r15"},
                {7,21,"r15"},
                {7,22,"r15"},
                {8,0,"r16"},
                {8,1,"r16"},
                {8,2,"r16"},
                {8,9,"r16"},
                {8,11,"r16"},
                {8,12,"r16"},
                {8,13,"r16"},
                {8,18,"r16"},
                {8,19,"r16"},
                {8,20,"r16"},
                {8,21,"r16"},
                {8,22,"r16"},
                {9,0,"r17"},
                {9,1,"r17"},
                {9,2,"r17"},
                {9,9,"r17"},
                {9,11,"r17"},
                {9,12,"r17"},
                {9,13,"r17"},
                {9,18,"r17"},
                {9,19,"r17"},
                {9,20,"r17"},
                {9,21,"r17"},
                {9,22,"r17"},
                {10,0,"r18"},
                {10,1,"r18"},
                {10,2,"r18"},
                {10,9,"r18"},
                {10,11,"r18"},
                {10,12,"r18"},
                {10,13,"r18"},
                {10,18,"r18"},
                {10,19,"r18"},
                {10,20,"r18"},
                {10,21,"r18"},
                {10,22,"r18"},
                {11,0,"r19"},
                {11,1,"r19"},
                {11,2,"r19"},
                {11,9,"r19"},
                {11,11,"r19"},
                {11,12,"r19"},
                {11,13,"r19"},
                {11,18,"r19"},
                {11,19,"r19"},
                {11,20,"r19"},
                {11,21,"r19"},
                {11,22,"r19"},
                {12,0,"r20"},
                {12,1,"r20"},
                {12,2,"r20"},
                {12,9,"r20"},
                {12,11,"r20"},
                {12,12,"r20"},
                {12,13,"r20"},
                {12,18,"r20"},
                {12,19,"r20"},
                {12,20,"r20"},
                {12,21,"r20"},
                {12,22,"r20"},
                {14,7,"r35"},
                {14,14,"r35"},
                {14,15,"r35"},
                {14,16,"r35"},
                {14,17,"r35"},
                {20,1,"r40"},
                {21,1,"r41"},
                {22,1,"r42"},
                {23,0,"r31"},
                {23,3,"r31"},
                {23,4,"r31"},
                {23,7,"r31"},
                {23,10,"r31"},
                {23,14,"r31"},
                {23,15,"r31"},
                {23,23,"r31"},
                {23,24,"r31"},
                {23,25,"r31"},
                {23,26,"r31"},
                {23,27,"r31"},
                {23,28,"r31"},
                {24,0,"r34"},
                {24,3,"r34"},
                {24,4,"r34"},
                {24,7,"r34"},
                {24,10,"r34"},
                {24,14,"r34"},
                {24,15,"r34"},
                {24,16,"r34"},
                {24,17,"r34"},
                {24,23,"r34"},
                {24,24,"r34"},
                {24,25,"r34"},
                {24,26,"r34"},
                {24,27,"r34"},
                {24,28,"r34"},
                {26,0,"r37"},
                {26,3,"r37"},
                {26,4,"r37"},
                {26,7,"r37"},
                {26,10,"r37"},
                {26,14,"r37"},
                {26,15,"r37"},
                {26,16,"r37"},
                {26,17,"r37"},
                {26,23,"r37"},
                {26,24,"r37"},
                {26,25,"r37"},
                {26,26,"r37"},
                {26,27,"r37"},
                {26,28,"r37"},
                {27,0,"r38"},
                {27,3,"r38"},
                {27,4,"r38"},
                {27,7,"r38"},
                {27,10,"r38"},
                {27,14,"r38"},
                {27,15,"r38"},
                {27,16,"r38"},
                {27,17,"r38"},
                {27,23,"r38"},
                {27,24,"r38"},
                {27,25,"r38"},
                {27,26,"r38"},
                {27,27,"r38"},
                {27,28,"r38"},
                {28,0,"r39"},
                {28,3,"r39"},
                {28,4,"r39"},
                {28,7,"r39"},
                {28,10,"r39"},
                {28,14,"r39"},
                {28,15,"r39"},
                {28,16,"r39"},
                {28,17,"r39"},
                {28,23,"r39"},
                {28,24,"r39"},
                {28,25,"r39"},
                {28,26,"r39"},
                {28,27,"r39"},
                {28,28,"r39"},
                {29,6,"r2"},
                {29,29,"r2"},
                {35,0,"r35"},
                {35,3,"r35"},
                {35,4,"r35"},
                {35,7,"r35"},
                {35,10,"r35"},
                {35,14,"r35"},
                {35,15,"r35"},
                {35,16,"r35"},
                {35,17,"r35"},
                {35,23,"r35"},
                {35,24,"r35"},
                {35,25,"r35"},
                {35,26,"r35"},
                {35,27,"r35"},
                {35,28,"r35"},
                {39,0,"r49"},
                {39,1,"r49"},
                {39,2,"r49"},
                {39,9,"r49"},
                {39,11,"r49"},
                {39,12,"r49"},
                {39,13,"r49"},
                {39,18,"r49"},
                {39,19,"r49"},
                {39,20,"r49"},
                {39,21,"r49"},
                {39,22,"r49"},
                {46,0,"r21"},
                {46,1,"r21"},
                {46,2,"r21"},
                {46,9,"r21"},
                {46,11,"r21"},
                {46,12,"r21"},
                {46,13,"r21"},
                {46,18,"r21"},
                {46,19,"r21"},
                {46,20,"r21"},
                {46,21,"r21"},
                {46,22,"r21"},
                {61,0,"r28"},
                {61,1,"r28"},
                {61,2,"r28"},
                {61,9,"r28"},
                {61,11,"r28"},
                {61,12,"r28"},
                {61,13,"r28"},
                {61,18,"r28"},
                {61,19,"r28"},
                {61,20,"r28"},
                {61,21,"r28"},
                {61,22,"r28"},
                {62,0,"r29"},
                {62,3,"r29"},
                {62,4,"r29"},
                {62,7,"r29"},
                {62,10,"r29"},
                {62,14,"r29"},
                {62,15,"r29"},
                {62,23,"r29"},
                {62,24,"r29"},
                {62,25,"r29"},
                {62,26,"r29"},
                {62,27,"r29"},
                {62,28,"r29"},
                {63,0,"r30"},
                {63,3,"r30"},
                {63,4,"r30"},
                {63,7,"r30"},
                {63,10,"r30"},
                {63,14,"r30"},
                {63,15,"r30"},
                {63,23,"r30"},
                {63,24,"r30"},
                {63,25,"r30"},
                {63,26,"r30"},
                {63,27,"r30"},
                {63,28,"r30"},
                {64,0,"r32"},
                {64,3,"r32"},
                {64,4,"r32"},
                {64,7,"r32"},
                {64,10,"r32"},
                {64,14,"r32"},
                {64,15,"r32"},
                {64,16,"r32"},
                {64,17,"r32"},
                {64,23,"r32"},
                {64,24,"r32"},
                {64,25,"r32"},
                {64,26,"r32"},
                {64,27,"r32"},
                {64,28,"r32"},
                {65,0,"r33"},
                {65,3,"r33"},
                {65,4,"r33"},
                {65,7,"r33"},
                {65,10,"r33"},
                {65,14,"r33"},
                {65,15,"r33"},
                {65,16,"r33"},
                {65,17,"r33"},
                {65,23,"r33"},
                {65,24,"r33"},
                {65,25,"r33"},
                {65,26,"r33"},
                {65,27,"r33"},
                {65,28,"r33"},
                {66,0,"r36"},
                {66,3,"r36"},
                {66,4,"r36"},
                {66,7,"r36"},
                {66,10,"r36"},
                {66,14,"r36"},
                {66,15,"r36"},
                {66,16,"r36"},
                {66,17,"r36"},
                {66,23,"r36"},
                {66,24,"r36"},
                {66,25,"r36"},
                {66,26,"r36"},
                {66,27,"r36"},
                {66,28,"r36"},
                {70,0,"r23"},
                {70,1,"r23"},
                {70,2,"r23"},
                {70,7,"r23"},
                {70,9,"r23"},
                {70,11,"r23"},
                {70,12,"r23"},
                {70,13,"r23"},
                {70,18,"r23"},
                {70,19,"r23"},
                {70,20,"r23"},
                {70,21,"r23"},
                {70,22,"r23"},
                {71,0,"r24"},
                {71,1,"r24"},
                {71,2,"r24"},
                {71,9,"r24"},
                {71,11,"r24"},
                {71,12,"r24"},
                {71,13,"r24"},
                {71,18,"r24"},
                {71,19,"r24"},
                {71,20,"r24"},
                {71,21,"r24"},
                {71,22,"r24"},
                {72,3,"r8"},
                {74,3,"r10"},
                {75,0,"r25"},
                {75,1,"r25"},
                {75,2,"r25"},
                {75,9,"r25"},
                {75,11,"r25"},
                {75,12,"r25"},
                {75,13,"r25"},
                {75,18,"r25"},
                {75,19,"r25"},
                {75,20,"r25"},
                {75,21,"r25"},
                {75,22,"r25"},
                {76,3,"r43"},
                {76,7,"r43"},
                {76,10,"r43"},
                {77,3,"r44"},
                {77,7,"r44"},
                {77,10,"r44"},
                {78,3,"r45"},
                {78,7,"r45"},
                {78,10,"r45"},
                {79,3,"r46"},
                {79,7,"r46"},
                {79,10,"r46"},
                {80,3,"r47"},
                {80,7,"r47"},
                {80,10,"r47"},
                {81,3,"r48"},
                {81,7,"r48"},
                {81,10,"r48"},
                {86,0,"r22"},
                {86,1,"r22"},
                {86,2,"r22"},
                {86,9,"r22"},
                {86,11,"r22"},
                {86,12,"r22"},
                {86,13,"r22"},
                {86,18,"r22"},
                {86,19,"r22"},
                {86,20,"r22"},
                {86,21,"r22"},
                {86,22,"r22"},
                {89,0,"r27"},
                {89,1,"r27"},
                {89,2,"r27"},
                {89,9,"r27"},
                {89,11,"r27"},
                {89,12,"r27"},
                {89,13,"r27"},
                {89,18,"r27"},
                {89,19,"r27"},
                {89,20,"r27"},
                {89,21,"r27"},
                {89,22,"r27"},
                {91,0,"r4"},
                {91,1,"r4"},
                {91,2,"r4"},
                {91,9,"r4"},
                {91,11,"r4"},
                {91,12,"r4"},
                {91,13,"r4"},
                {91,18,"r4"},
                {91,19,"r4"},
                {91,20,"r4"},
                {91,21,"r4"},
                {91,22,"r4"},
                {92,3,"r5"},
                {94,3,"r7"},
                {95,3,"r9"},
                {100,0,"r11"},
                {100,1,"r11"},
                {100,2,"r11"},
                {100,9,"r11"},
                {100,11,"r11"},
                {100,12,"r11"},
                {100,13,"r11"},
                {100,18,"r11"},
                {100,19,"r11"},
                {100,20,"r11"},
                {100,21,"r11"},
                {100,22,"r11"},
                {103,3,"r6"},
                {104,0,"r26"},
                {104,1,"r26"},
                {104,2,"r26"},
                {104,9,"r26"},
                {104,11,"r26"},
                {104,12,"r26"},
                {104,13,"r26"},
                {104,18,"r26"},
                {104,19,"r26"},
                {104,20,"r26"},
                {104,21,"r26"},
                {104,22,"r26"} };

goto_table[0][1] = 1;
goto_table[0][2] = 4;
goto_table[0][8] = 2;
goto_table[0][9] = 5;
goto_table[0][10] = 6;
goto_table[0][11] = 10;
goto_table[0][12] = 7;
goto_table[0][13] = 8;
goto_table[0][14] = 9;
goto_table[0][15] = 11;
goto_table[0][16] = 19;
goto_table[0][17] = 23;
goto_table[0][18] = 24;
goto_table[0][19] = 26;
goto_table[0][20] = 13;
goto_table[0][22] = 12;
goto_table[2][1] = 29;
goto_table[2][2] = 4;
goto_table[2][8] = 2;
goto_table[2][9] = 5;
goto_table[2][10] = 6;
goto_table[2][11] = 10;
goto_table[2][12] = 7;
goto_table[2][13] = 8;
goto_table[2][14] = 9;
goto_table[2][15] = 11;
goto_table[2][16] = 19;
goto_table[2][17] = 23;
goto_table[2][18] = 24;
goto_table[2][19] = 26;
goto_table[2][20] = 13;
goto_table[2][22] = 12;
goto_table[15][16] = 34;
goto_table[15][17] = 23;
goto_table[15][18] = 24;
goto_table[15][19] = 26;
goto_table[15][21] = 33;
goto_table[18][16] = 38;
goto_table[18][17] = 23;
goto_table[18][18] = 24;
goto_table[18][19] = 26;
goto_table[25][16] = 44;
goto_table[25][17] = 23;
goto_table[25][18] = 24;
goto_table[25][19] = 26;
goto_table[31][16] = 48;
goto_table[31][17] = 23;
goto_table[31][18] = 24;
goto_table[31][19] = 26;
goto_table[32][5] = 49;
goto_table[32][16] = 50;
goto_table[32][17] = 23;
goto_table[32][18] = 24;
goto_table[32][19] = 26;
goto_table[36][10] = 58;
goto_table[37][16] = 34;
goto_table[37][17] = 23;
goto_table[37][18] = 24;
goto_table[37][19] = 26;
goto_table[37][21] = 60;
goto_table[40][17] = 62;
goto_table[40][18] = 24;
goto_table[40][19] = 26;
goto_table[41][17] = 63;
goto_table[41][18] = 24;
goto_table[41][19] = 26;
goto_table[42][18] = 64;
goto_table[42][19] = 26;
goto_table[43][18] = 65;
goto_table[43][19] = 26;
goto_table[45][3] = 67;
goto_table[45][20] = 68;
goto_table[47][16] = 69;
goto_table[47][17] = 23;
goto_table[47][18] = 24;
goto_table[47][19] = 26;
goto_table[50][6] = 72;
goto_table[51][2] = 4;
goto_table[51][8] = 75;
goto_table[51][9] = 5;
goto_table[51][10] = 6;
goto_table[51][11] = 10;
goto_table[51][12] = 7;
goto_table[51][13] = 8;
goto_table[51][14] = 9;
goto_table[51][15] = 11;
goto_table[51][16] = 19;
goto_table[51][17] = 23;
goto_table[51][18] = 24;
goto_table[51][19] = 26;
goto_table[51][20] = 13;
goto_table[51][22] = 12;
goto_table[52][16] = 76;
goto_table[52][17] = 23;
goto_table[52][18] = 24;
goto_table[52][19] = 26;
goto_table[53][16] = 77;
goto_table[53][17] = 23;
goto_table[53][18] = 24;
goto_table[53][19] = 26;
goto_table[54][16] = 78;
goto_table[54][17] = 23;
goto_table[54][18] = 24;
goto_table[54][19] = 26;
goto_table[55][16] = 79;
goto_table[55][17] = 23;
goto_table[55][18] = 24;
goto_table[55][19] = 26;
goto_table[56][16] = 80;
goto_table[56][17] = 23;
goto_table[56][18] = 24;
goto_table[56][19] = 26;
goto_table[57][16] = 81;
goto_table[57][17] = 23;
goto_table[57][18] = 24;
goto_table[57][19] = 26;
goto_table[73][16] = 87;
goto_table[73][17] = 23;
goto_table[73][18] = 24;
goto_table[73][19] = 26;
goto_table[82][16] = 34;
goto_table[82][17] = 23;
goto_table[82][18] = 24;
goto_table[82][19] = 26;
goto_table[82][21] = 88;
goto_table[83][7] = 89;
goto_table[84][7] = 91;
goto_table[85][4] = 92;
goto_table[87][6] = 95;
goto_table[90][1] = 97;
goto_table[90][2] = 4;
goto_table[90][8] = 2;
goto_table[90][9] = 5;
goto_table[90][10] = 6;
goto_table[90][11] = 10;
goto_table[90][12] = 7;
goto_table[90][13] = 8;
goto_table[90][14] = 9;
goto_table[90][15] = 11;
goto_table[90][16] = 19;
goto_table[90][17] = 23;
goto_table[90][18] = 24;
goto_table[90][19] = 26;
goto_table[90][20] = 13;
goto_table[90][22] = 12;
goto_table[93][20] = 98;
goto_table[96][16] = 99;
goto_table[96][17] = 23;
goto_table[96][18] = 24;
goto_table[96][19] = 26;
goto_table[101][4] = 103;
goto_table[102][7] = 104;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            strcpy(matrix[i][j].type, "E"); // Empty cell
        }
    }
    for (int i = 0; i < sizeof(insert2) / sizeof(insert2[0]); i++) {


        strcpy(matrix[insert2[i]->row][insert2[i]->col].type, insert2[i]->data);

    }
    for (int i = 0; i < sizeof(insert3) / sizeof(insert3[0]); i++) {


        strcpy(matrix[insert3[i]->row][insert3[i]->col].type, insert3[i]->data);

    }
}

