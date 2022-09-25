#include <stdbool.h>

#define DTS_USE_ARRAY

#include "../dts.h"

static int final_vals [] = { 345*2, 0, 127*2, 1011*2, 2022*2 };

int main()
{
    array(int) vals = array_new(int, 5);

    bool result = !array_is_empty(&vals);

    for (size_t i = 0; i < array_size(&vals); i++)
        array_ele(&vals, int, i) = 0;

    array_ele(&vals, int, 0) = 345;
    array_ele(&vals, int, 4) = 2022;
    array_ele(&vals, int, 2) = 127;
    array_ele(&vals, int, 3) = 1011;

    for (size_t i = 0; i < array_size(&vals); i++)
        array_ele(&vals, int, i) *= 2;

    for (size_t i = 0; i < array_size(&vals); i++)
        result = result && array_ele(&vals, int, i) == final_vals[i];

    array_free(&vals);

    result = result && array_is_empty(&vals);

    return result ? 0 : 1;
}