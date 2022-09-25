#include <stdbool.h>

#include "../dts.h"

int main()
{
    size_t a_sizeof_1 = sizeof(struct { char a; int b; });
    size_t m_sizeof_1 = dts_align_sizeof(char, dts_alignof(int)) + dts_align_sizeof(int, dts_alignof(char));
    size_t a_sizeof_2 = sizeof(struct { float a; void* b; });
    size_t m_sizeof_2 = dts_align_sizeof(float, dts_alignof(void*)) + dts_align_sizeof(void*, dts_alignof(float));

    bool result = a_sizeof_1 == m_sizeof_1 && a_sizeof_2 == m_sizeof_2;
    return result ? 0 : 1;
}