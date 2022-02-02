#include "stack.h"
#include "stdlib.h"


int init(Stack* stack)
{
    stack->top = malloc(sizeof(char));
    if(!stack->top) return 0;
    stack->max = 1;
    stack->used = 0;
    return 1;
}

int push(Stack* stack, char data)
{
    if(stack->used == stack->max)
    {
        char* temp = realloc(stack->top, sizeof(char) * 2 * stack->max);
        if(temp == NULL) return 0;
        stack->top = temp;
        stack->max *= 2;
    }
    stack->top[stack->used] = data;
    stack->used++;    
    return 1;
}

char pop(Stack* stack)
{
    stack->used--;
    if(stack->used * 4 < stack->max)
    {
        stack->top = realloc(stack->top, sizeof(char) * (stack->max / 2 + 1));
        stack->max = stack->max / 2 + 1;
    }
    return stack->top[stack->used];
}


void free_stack(Stack* stack)
{
    free(stack->top);
}
