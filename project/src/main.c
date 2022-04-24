#include <stdlib.h>
#include <stdio.h>

#include "emlparse.h"


#define ERR_ARGS_COUNT  "ERROR: invalid argument count"
#define ERR_FILE_ACCESS "ERROR: failed to open file"


int main(int argc, const char **argv) {
    if (argc != 2) {
        puts(ERR_ARGS_COUNT);
        return -1;
    }

    const char *path_to_eml = argv[1];

    FILE *eml = fopen(path_to_eml, "r");
    if (eml == NULL) {
        puts("file opened");
        return 1;
    }

    emlparse(eml);

    fclose(eml);
    return 0;
}
