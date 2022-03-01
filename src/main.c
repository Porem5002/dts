#include <stdint.h>
#include <stdio.h>
#include <time.h> 
#include <string.h> 

#include "include/dtstructs.h"

int main(int argc, char** argv)
{
    array(char*) args = array_create(char*, argc);

    for (size_t i = 0; i < array_size(&args); i++)
    {
        array_element(&args, char*, i) = argv[i];
    }
    
    for (size_t i = 0; i < array_size(&args); i++)
    {
        char* current_arg = array_element(&args, char*, i);
        printf("Arg %d: %s\n", i, current_arg);
    }
    
    array_free(&args);

    return 0;
}