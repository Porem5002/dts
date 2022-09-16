#include <stdio.h>

/* Allows usage of lists */
#define DTS_USE_LIST

#include "../../dts.h"

int main(int argc, char** argv)
{
    /* NULL value is equivalent to an empty list */
    list(float) list1 = NULL;

    /* use 'list_insert_last' to add a new element/node to the end of the list */
    list_insert_last(list1, float, 1.0);
    list_insert_last(list1, float, 2.0);
    list_insert_last(list1, float, 3.0);

    /* use 'list_insert_last' to add a new element/node to the beginning of the list */
    /* this will be the new first element of the list */
    list_insert_first(list1, float, 4.5);

    /* list(TYPE) is an alias to listnode(TYPE)* */
    /* We will use this variable to iterate over the nodes */ 
    listnode(float)* node = list1;

    while(node != NULL)
    {
        float val = listnode_value(node, float);
        printf("%f\n", val);
        node = node->next;
    }
    
    list1 = list_free(list1);

    putchar('\n');

    /* Creating a list manually from nodes */
    /* We will use n1 as the first node of the list */

    listnode(int)* n1 = listnode_new(int, NULL);
    listnode_value(n1, int) = 1;
    
    listnode(int)* n2 = listnode_new(int, NULL);
    listnode_value(n2, int) = 2;

    listnode(int)* n3 = listnode_new(int, NULL);
    listnode_value(n3, int) = 3;

    n1->next = n2;
    n2->next = n3;

    /* Iterator node */ 
    listnode(int)* iter_node = n1;

    while(iter_node != NULL)
    {
        int val = listnode_value(iter_node, int);
        printf("%d\n", val);
        iter_node = iter_node->next;
    }

    n1 = list_free(n1);

    return 0;
}