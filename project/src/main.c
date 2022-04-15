#include <stdlib.h>
#include <stdio.h>

#include "emlparse.h"

#define ERR_ARGS_COUNT "ERROR: invalid argument count"


char* read_eml_from_file(const char *path_to_eml) {
    FILE *eml_file = fopen(path_to_eml, "r");
    fseek(eml_file, 0, SEEK_END);
    size_t eml_size = ftell(eml_file);
    fseek(eml_file, 0, SEEK_SET);

    char *eml = malloc(sizeof(char) * eml_size);
    fread(eml, sizeof(char), eml_size, eml_file);

    return eml;
}

int main( /*int argc, const char **argv*/) {
    // if (argc != 2) {
    //     puts(ERR_ARGS_COUNT);
    //     return -1;
    // }

    // const char *path_to_eml = argv[1];
    const char *path_to_eml = "./btests/emails/bilingual-simple.eml";
    char *eml = read_eml_from_file(path_to_eml);
    emlparse(eml);
    free(eml);
    return 0;
}
