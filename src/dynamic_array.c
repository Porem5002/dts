#include <stdint.h>
#include <string.h>

#include "include/dtstructs.h"

size_t dynamic_array_allocated_size(dynamic_array_t* array)
{
    return array->element_count;
}

size_t dynamic_array_size(dynamic_array_t* array)
{
    return array->top_element_index;
}

dynamic_array_t dynamic_array_raw_create(size_t element_size, size_t element_count)
{
    dynamic_array_t array;
    dynamic_array_raw_init(&array, element_size, element_count);
    return array;
}

void dynamic_array_raw_init(dynamic_array_t* array, size_t element_size, size_t element_count)
{
    array->top_element_index = element_count;
    array->element_size = element_size;

    if(element_count != 0)
        array->element_count = (DYNAMIC_ARRAY_DEFAULT_ELEMENT_COUNT - element_count % DYNAMIC_ARRAY_DEFAULT_ELEMENT_COUNT) + element_count;
    else
        array->element_count = DYNAMIC_ARRAY_DEFAULT_ELEMENT_COUNT;

    array->data = malloc(array->element_size * array->element_count);
}

size_t dynamic_array_raw_add(dynamic_array_t* array, void* data_to_add)
{
    byte* new_element;

    if(array->element_count <= array->top_element_index)
    {
        array->element_count *= 2;
        array->data = realloc(array->data, array->element_size * array->element_count);
    }

    new_element = &array->data[array->top_element_index * array->element_size]; 

    if(data_to_add != NULL)
    {
        memcpy(new_element, data_to_add, array->element_size);
    }

    array->top_element_index++;

    return array->top_element_index - 1;
}

void* dynamic_array_raw_element(dynamic_array_t* array, size_t index)
{
    return &array->data[index * array->element_size];   
}

void dynamic_array_free(dynamic_array_t* array)
{
    free(array->data);
    array->data = NULL;  
}

dynamic_array_t __internal_cast_array_to_dynamic_array(array_t* array, size_t data_size)
{
    dynamic_array_t dynamic_array;
    dynamic_array.element_count = array->size;
    dynamic_array.element_size = data_size;
    dynamic_array.top_element_index = array->size;
    dynamic_array.data = array->data;
    return dynamic_array;
}