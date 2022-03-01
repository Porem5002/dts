#ifndef DTSTRUCTS_HEADER
#define DTSTRUCTS_HEADER

#include <stdlib.h>
#include <stdbool.h>

typedef unsigned char byte;

typedef struct ARRAY_STRUCT 
{
    size_t size;
    byte* data;
} array_t;

#define array(TYPE) array_t

size_t array_size(array_t* array);

array_t array_raw_create(size_t element_size, size_t element_count);

void array_raw_init(array_t* array, size_t element_size, size_t element_count);

void* array_raw_element(array_t* array, size_t element_size, size_t index);

void array_free(array_t* array);

#define array_create(TYPE, COUNT) array_raw_create(sizeof(TYPE), COUNT)

#define array_init(ARRAY, TYPE, COUNT) array_raw_init(ARRAY, sizeof(TYPE), COUNT)

#define array_element(ARRAY, TYPE, INDEX) (*(TYPE*)array_raw_element(ARRAY, sizeof(TYPE), INDEX))

typedef struct DYNAMIC_ARRAY_STRUCT
{
    size_t element_count;
    size_t element_size;
    size_t top_element_index;
    byte* data;
} dynamic_array_t;

#define DYNAMIC_ARRAY_DEFAULT_ELEMENT_COUNT 8

#define dynamic_array(TYPE) dynamic_array_t

size_t dynamic_array_allocated_size(dynamic_array_t* array);

size_t dynamic_array_size(dynamic_array_t* array);

dynamic_array_t dynamic_array_raw_create(size_t element_size, size_t element_count);

void dynamic_array_raw_init(dynamic_array_t* array, size_t element_size, size_t element_count);

size_t dynamic_array_raw_add(dynamic_array_t* array, void* data_to_add);

void* dynamic_array_raw_element(dynamic_array_t* array, size_t index);

void dynamic_array_free(dynamic_array_t* array);

#define dynamic_array_create(TYPE, ELEMENT_COUNT) dynamic_array_raw_create(sizeof(TYPE), ELEMENT_COUNT)

#define dynamic_array_init(ARRAY, TYPE, ELEMENT_COUNT) dynamic_array_raw_init(ARRAY, sizeof(TYPE), ELEMENT_COUNT)

#define dynamic_array_add(ARRAY, TYPE, DATA) dynamic_array_raw_add(ARRAY, DATA)

#define dynamic_array_element(ARRAY, TYPE, INDEX) (*(TYPE*)(dynamic_array_raw_element(ARRAY, INDEX)))

typedef struct
{
    void* top;
    void* data;
    size_t max_size;
} stack_t;

#define stack(TYPE) stack_t

size_t stack_max_size(stack_t* stack);

size_t stack_raw_size(stack_t* stack, size_t data_size);

stack_t stack_raw_create(size_t element_size, size_t max_element_count);

void* stack_raw_peek(stack_t* stack, size_t data_size);

void* stack_raw_pop(stack_t* stack, size_t data_size);

bool stack_raw_push(stack_t* stack, size_t data_size, void* data);

bool stack_is_empty(stack_t* stack);

void stack_free(stack_t* stack);

#define stack_size(STACK, TYPE) stack_raw_size(STACK, sizeof(TYPE))

#define stack_create(TYPE, MAX_COUNT) stack_raw_create(sizeof(TYPE), MAX_COUNT)

#define stack_peek(STACK, TYPE) (*(TYPE*)stack_raw_peek(STACK, sizeof(TYPE)))

#define stack_pop(STACK, TYPE) (*(TYPE*)stack_raw_pop(STACK, sizeof(TYPE)))

#define stack_push(STACK, TYPE, DATA) stack_raw_push(STACK, sizeof(TYPE), DATA)

typedef struct NODE_STRUCT
{
    struct NODE_STRUCT* next;
    byte data [0];
} node_t;

node_t* node_raw_create_empty(size_t data_size);

node_t* node_raw_create(size_t data_size, void* data);

#define node_create_empty(TYPE) node_raw_create_empty(sizeof(TYPE))

#define node_create(TYPE, DATA) node_raw_create(sizeof(TYPE), DATA)

typedef node_t* list_t;

#define list(TYPE) list_t

#define EMPTY_LIST NULL

size_t list_size(list_t* list);

void list_raw_append(list_t* list, size_t data_size, void* data);

void list_raw_insert(list_t* list, size_t data_size, void* data, size_t index);

node_t* list_get_node(list_t* list, size_t index);

void list_free(list_t* list);

#define list_append(LIST, TYPE, DATA) list_raw_append(LIST, sizeof(TYPE), DATA)

#define list_insert(LIST, TYPE, DATA, INDEX) list_raw_insert(LIST, sizeof(TYPE), DATA, INDEX)

#define list_element_address(LIST, INDEX) (&list_get_node(LIST, INDEX)->data) 

#define list_element(LIST, TYPE, INDEX) (*(TYPE*)(list_element_address(LIST, INDEX)))

typedef struct TREE_NODE_STRUCT
{
    struct TREE_NODE_STRUCT** leafs;
    size_t leaf_count;
    byte data [0];
} tree_node_t;

typedef tree_node_t* tree_t; 

#define tree(TYPE) tree_t

size_t tree_max_depth(tree_t tree);

size_t tree_child_count(tree_t tree);

tree_t tree_raw_create(size_t data_size, void* data);

void* tree_raw_value(tree_t tree);

tree_t tree_raw_insert(tree_t tree, size_t data_size, void* data);

void tree_insert_subtree(tree_t tree, tree_t leaf);

void tree_remove_subtree(tree_t tree, size_t child_index);

tree_t tree_get_subtree(tree_t tree, size_t child_index);

void tree_free(tree_t tree);

#define tree_create_empty(TYPE) tree_raw_create(sizeof(TYPE), NULL)

#define tree_create(TYPE, DATA) tree_raw_create(sizeof(TYPE), DATA)

#define tree_value(TREE, TYPE) *((TYPE*)tree_raw_value(TREE))

#define tree_insert_empty(TREE, TYPE) tree_raw_insert(TREE, sizeof(TYPE), NULL)

#define tree_insert(TREE, TYPE, DATA) tree_raw_insert(TREE, sizeof(TYPE), DATA)

//***********************************************
//                   CASTING
//***********************************************

#define cast_array_to_dynamic_array(ARRAY, TYPE)            __internal_cast_array_to_dynamic_array(ARRAY, sizeof(TYPE))
#define cast_dynamic_array_to_array(DYNAMIC_ARRAY, TYPE)    __internal_cast_dynamic_array_to_array(DYNAMIC_ARRAY)

array_t __internal_cast_dynamic_array_to_array(dynamic_array_t* dynamic_array);
dynamic_array_t __internal_cast_array_to_dynamic_array(array_t* array, size_t data_size);

#endif