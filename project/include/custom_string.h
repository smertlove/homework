#ifndef PROJECT_INCLUDE_CUSTOM_STRING_H_
#define PROJECT_INCLUDE_CUSTOM_STRING_H_

#include <stdlib.h>

typedef struct {
	char *data;
	size_t size;
	size_t memory;
} string_t;




string_t* init_string(void);
void add_char (string_t *string, char ch);
void free_string(string_t *string);


#endif  // PROJECT_INCLUDE_CUSTOM_STRING_H_