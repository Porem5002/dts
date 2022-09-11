#include <stdio.h>

/* Allows usage of arrays */
#define DTS_USE_ARRAY

#include "../../dts.h"

int main()
{
    /* Create an array on the heap (using malloc) */
    array(int) nums = array_new(int, 4);

    /* Modify elements of the array using 'array_ele' */
    array_ele(&nums, int, 0) = 32;
    array_ele(&nums, int, 1) = 9;
    array_ele(&nums, int, 2) = 11;
    array_ele(&nums, int, 3) = 3;

    puts("Heap Array:");

    for (size_t i = 0; i < array_size(&nums); i++)
    {
        /* You can also use 'array_ele' to get the value of an element */
        int current = array_ele(&nums, int, i);
        printf("%d\n", current);
    }

    /* Deallocating the array */
    array_free(&nums);

    putchar('\n');

    float values [3] = { 1050, 0.005, 12.34 };

    /* Create an alias to an array or block of memory */
    array(float) values_alias = array_stt(3, values);

    /* Modifying element of 'values' through 'values_alias' */
    array_ele(&values_alias, float, 0) *= 2;

    puts("Values:");

    for (size_t i = 0; i < 3; i++)
        printf("%f\n", values[i]);

    puts("\nValues Alias:");

    for (size_t i = 0; i < array_size(&values_alias); i++)
        printf("%f\n", array_ele(&values_alias, float, i));

    // Using 'array_stt' does not allocate any heap memory
    // No need to call 'array_free'

    return 0;    
}