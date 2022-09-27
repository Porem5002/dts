#include <stdbool.h>

#define DTS_USE_BUKARRAY

#include "../dts.h"

typedef struct person_t
{
    char* name;
    double height;
    int age;
} test_struct_t;

int main()
{
    struct { buk_t* next; double b [DTS_ELEMENTS_PER_BUCKET]; } tdouble;
    struct { buk_t* next; test_struct_t b [DTS_ELEMENTS_PER_BUCKET]; } tstruct;

    void* a_buk_value_ptr1 = &tdouble.b;
    void* m_buk_value_ptr1 = ((char*)&tdouble) + buk_value_offset(double);
    void* a_buk_value_ptr2 = &tstruct.b;
    void* m_buk_value_ptr2 = ((char*)&tstruct) + buk_value_offset(test_struct_t);

    bool result = a_buk_value_ptr1 == m_buk_value_ptr1 && a_buk_value_ptr2 == m_buk_value_ptr2;
    return result ? 0 : 1;
}