#include <stdio.h>
#include <stdbool.h>

#define DTS_USE_BUKARRAY

#include "../dts.h"

typedef struct test_struct_t
{
    size_t id;
    char value;
} test_struct_t;

int main()
{
    bool result = true;
    bukarray(test_struct_t) ts = BUKARRAY_EMPTY_INIT(test_struct_t);

    result = result && bukarray_is_empty(&ts);

    ts = bukarray_new(test_struct_t, 20);

    result = result && !bukarray_is_empty(&ts);
    result = result && bukarray_bucket_amount(&ts) == 1;

    bukarray_add(&ts, test_struct_t, (test_struct_t){ .id = 1, .value = 'A' });
    bukarray_add(&ts, test_struct_t, (test_struct_t){ .id = 2, .value = 'b' });
    bukarray_add(&ts, test_struct_t, (test_struct_t){ .id = 3, .value = 'c' });

    result = result && bukarray_size(&ts) == 3;

    for (size_t i = 0; i < DTS_ELEMENTS_PER_BUCKET / 2; i++)
        bukarray_add(&ts, test_struct_t, (test_struct_t){ .id = i, .value = '0' + (char)(i % 25) });

    for (size_t i = 0; i < DTS_ELEMENTS_PER_BUCKET / 2; i++)
        bukarray_add(&ts, test_struct_t, (test_struct_t){ .id = i, .value = '1' + (char)(i % 24) });

    bukarray_remove(&ts, test_struct_t);
    bukarray_remove(&ts, test_struct_t);

    result = result && bukarray_bucket_amount(&ts) == 2;
    result = result && bukarray_size(&ts) == (DTS_ELEMENTS_PER_BUCKET + 1);

    test_struct_t first = bukarray_ele(&ts, test_struct_t, 0);
    test_struct_t second = bukarray_ele(&ts, test_struct_t, 1);
    test_struct_t third = bukarray_ele(&ts, test_struct_t, 2);

    result = result && first.id == 1 && first.value == 'A';
    result = result && second.id == 2 && second.value == 'b';
    result = result && third.id == 3 && third.value == 'c';
    
    size_t external_i = 3;

    for (size_t i = 0; i < DTS_ELEMENTS_PER_BUCKET / 2; i++)
    {
        test_struct_t val = bukarray_ele(&ts, test_struct_t, external_i);
        result = result && val.id == i && val.value == ('0' + (char)(i % 25));
        external_i++;
    }
    
    for (size_t i = 0; i < DTS_ELEMENTS_PER_BUCKET / 2 - 2; i++)
    {
        test_struct_t val = bukarray_ele(&ts, test_struct_t, external_i);
        result = result && val.id == i && val.value == ('1' + (char)(i % 24));
        external_i++;
    }

    result = result && external_i == bukarray_size(&ts) && bukarray_size(&ts) == (DTS_ELEMENTS_PER_BUCKET + 1);

    bukarray_free(&ts);

    result = result && bukarray_is_empty(&ts);

    return result ? 0 : 1;
}