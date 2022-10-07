#ifndef DTS_LIB_MAIN_DEFS
#define DTS_LIB_MAIN_DEFS

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifdef DTS_DEBUG_CHECKS
#include <stdio.h>
#include <inttypes.h>
#define dts_debug_only(...) __VA_ARGS__
#else
#define dts_debug_only(...)
#endif

/* Inline only if the standard supports it */
#ifndef __STDC_VERSION__
#define DTSDEF_DEFAULT static
#else
#define DTSDEF_DEFAULT static inline
#endif

#ifndef DTSDEF
#define DTSDEF DTSDEF_DEFAULT
#endif

#ifdef _WIN32
#define dts_PRIzu "Iu"
#else
#define dts_PRIzu "zu"
#endif

#if !defined(__STDC_VERSION__) || (__STDC_VERSION__ == 199901L)
#define dts_alignof(TYPE) (size_t)(sizeof(struct { char a; TYPE b; }) - sizeof(TYPE))
#else
#define dts_alignof(TYPE) _Alignof(TYPE)
#endif

#define dts_align_size(SIZE, ALIGNMENT) ((SIZE) <= (ALIGNMENT) ? (ALIGNMENT) : ((SIZE) + ((SIZE) % (ALIGNMENT))))
#define dts_align_sizeof(TYPE, ALIGNMENT) dts_align_size(sizeof(TYPE), ALIGNMENT)

#endif

#if !defined(DTS_LIB_ARRAY_DEFS) && defined(DTS_USE_ARRAY)
#define DTS_LIB_ARRAY_DEFS

typedef struct ARRAY_STRUCT 
{
    size_t size;
    void* data;
} array_t;

#define array(TYPE) array_t

/**
 *  Represents an empty array of a certain type.
 *  This should only be used to initialize a variable, for other cases use ARRAY_EMPTY.
 *  @param TYPE element type of the array
 */ 
#define ARRAY_EMPTY_INIT(TYPE) { .size = 0, .data = NULL }

/**
 *  Represents an empty array of a certain type.
 *  When initializing a variable, ARRAY_EMPTY_INIT should be used instead.
 *  @param TYPE element type of the array
 */ 
#define ARRAY_EMPTY(TYPE) ((array(TYPE))ARRAY_EMPTY_INIT(TYPE))

// ARRAY: Main Functions

#define array_stt(SIZE, DATA_PTR) (array_t){ .size = SIZE, .data = DATA_PTR }
#define array_new(TYPE, COUNT) rrr_array_new(COUNT, sizeof(TYPE))

/**
 * Used to get a pointer to an element of the array.
 * Performs bounds checking at runtime if DTS_DEBUG_CHECKS is defined.
 * @param ARRAY (array_t*) the array 
 * @param TYPE type of the element
 * @param INDEX (size_t) index of the element
 * @return the pointer to the element
 */
#define array_eleptr(ARRAY, TYPE, INDEX) ((TYPE*)rrr_array_eleptr(dts_debug_only(__FILE__, __LINE__,) ARRAY, sizeof(TYPE), INDEX))

/**
 * Used to get/set the value of an element of the array.
 * Equivalent to indexing operator [] on normal C arrays/pointers, but performs bounds checking at runtime if DTS_DEBUG_CHECKS is defined.  
 * @param ARRAY (array_t*) the array 
 * @param TYPE type of the element
 * @param INDEX (size_t) index of the element
 * @return the value of the element
 */
#define array_ele(ARRAY, TYPE, INDEX) (*array_eleptr(ARRAY, TYPE, INDEX))

#define array_free(ARRAY) rrr_array_free(dts_debug_only(__FILE__, __LINE__,) ARRAY)

DTSDEF size_t array_size(array_t* array)
{
    return array->size;
}

/**
 *  Used to check if an array is empty (is equal to ARRAY_EMPTY_INIT or ARRAY_EMPTY).
 *  @param array the array to check
 *  @return the result of the check
 */ 
DTSDEF bool array_is_empty(array_t* array)
{
    return array->size == 0 && array->data == NULL;
}

// ARRAY: Raw functions

DTSDEF void rrr_array_free(dts_debug_only(const char* file, int line,) array_t* array)
{
    #ifdef DTS_DEBUG_CHECKS
    if(array == NULL)
    {
        fprintf(stdout, "%s:%d: Attempting to free array, but the pointer to the array is null!\n", file, line);
        exit(EXIT_FAILURE);
    }
    if(array_size(array) == 0 && array->data != NULL)
    {
        fprintf(stdout, "%s:%d: Attempting to free an invalid array!\n", file, line);
        printf(" The array has no size but a block of data is associated to it (data: %p).\n", array->data);
        exit(EXIT_FAILURE);
    }
    #endif

    free(array->data);
    *array = ARRAY_EMPTY(void);
}

DTSDEF array_t rrr_array_new(size_t element_count, size_t element_size)
{
    if(element_count == 0)
        return ARRAY_EMPTY(void);

    array_t array;
    array.size = element_count;
    array.data = malloc(element_size * element_count);
    return array;
}

DTSDEF void* rrr_array_eleptr(dts_debug_only(const char* file, int line,) array_t* array, size_t element_size, size_t index)
{
    #ifdef DTS_DEBUG_CHECKS
    if(array_size(array) <= index)
    {
        fprintf(stdout, "ERROR in %s:%d: Out of bounds access of an array element!\n", file, line);
        printf(" (array size: %"dts_PRIzu", accessed index: %"dts_PRIzu")\n", array_size(array), index);
        exit(EXIT_FAILURE);
    }
    #endif

    return &((char*)array->data)[element_size * index];
}

#endif

#if !defined(DTS_LIB_DYNARRAY_DEFS) && defined(DTS_USE_DYNARRAY)
#define DTS_LIB_DYNARRAY_DEFS

typedef struct DYNARRAY_STRUCT
{
    size_t capacity;
    size_t size;
    size_t element_size;
    char* data;
} dynarray_t;

#define DYNARRAY_DEFAULT_ELEMENT_COUNT 8

#define dynarray(TYPE) dynarray_t

#define RRR_DYNARRAY_EMPTY_INIT(ELEMENT_SIZE) { .capacity = 0, .size = 0, .element_size = (size_t)(ELEMENT_SIZE), .data = NULL }

#define RRR_DYNARRAY_EMPTY(ELEMENT_SIZE) ((dynarray_t)RRR_DYNARRAY_EMPTY_INIT(ELEMENT_SIZE))

#define DYNARRAY_EMPTY_INIT(TYPE) RRR_DYNARRAY_EMPTY_INIT(sizeof(TYPE))

#define DYNARRAY_EMPTY(TYPE) ((dynarray(TYPE))DYNARRAY_EMPTY_INIT(TYPE))

// DYNARRAY: Main Functions

#define dynarray_new(TYPE, ELEMENT_COUNT) rrr_dynarray_new(sizeof(TYPE), ELEMENT_COUNT)

#define dynarray_add(ARRAY, TYPE, ...) do { size_t last_index = rrr_dynarray_add_empty(ARRAY); dynarray_ele(ARRAY, TYPE, last_index) = (__VA_ARGS__); } while (0)

#define dynarray_remove(ARRAY, TYPE) rrr_dynarray_remove(ARRAY)

#define dynarray_eleptr(ARRAY, TYPE, INDEX) ((TYPE*)(rrr_dynarray_eleptr(dts_debug_only(__FILE__, __LINE__,) ARRAY, INDEX)))

#define dynarray_ele(ARRAY, TYPE, INDEX) (*dynarray_eleptr(ARRAY, TYPE, INDEX))

DTSDEF size_t dynarray_capacity(dynarray_t* array)
{
    return array->capacity;
}

DTSDEF size_t dynarray_size(dynarray_t* array)
{
    return array->size;
}

DTSDEF bool dynarray_is_empty(dynarray_t* array)
{
    return array->capacity == 0 && array->size == 0 && array->data == NULL;
}

DTSDEF void dynarray_free(dynarray_t* array)
{
    free(array->data);
    *array = RRR_DYNARRAY_EMPTY(array->element_size);
}

// DYNARRAY: Backing Functions

DTSDEF dynarray_t rrr_dynarray_new(size_t element_size, size_t initial_capacity)
{
    if(initial_capacity == 0)
        return RRR_DYNARRAY_EMPTY(element_size);

    dynarray_t array;
    array.capacity = initial_capacity;
    array.element_size = element_size;
    array.size = 0;
    array.data = malloc(array.element_size * array.capacity);
    return array;
}

DTSDEF size_t rrr_dynarray_add_empty(dynarray_t* array)
{
    if(array->capacity == 0)
    {
        array->capacity = DYNARRAY_DEFAULT_ELEMENT_COUNT;
        array->data = malloc(array->element_size * array->capacity);
    }
    else if(array->capacity <= array->size)
    {
        array->capacity *= 2;
        array->data = realloc(array->data, array->element_size * array->capacity);
    }

    return array->size++;
}

DTSDEF bool rrr_dynarray_remove(dynarray_t* array)
{
    if(array->size != 0)
    {
        array->size--;
        return true;
    }

    return false;
}

DTSDEF void* rrr_dynarray_eleptr(dts_debug_only(const char* file, int line,) dynarray_t* array, size_t index)
{
    #ifdef DTS_DEBUG_CHECKS
    if(dynarray_size(array) <= index)
    {
        fprintf(stdout, "ERROR in %s:%d: Out of bounds access of a dynarray element!\n", file, line);
        printf(" (dynarray size: %"dts_PRIzu", accessed index: %"dts_PRIzu")\n", dynarray_size(array), index);
        exit(EXIT_FAILURE);
    }
    #endif

    return &array->data[index * array->element_size];   
}

#endif

#if !defined(DTS_LIB_BUKARRAY_DEFS) && defined(DTS_USE_BUKARRAY)
#define DTS_LIB_BUKARRAY_DEFS

#define DTS_ELEMENTS_PER_BUCKET ((size_t)512)

typedef struct BUKARRAY_STRUCT
{
    size_t bucket_amount;
    size_t size;
    char** buckets;
} bukarray_t;

#define bukarray(TYPE) bukarray_t

#define BUKARRAY_EMPTY_INIT(TYPE) { .bucket_amount = 0, .size = 0, .buckets = NULL }

#define BUKARRAY_EMPTY(TYPE) ((bukarray_t)BUKARRAY_EMPTY_INIT(TYPE))

#define bukarray_new(TYPE, INIT_CAPACITY) rrr_bukarray_new(sizeof(TYPE), dts_alignof(TYPE), INIT_CAPACITY)

#define bukarray_add(ARRAY, TYPE, ...) do { TYPE* last_elem = rrr_bukarray_add_empty(ARRAY, sizeof(TYPE), dts_alignof(TYPE)); *last_elem = (__VA_ARGS__); } while (0)

#define bukarray_remove(ARRAY, TYPE) rrr_bukarray_remove(ARRAY)

#define bukarray_eleptr(ARRAY, TYPE, INDEX) ((TYPE*)rrr_bukarray_eleptr(dts_debug_only(__FILE__, __LINE__,) ARRAY, INDEX, sizeof(TYPE), dts_alignof(TYPE)))

#define bukarray_ele(ARRAY, TYPE, INDEX) (*bukarray_eleptr(ARRAY, TYPE, INDEX))

DTSDEF size_t bukarray_bucket_amount(bukarray_t* array)
{
    return array->bucket_amount;
}

DTSDEF size_t bukarray_capacity(bukarray_t* array)
{
    return array->bucket_amount * DTS_ELEMENTS_PER_BUCKET;
}

DTSDEF size_t bukarray_size(bukarray_t* array)
{
    return array->size;
}

DTSDEF bool bukarray_is_empty(bukarray_t* array)
{
    return array->bucket_amount == 0 && array->size == 0 && array->buckets == NULL;
}

DTSDEF void bukarray_free(bukarray_t* array)
{
    for (size_t i = 0; i < array->bucket_amount; i++)
        free(array->buckets[i]);

    free(array->buckets);
    *array = BUKARRAY_EMPTY();
}

DTSDEF bukarray_t rrr_bukarray_new(size_t sizeof_type, size_t alignof_type, size_t initial_capacity)
{
    if(initial_capacity == 0)
        return BUKARRAY_EMPTY();

    bukarray_t array;
    array.bucket_amount = (initial_capacity - 1) / DTS_ELEMENTS_PER_BUCKET + 1;
    array.size = 0;
    array.buckets = malloc(sizeof(char*) * array.bucket_amount);

    for (size_t i = 0; i < bukarray_bucket_amount(&array); i++)
        array.buckets[i] = malloc(sizeof_type * DTS_ELEMENTS_PER_BUCKET);
    
    return array;
}

DTSDEF void* rrr_bukarray_eleptr(dts_debug_only(const char* file, int line,) bukarray_t* array, size_t index, size_t sizeof_type, size_t alignof_type)
{
    #ifdef DTS_DEBUG_CHECKS
    if(bukarray_size(array) <= index)
    {
        fprintf(stdout, "ERROR in %s:%d: Out of bounds access of a bukarray element!\n", file, line);
        printf(" (bukarray size: %"dts_PRIzu", accessed index: %"dts_PRIzu")\n", bukarray_size(array), index);
        exit(EXIT_FAILURE);
    }
    #endif

    size_t bucket_index = index / DTS_ELEMENTS_PER_BUCKET;
    size_t internal_index = index % DTS_ELEMENTS_PER_BUCKET;

    return &(array->buckets[bucket_index])[sizeof_type * internal_index];
}

DTSDEF void* rrr_bukarray_add_empty(bukarray_t* array, size_t sizeof_type, size_t alignof_type)
{
    size_t new_index = bukarray_size(array);

    array->size++;

    if(new_index >= bukarray_capacity(array))
    {
        array->bucket_amount++;

        char* new_bucket = malloc(sizeof_type * DTS_ELEMENTS_PER_BUCKET);
        array->buckets = realloc(array->buckets, sizeof(char*) * array->bucket_amount);
        array->buckets[array->bucket_amount-1] = new_bucket;

        return new_bucket;
    }

    return rrr_bukarray_eleptr(dts_debug_only(__FILE__, __LINE__,) array, new_index, sizeof_type, alignof_type);
}

DTSDEF bool rrr_bukarray_remove(bukarray_t* array)
{
    if(bukarray_size(array) != 0)
    {
        array->size--;
        return true;
    }

    return false;
}

#endif

#if !defined(DTS_LIB_LIST_DEFS) && defined(DTS_USE_LIST)
#define DTS_LIB_LIST_DEFS

typedef struct listnode_t
{
    struct listnode_t* next;
    char rest [];
} listnode_t;

#define listnode(TYPE) listnode_t

#define rrr_listnode_value_offset(ALIGNOF_TYPE)        dts_align_sizeof(listnode_t*, ALIGNOF_TYPE)
#define rrr_listnode_size(SIZEOF_TYPE, ALIGNOF_TYPE)   (dts_align_sizeof(listnode_t*, ALIGNOF_TYPE) + dts_align_size(SIZEOF_TYPE, dts_alignof(listnode_t*)))

#define listnode_value_offset(TYPE)    rrr_listnode_value_offset(dts_alignof(TYPE))
#define listnode_size(TYPE)            rrr_listnode_size(sizeof(TYPE), dts_alignof(TYPE))

#define listnode_new(TYPE, NEXT)   rrr_listnode_new(sizeof(TYPE), dts_alignof(TYPE), NEXT)
#define listnode_next(NODE)         ((NODE)->next)

#define listnode_valueptr(NODE, TYPE)   ((TYPE*)rrr_listnode_valueptr(NODE, dts_alignof(TYPE)))
#define listnode_value(NODE, TYPE)      (*listnode_valueptr(NODE, TYPE))

DTSDEF void listnode_free(listnode_t* node)
{
    free(node);
}

DTSDEF listnode_t* rrr_listnode_new(size_t sizeof_type, size_t alignof_type, listnode_t* next)
{
    listnode_t* l = malloc(rrr_listnode_size(sizeof_type, alignof_type));
    l->next = next; 
    return l;
}

DTSDEF void* rrr_listnode_valueptr(listnode_t* node, size_t alignof_type)
{
    return ((char*)node) + rrr_listnode_value_offset(alignof_type);
}

typedef listnode_t* list_t;
#define list(TYPE) list_t

#define list_eleptr(LIST, TYPE, INDEX)  ((TYPE*)rrr_list_eleptr(dts_debug_only(__FILE__, __LINE__,) LIST, dts_alignof(TYPE), INDEX))

#define list_ele(LIST, TYPE, INDEX)     (*list_eleptr(LIST, TYPE, INDEX))

#define list_ele_node(LIST, INDEX)      rrr_list_ele_node(dts_debug_only(__FILE__, __LINE__,) LIST, INDEX)

#define list_insert_first(LIST, TYPE, VALUE) \
    do { \
        listnode_t* __new_node = listnode_new(TYPE, LIST); \
        listnode_value(__new_node, TYPE) = VALUE; \
        LIST = __new_node; \
    } while(0)

#define list_insert_at(LIST, TYPE, INDEX, VALUE) \
    do { \
        listnode_t* __new_node = listnode_new(TYPE, NULL); \
        listnode_value(__new_node, TYPE) = VALUE; \
        if(INDEX == 0) { \
            __new_node->next = LIST; \
            LIST = __new_node; \
        } else { \
            listnode_t* __prev_node = list_ele_node(LIST, (INDEX)-1); \
            __new_node->next = __prev_node->next; \
            __prev_node->next = __new_node; \
        } \
    } while(0)

#define list_insert_last(LIST, TYPE, VALUE) \
    do { \
        listnode_t* __new_node = listnode_new(TYPE, NULL); \
        listnode_value(__new_node, TYPE) = VALUE; \
        \
        if(LIST != NULL) \
            list_last_node(LIST)->next = __new_node; \
        else \
            LIST = __new_node; \
    } while(0)

DTSDEF size_t list_size(list_t list)
{
    size_t size = 0;

    while(list != NULL)
    {
        size++;
        list = list->next;
    }

    return size;
}

DTSDEF listnode_t* list_first_node(list_t list)
{
    return list;
}

DTSDEF listnode_t* rrr_list_ele_node(dts_debug_only(const char* file, int line,) list_t list, size_t index)
{
    #ifdef DTS_DEBUG_CHECKS
    if(list_size(list) <= index)
    {
        fprintf(stdout, "ERROR in %s:%d: Out of bounds access of an array element!\n", file, line);
        printf(" (array size: %"dts_PRIzu", accessed index: %"dts_PRIzu")\n", list_size(list), index);
        exit(EXIT_FAILURE);
    }
    #endif

    listnode_t* node = list;

    for (size_t i = 0; i < index; i++)
        node = node->next;

    return node;
}

DTSDEF listnode_t* list_last_node(list_t l)
{
    if(l == NULL) return NULL;

    listnode_t* last = l;

    while(last->next != NULL)
        last = last->next;

    return last;
}

DTSDEF list_t list_free(list_t l)
{
    while(l != NULL)
    {
        list_t next = l->next;
        free(l);
        l = next;
    }

    return NULL;
}

DTSDEF void* rrr_list_eleptr(dts_debug_only(const char* file, int line,) list_t l, size_t alignof_type, size_t index)
{
    #ifdef DTS_DEBUG_CHECKS
    if(list_size(l) <= index)
    {
        fprintf(stdout, "ERROR in %s:%d: Out of bounds access of an list element!\n", file, line);
        printf(" (list size: %"dts_PRIzu", accessed index: %"dts_PRIzu")\n", list_size(l), index);
        exit(EXIT_FAILURE);
    }
    #endif

    list_t current_list = l;

    for(size_t i = 0; i < index; i++)
        current_list = current_list->next;

    return rrr_listnode_valueptr(current_list, alignof_type);
}

#endif

#if !defined(DTS_LIB_TREE_DEFS) && defined(DTS_USE_TREE)
#define DTS_LIB_TREE_DEFS

typedef struct TREE_NODE_STRUCT
{
    struct TREE_NODE_STRUCT** leafs;
    size_t leaf_count;
    char data [];
} tnode_t;

typedef tnode_t* tree_t;

#define tree(TYPE) tree_t

DTSDEF void rrr_tree_max_depth(tree_t tree, size_t* current_max_depth, size_t current_depth)
{
    if(current_depth >= *current_max_depth) *current_max_depth = current_depth;

    for (size_t i = 0; i < tree->leaf_count; i++)
    {
        rrr_tree_max_depth(tree->leafs[i], current_max_depth, current_depth + 1);
    }
}

DTSDEF size_t tree_max_depth(tree_t tree)
{
    size_t max_depth = 0;

    rrr_tree_max_depth(tree, &max_depth, 0);
    
    return max_depth;
}

DTSDEF size_t tree_child_count(tree_t tree)
{
    return tree->leaf_count;
}

DTSDEF void tree_free(tree_t tree)
{
    for (size_t i = 0; i < tree->leaf_count; i++)
        tree_free(tree->leafs[i]);

    if(tree->leafs != NULL)
        free(tree->leafs);
    
    free(tree);
}

DTSDEF void tree_insert_subtree(tree_t tree, tree_t subtree)
{
    tree->leaf_count++;
    tree->leafs = realloc(tree->leafs, sizeof(tree_t) * tree->leaf_count);
    tree->leafs[tree->leaf_count - 1] = subtree; 
}

DTSDEF void tree_remove_subtree(tree_t tree, size_t subtree_index)
{
    tree_free(tree->leafs[subtree_index]);

    for (size_t i = subtree_index; i < tree->leaf_count - 1; i++)
    {
        tree->leafs[i] = tree->leafs[i + 1];
    }

    tree->leaf_count--;
    tree->leafs = realloc(tree->leafs, sizeof(tree_t) * tree->leaf_count);
}

DTSDEF tree_t tree_get_subtree(tree_t tree, size_t subtree_index)
{
    if(tree->leaf_count <= subtree_index) return NULL;

    return tree->leafs[subtree_index];
}

#define tree_new_empty(TYPE) rrr_tree_new(sizeof(TYPE), NULL)

#define tree_new(TYPE, DATA) rrr_tree_new(sizeof(TYPE), DATA)

#define tree_value(TREE, TYPE) *((TYPE*)rrr_tree_value(TREE))

#define tree_insert_empty(TREE, TYPE) rrr_tree_insert(TREE, sizeof(TYPE), NULL)

#define tree_insert(TREE, TYPE, DATA) rrr_tree_insert(TREE, sizeof(TYPE), DATA)´

DTSDEF tree_t rrr_tree_new(size_t data_size, void* data)
{
    tree_t tree = malloc(sizeof(tnode_t) + data_size);
    tree->leafs = NULL;
    tree->leaf_count = 0;

    if(data != NULL) memcpy(tree->data, data, data_size);
    
    return tree;
}

DTSDEF void* rrr_tree_value(tree_t tree)
{
    return tree->data;
}

DTSDEF tree_t rrr_tree_insert(tree_t tree, size_t data_size, void* data)
{
    tree->leaf_count++;
    tree->leafs = realloc(tree->leafs, sizeof(tree_t) * tree->leaf_count);
    tree->leafs[tree->leaf_count - 1] = rrr_tree_new(data_size, data);
    return tree->leafs[tree->leaf_count - 1];
}

#endif

#if !defined(DTS_LIB_CAST_ARRAY_DYNARRAY_DEFS) && defined(DTS_USE_DYNARRAY) && defined(DTS_USE_ARRAY)
#define DTS_LIB_CAST_ARRAY_DYNARRAY_DEFS

#define array_to_dynarray(ARRAY, TYPE)      rrr_array_to_dynarray(ARRAY, sizeof(TYPE))
#define dynarray_to_array(DYNARRAY, TYPE)   rrr_dynarray_to_array(DYNARRAY)

DTSDEF dynarray_t rrr_array_to_dynarray(array_t* array, size_t data_size)
{
    dynarray_t dynarray;
    dynarray.capacity = array->size;
    dynarray.element_size = data_size;
    dynarray.size = array->size;
    dynarray.data = array->data;
    return dynarray;
}

DTSDEF array_t rrr_dynarray_to_array(dynarray_t* dynarray)
{
    array_t array;
    array.size = dynarray->size;
    array.data = realloc(dynarray->data, dynarray->size * dynarray->element_size);
    return array;
}

#endif