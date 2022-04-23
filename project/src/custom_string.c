#include <malloc.h>
#include <stdbool.h>


#include "custom_string.h"



string_t* init_string(void) {
	string_t *string = calloc(1, sizeof(string_t));
	string->size = 0;
	return string;
}

void add_char (string_t *string, char ch) {
	if (ch == '\r') return;
	++string->size;
	if (string->data == NULL) {
		string->data = calloc(1, string->size);
	} else {
		char *tmp = realloc(string->data, string->size);
		string->data = tmp;
	}
	string->data[string->size - 1] = ch;
}

void free_string(string_t *string){
    if (string != NULL && string->data != NULL)
    {
    free(string->data);
    }
    free(string);
}