#include <stdio.h>
#include <stdbool.h>
#include "SymbolTable.h"
#include "Lexer.h"
#include "Tree.h"
#include "CodeGeneration.h"




// Create a new code generator and points the compiler's code generator to it
void code_generator_create() {
	generator = (Code_Generator*)calloc(1, sizeof(Code_Generator));
	if (generator == NULL) {
		printf("%s", "Error! cant create a output file");
		exit(1);
	}
	strcpy(generator->registers[0].name,"AX");
	strcpy(generator->registers[0].low, "AL");
	strcpy(generator->registers[0].high, "AH");
	generator->registers[0].inuse = false;
	strcpy(generator->registers[1].name, "BX");
	strcpy(generator->registers[1].low, "BL");
	strcpy(generator->registers[1].high, "BH");
	generator->registers[1].inuse = false;
	strcpy(generator->registers[2].name, "CX");
	strcpy(generator->registers[2].low, "CL");
	strcpy(generator->registers[2].high, "CH");
	generator->registers[2].inuse = false;
	strcpy(generator->registers[3].name, "DX");
	strcpy(generator->registers[3].low, "DL");
	strcpy(generator->registers[3].high, "DH");
	generator->registers[3].inuse = false;
}
// Frees the memory allocated for the code generator of the compiler
void code_generator_destroy() {
	if (generator != NULL)
	{
		// Close the destination file
		fclose(generator->dest_file);
		free(generator);
		generator = NULL;
	}
}
// Initializes the compiler's code generator
void code_generator_init() {

}
// Searches for a free register in the code generator registers array.
// If found, marks it as inuse and returns the index of that register.
// If not found, terminates the compiler.
int code_generator_register_alloc() {
	for (int i = 0; i < NUM_OF_REGISTERS; i++)
	{
		if (generator->registers[i].inuse != true) {
			generator->registers[i].inuse = true;
			return i;
		}
	}
	// If couldn't find a free register
	printf("Couldn't find a free register");
	//compiler_destroy();
	exit(1);
}
// Marks the register in index r in the code generator registers array as unused
void code_generator_register_free(int r) {
	generator->registers[r].inuse = false;
}
// Returns the register name of register r in the code generator registers array
char* code_generator_register_name(int r) {
	return generator->registers[r].name;
}
// Allocates a new lable name and returns a pointer to it
char* code_generator_label_create() {
	// A static integer to create unique lables
	static int label_num = 0;
	// Allocate memory for the label
	char* label = (char*)calloc(8, sizeof(char));
	if (label == NULL) exit(1);
	// Create label
	sprintf(label, LABEL_FORMAT, label_num);
	// Increment static int for next label
	label_num++;
	// Return the new label
	return label;
}
// Performs the right address computation for the given symbol according to its
// place in the program (global / local),
// and returns a string that represents that address.
// If the entry is NULL, returns NULL.
char* code_generator_symbol_address(SymbolTableEntry* entry) {

}
// Outputs the given formated string to the target file
void code_generator_output(char* format, ...) {

}
// Outputs the data segment of the program to the target file
void code_generator_output_data_segment() {

}
// Generates the assembly code for the given parse tree
void code_generator_generate(ASTNode* parse_tree) {

}
// Generates a block (BLOCK)
void code_generator_block(ASTNode* block) {
	// BLOCK -> done
	if (block->childrenCount == 1)
		// Go to the parent scope when exiting a block
		return;
	// BLOCK -> STMT BLOCK
	else
	{
		// Generate the statement
		code_generator_stmt(block->children[0]);
		// Generate the block
		code_generator_block(block->children[1]);
	}
}
// Generates a statement (STMT)
void code_generator_stmt(ASTNode* stmt) {
	typedef int (*pFun)(ASTNode* );
	pFun arFun[] = { code_generator_decl ,code_generator_assign ,code_generator_while ,code_generator_expression };
	static const char* non_terminals[] = {
		"declaration",
		"assignment",
		"if_statement",
		"for_statement",
		"while_statement",
		"expression",
		"expression_statement"
	};
	for (int i = 0; i < sizeof(non_terminals) / sizeof(non_terminals[0]); i++)
	{
		if (strcmp(stmt->type, non_terminals[i]) == 0)
			arFun[i](stmt);
	}

}
// Generates a variable declaration statement (DECL)
void code_generator_decl(ASTNode* decl) {

}
// Generates an assignment statement (ASSIGN)
void code_generator_assign(ASTNode* assign,SymbolTable* table) {
	code_generator_expression(assign->children[1]);
	// Assign the expression value to the variable
	SymbolTable* entry = symbolTableLookup(table,assign->children[1]->value,assign->scope);
	
	code_generator_output("MOV", code_generator_symbol_address(entry),
		code_generator_register_name(assign->children[3]->data));
	// Free result register because we don't need it anymore
	code_generator_register_free(assign->children[3]->data);
}

// Generates a while statement (WHILE)
void code_generator_while(ASTNode* _while) {

}
// Generates an expression
void code_generator_expression(ASTNode* expr) {

}
// Generates a binary expression of the form: Expr -> Expr binary_operator Expr
void code_generator_binary_expression(int left_register, int right_register, TokensType op) {

}


// Generates target code that moves the given token to the given register.
// Moves the token according to its type (identifier / literal)
void code_generator_mov_token(int register_number, Token* token) {
		code_generator_output("MOV", code_generator_register_name(register_number), token->data);
}
// Generates target code that moves the given identifier token to the given register.
void code_generator_mov_identifier(int register_number, Token* token) {
	
	//code_generator_output("MOV", code_generator_register_name(register_number),token->data );
}

void code_generator_and(int left_register, int right_register) {
	
	code_generator_output("AND", code_generator_register_name(left_register), code_generator_register_name(right_register));
	code_generator_output("CMP", code_generator_register_name(left_register), 0);
}
// Generates division operation between left and right registers. left_register =left_register / right_register,
void code_generator_divide(int left_register, int right_register) {
	code_generator_output("MOV", "AX", code_generator_register_name(left_register));
	generator->registers[0].inuse = true;
	code_generator_output("XOR", "DX", "DX");
	code_generator_output("DIV", generator->registers[right_register].name);
	code_generator_output("MOV", code_generator_register_name(left_register), "AX");
	code_generator_register_free(0);
}
void code_generator_mul(int left_register, int right_register) {
	code_generator_output("MOV", "AX", code_generator_register_name(left_register));
	generator->registers[0].inuse = true;
	code_generator_output("XOR", "DX", "DX");
	code_generator_output("MUL", generator->registers[right_register].name);
	code_generator_output("MOV", code_generator_register_name(left_register), "AX");
	code_generator_register_free(0);
}
void code_generator_add(int left_register, int right_register) {
	code_generator_output("ADD", code_generator_register_name(left_register), code_generator_register_name(right_register));
}
void code_generator_sub(int left_register, int right_register) {
	code_generator_output("SUB", code_generator_register_name(left_register), code_generator_register_name(right_register));
}
