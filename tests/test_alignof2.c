#include <stdbool.h>

#include "../dts.h"

typedef struct test_struct_t
{ 
    double a;
    unsigned int b;
} test_struct_t;

int main()
{
    size_t align1 = dts_alignof(struct { double a; unsigned int b; });
    size_t align2 = dts_alignof(struct { char a; struct { double a; unsigned int b; } b; });
    size_t align3 = dts_alignof(struct test_struct_t);
    size_t align4 = dts_alignof(test_struct_t);
    
    bool result = align1 == align2 && align2 == align3 && align3 == align4;
    return result ? 0 : 1;
}