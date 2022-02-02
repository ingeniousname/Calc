#ifndef STACK_H_
#define STACK_H_




typedef struct Stack
{
    char* top;
    int used, max;
} Stack;

int init(Stack* stack);
int push(Stack* stack, char data);
char pop(Stack* stack);

void free_stack(Stack* stack);





#endif