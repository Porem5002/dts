#include <stdbool.h>

#define DTS_USE_LIST

#include "../dts.h"

typedef struct person_t
{
    char* name;
    double height;
    int age;
} person_t;

int main()
{
    size_t a_list_node_sizeof1 = sizeof(struct { listnode_t* next; double b; });
    size_t m_list_node_sizeof1 = listnode_size(double);
    size_t a_list_node_sizeof2 = sizeof(struct { listnode_t* next; person_t b; });
    size_t m_list_node_sizeof2 = listnode_size(person_t);

    bool result = a_list_node_sizeof1 == m_list_node_sizeof1 && a_list_node_sizeof2 == m_list_node_sizeof2;
    return result ? 0 : 1;
}