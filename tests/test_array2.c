#include <string.h>
#include <stdbool.h>

#define DTS_USE_ARRAY

#include "../dts.h"

static char* final_words [] = { "You", "are", "an", "array", "with", "many", "words", "inside", "of", "it" };

int main()
{ 
    char* c_array_words [] = { "I", "am", "an", "array", "with", "different", "words", "inside", "of", "it" };
    array(char*) words = ARRAY_EMPTY_INIT(char*);
    bool result = array_is_empty(&words);

    words = array_stt(sizeof(c_array_words)/sizeof(char*), c_array_words);

    result = result && !array_is_empty(&words);
    result = result && array_size(&words) == (sizeof(c_array_words)/sizeof(char*));

    array_ele(&words, char*, 0) = "You";
    array_ele(&words, char*, 1) = "are";
    array_ele(&words, char*, 5) = "many";

    for (size_t i = 0; i < array_size(&words); i++)
        result = result && strcmp(array_ele(&words, char*, i), final_words[i]) == 0;

    words = ARRAY_EMPTY(char*);

    result = result && array_is_empty(&words);

    return result ? 0 : 1;
}