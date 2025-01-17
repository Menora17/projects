#pragma once
#include <stdio.h>
#include <stdbool.h>
#include "SemanticAnalysis.h"
#include "Lexer.h"
#include "Tree.h"
#define NUM_OF_REGISTERS 8
#define LABEL_FORMAT "$$L%d"
/* ---------- Structs ---------- */
// Struct of a register in the code generator's register array
typedef struct Register
{
	char name[2]; // The name of the register for target code output
	char high[2];
	char low[2];
	bool inuse; // Whether the register is currently in use or not
} Register;
// Struct of the code generator
typedef struct Code_Generator
{
	Register registers[NUM_OF_REGISTERS]; // Array of registers to be used in the code generation process
		FILE* dest_file; // A pointer to the output file for the generated code
} Code_Generator;

Code_Generator* generator;

// Create a new code generator and points the compiler's code generator to it
void code_generator_create();
// Frees the memory allocated for the code generator of the compiler
void code_generator_destroy();
// Initializes the compiler's code generator
void code_generator_init();
// Searches for a free register in the code generator registers array.
// If found, marks it as inuse and returns the index of that register.
// If not found, terminates the compiler.
int code_generator_register_alloc();
// Marks the register in index r in the code generator registers array as unused
void code_generator_register_free(int r);
// Returns the register name of register r in the code generator registers array
char* code_generator_register_name(int r);
// Allocates a new lable name and returns a pointer to it
char* code_generator_label_create();
// Performs the right address computation for the given symbol according to its
// place in the program (global / local),
// and returns a string that represents that address.
// If the entry is NULL, returns NULL.
char* code_generator_symbol_address(SymbolTableEntry* entry);
// Outputs the given formated string to the target file
void code_generator_output(char* format, ...);
// Outputs the data segment of the program to the target file
void code_generator_output_data_segment();
// Generates the assembly code for the given parse tree
void code_generator_generate(ASTNode* parse_tree);
// Generates a block (BLOCK)
void code_generator_block(ASTNode* block);
// Generates a statement (STMT)
void code_generator_stmt(ASTNode* stmt);
// Generates a variable declaration statement (DECL)
void code_generator_decl(ASTNode* decl);
// Generates an assignment statement (ASSIGN)
void code_generator_assign(ASTNode* assign, SymbolTable* table);

// Generates a while statement (WHILE)
void code_generator_while(ASTNode* _while);
// Generates an expression
void code_generator_expression(ASTNode* expr);
// Generates a binary expression of the form: Expr -> Expr binary_operator Expr
void code_generator_binary_expression(int left_register, int right_register, TokensType op);


// Generates target code that moves the given token to the given register.
// Moves the token according to its type (identifier / literal)
void code_generator_mov_token(int register_number, Token* token);
// Generates target code that moves the given identifier token to the given register.
void code_generator_mov_identifier(int register_number, Token* token);

void code_generator_and(int left_register, int right_register);
// Generates division operation between left and right registers. left_register =left_register / right_register,
void code_generator_divide(int left_register, int right_register);
void code_generator_mul(int left_register, int right_register);
void code_generator_add(int left_register, int right_register);
void code_generator_sub(int left_register, int right_register);

