// my_stack.c
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


/*********************** Function bodies **************/

// Initialize the stack
void stack_init(stack* stack) {
    stack->top = NULL;
}
Boolean stack_empty(stack* s) {
    return s->top == -1 ? 1 : 0;
}
Boolean  stack_full(stack* s) {
    return s->top == STACK_MAX_SIZE ? 1 : 0;
}

// Push an ASTNode onto the stack
void stack_push(stack* stack, void* data) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (newNode == NULL) {
        fprintf(stderr, "Failed to allocate memory for stack node.\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
}

// Pop an ASTNode from the stack
void* stack_pop(stack* stack) {
    if (stack->top == NULL) {
        return NULL;
    }
    StackNode* topNode = stack->top;
    void* data = topNode->data;
    stack->top = topNode->next;
    free(topNode);
    return data;
}

// Peek at the top ASTNode of the stack
void* stack_top(stack* stack) {
    if (stack->top == NULL) {
        return NULL;
    }
    return stack->top->data;
}
void stackFree(stack* stack) {
    while (stack->top != NULL) {
        StackNode* temp = stack->top;
        stack->top = stack->top->next;
        free(temp);
    }
}