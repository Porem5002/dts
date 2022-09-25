#include <stdbool.h>

#include "../dts.h"

int main()
{
    size_t align1 = dts_alignof(int);
    size_t align2 = dts_alignof(struct { char a; int b; });

    bool result = align1 == align2;
    return result ? 0 : 1;
}