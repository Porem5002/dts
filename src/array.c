#include <string.h>

#include "include/dtstructs.h"

size_t array_size(array_t* array)
{
    return array->size;
}

array_t array_raw_create(size_t element_size, size_t element_count)
{
    array_t array;
    array_raw_init(&array, element_size, element_count);
    return array;
}

void array_raw_init(array_t* array, size_t element_size, size_t element_count)
{
    array->size = element_count;
    array->data = malloc(element_size * element_count);
}

void* array_raw_element(array_t* array, size_t element_size, size_t index)
{
    return &array->data[element_size * index];
}

void array_free(array_t* array)
{
    free(array->data);
    array->data = NULL;
}

array_t __internal_cast_dynamic_array_to_array(dynamic_array_t* dynamic_array)
{
    array_t array;
    array.size = dynamic_array->top_element_index;
    array.data = realloc(dynamic_array->data, array.size * dynamic_array->element_size);
    return array;
}