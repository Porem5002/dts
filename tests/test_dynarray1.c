#include <string.h>
#include <stdbool.h>

#define DTS_USE_DYNARRAY

#include "../dts.h"

typedef struct
{
    int v1;
    bool v2;
} test_struct_t;

bool test_struct_equals(test_struct_t a, test_struct_t b)
{
    return a.v1 == b.v1 && a.v2 == b.v2;
}

int main()
{ 
    bool result = true;
    dynarray(test_struct_t) ts = dynarray_new(test_struct_t, 0);

    result = result && dynarray_is_empty(&ts);

    dynarray_add(&ts, test_struct_t, (test_struct_t){ 666, true });

    result = result && !dynarray_is_empty(&ts);

    dynarray_add(&ts, test_struct_t, (test_struct_t){ 32, true });
    dynarray_add(&ts, test_struct_t, (test_struct_t){ 69, false });
    dynarray_add(&ts, test_struct_t, (test_struct_t){ 32, true });

    result = result && dynarray_size(&ts) == 4;
    result = result && test_struct_equals(dynarray_ele(&ts, test_struct_t, 0), (test_struct_t){ 666, true });
    result = result && test_struct_equals(dynarray_ele(&ts, test_struct_t, 1), (test_struct_t){ 32, true });
    result = result && test_struct_equals(dynarray_ele(&ts, test_struct_t, 2), (test_struct_t){ 69, false });
    result = result && test_struct_equals(dynarray_ele(&ts, test_struct_t, 3), (test_struct_t){ 32, true });

    dynarray_remove(&ts, test_struct_t);
    dynarray_remove(&ts, test_struct_t);
    
    dynarray_add(&ts, test_struct_t, (test_struct_t){ 8, false });
    dynarray_add(&ts, test_struct_t, (test_struct_t){ 16, true });
    dynarray_add(&ts, test_struct_t, (test_struct_t){ 32, false });
    dynarray_add(&ts, test_struct_t, (test_struct_t){ 64, true });

    result = result && dynarray_size(&ts) == 6;
    result = result && test_struct_equals(dynarray_ele(&ts, test_struct_t, 0), (test_struct_t){ 666, true });
    result = result && test_struct_equals(dynarray_ele(&ts, test_struct_t, 1), (test_struct_t){ 32, true });
    result = result && test_struct_equals(dynarray_ele(&ts, test_struct_t, 2), (test_struct_t){ 8, false });
    result = result && test_struct_equals(dynarray_ele(&ts, test_struct_t, 3), (test_struct_t){ 16, true });
    result = result && test_struct_equals(dynarray_ele(&ts, test_struct_t, 4), (test_struct_t){ 32, false });
    result = result && test_struct_equals(dynarray_ele(&ts, test_struct_t, 5), (test_struct_t){ 64, true });

    dynarray_ele(&ts, test_struct_t, 0) = (test_struct_t){ 69, false };

    result = result && test_struct_equals(dynarray_ele(&ts, test_struct_t, 0), (test_struct_t){ 69, false });

    dynarray_free(&ts);

    result = result && dynarray_is_empty(&ts);

    return result ? 0 : 1;
}