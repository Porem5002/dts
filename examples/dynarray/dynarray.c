#include <stdio.h>

/* Allows usage of dynamic arrays */
#define DTS_USE_DYNARRAY

#include "../../dts.h"

int main()
{
    /* Allocate empty dynamic array */
    dynarray(char*) name_pool = dynarray_new(char*, 0);

    /* Add elements to the array using 'array_ele' */
    dynarray_add(&name_pool, char*, "Jack");
    dynarray_add(&name_pool, char*, "Karl");
    dynarray_add(&name_pool, char*, "Jess");
    dynarray_add(&name_pool, char*, "Anthony");
    dynarray_add(&name_pool, char*, "Josef");

    puts("Names:");

    for (size_t i = 0; i < dynarray_size(&name_pool); i++)
    {
        /* You can also use 'dynarray_ele' to get the value of an element */
        char* current = dynarray_ele(&name_pool, char*, i);
        printf("\t%s\n", current);
    }

    dynarray_remove(&name_pool, char*);
    dynarray_remove(&name_pool, char*);

    dynarray_add(&name_pool, char*, "Noah");
    dynarray_add(&name_pool, char*, "William");
    dynarray_add(&name_pool, char*, "Sophie");

    puts("\nNames:");

    for (size_t i = 0; i < dynarray_size(&name_pool); i++)
    {
        char* current = dynarray_ele(&name_pool, char*, i);
        printf("\t%s\n", current);
    }

    /* Deallocating the dynamic array */
    dynarray_free(&name_pool);

    return 0;    
}