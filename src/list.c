#include <string.h>

#include "include/dtstructs.h"

node_t* node_raw_create(size_t data_size, void* data)
{
    node_t* node = malloc(sizeof(node_t) + data_size);
    node->next = NULL;
    memcpy((void*)node->data, data, data_size);
    return node;
}

node_t* node_raw_create_empty(size_t data_size)
{
    node_t* node = malloc(sizeof(node_t) + data_size);
    node->next = NULL;
    return node;
}

size_t list_size(list_t* list)
{
    node_t* last_node = *list;
    size_t size = 0;

    while (last_node != NULL) 
    {
        last_node = last_node->next;
        size++;
    }

    return size;
}

void list_raw_append(list_t* list, size_t data_size, void* data)
{
    node_t** next_of_last = list;

    while (*next_of_last != NULL)
    {
        next_of_last = &((*next_of_last)->next);
    }

    *next_of_last = node_raw_create(data_size, data);
}

void list_raw_insert(list_t* list, size_t data_size, void* data, size_t index)
{
    node_t* new_node = node_raw_create(data_size, data);

    if(index == 0)
    {
        new_node->next = *list;
        *list = new_node;
    }
    else
    {
        node_t* prev_node = list_get_node(list, index - 1);
        new_node->next = prev_node->next;
        prev_node->next = new_node;
    }
}

node_t* list_get_node(list_t* list, size_t index)
{
    node_t* node = *list;

    if(node == NULL) return NULL;

    for (size_t i = 0; i < index; i++)
    {
        if(node->next == NULL) return NULL;

        node = node->next;
    }
    
    return node;
}

void list_free(list_t* list)
{
    node_t* current_node = *list;

    while (current_node != NULL) 
    {
        node_t* next_node = current_node->next;

        free(current_node);

        current_node = next_node;
    }
}