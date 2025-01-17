#define STACK_MAX_SIZE 100
#include "Tree.h"
enum { FALSE, TRUE };
typedef unsigned char Boolean;

typedef struct StackNode {
    void* data;
    struct StackNode* next;
} StackNode;

typedef struct Stack {
    StackNode* top;
} stack;
//======= PROTOTYPE ======================
void stack_init(stack* s);
Boolean  stack_empty(stack*);
Boolean  stack_full(stack*);
void* stack_pop(stack* s);
void stack_push(stack* s, void* info);
void* stack_top(stack* s);
void stackFree(stack* stack);