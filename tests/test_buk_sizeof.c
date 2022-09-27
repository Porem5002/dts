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
    size_t a_buk_sizeof1 = sizeof(struct { buk_t* next; double b [DTS_ELEMENTS_PER_BUCKET]; });
    size_t m_buk_sizeof1 = buk_size(double);
    size_t a_buk_sizeof2 = sizeof(struct { buk_t* next; test_struct_t b [DTS_ELEMENTS_PER_BUCKET]; });
    size_t m_buk_sizeof2 = buk_size(test_struct_t);

    bool result = a_buk_sizeof1 == m_buk_sizeof1 && a_buk_sizeof2 == m_buk_sizeof2;
    return result ? 0 : 1;
}