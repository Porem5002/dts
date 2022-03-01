#include <string.h>

#include "include/dtstructs.h"

size_t stack_max_size(stack_t* stack)
{
    return stack->max_size;
}

size_t stack_raw_size(stack_t* stack, size_t data_size)
{
    return (stack->top - stack->data) / data_size;
}

stack_t stack_raw_create(size_t element_size, size_t max_element_count)
{
    stack_t stack;
    stack.max_size = max_element_count;
    stack.data = malloc(element_size * max_element_count);
    stack.top = stack.data;
    return stack; 
}

void* stack_raw_peek(stack_t* stack, size_t data_size)
{
    return stack->top - data_size;
}

void* stack_raw_pop(stack_t* stack, size_t data_size)
{
    stack->top -= data_size;
    return stack->top;
}

bool stack_raw_push(stack_t* stack, size_t data_size, void* data)
{
    if(stack->top >= stack->data + data_size * stack->max_size)
        return false;

    memcpy(stack->top, data, data_size);
    stack->top += data_size;

    return true;
}

bool stack_is_empty(stack_t* stack)
{
    return stack->top == stack->data;
}

void stack_free(stack_t* stack)
{
    free(stack->data);
}