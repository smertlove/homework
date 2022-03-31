#include <stdio.h>

#include "client_t.h"
#include "print_manager.h"

void print_client_data_fields(char *data_fields_to_print[], size_t array_size) {
    // size_t array_size = sizeof(*data_fields_to_print) / sizeof(*data_fields_to_print[0]);
    for (size_t i = 0; i < array_size; i++) {
        printf("%zu %s\n", i + 1, data_fields_to_print[i]);
    }
}

