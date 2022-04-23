#include <stdlib.h>
#include <stdio.h>

#include "emlparse.h"

#define ERR_ARGS_COUNT "ERROR: invalid argument count"

//
int main( int argc, const char **argv) {
   if (argc != 2) {
       puts(ERR_ARGS_COUNT);
       return -1;
   }

   const char *path_to_eml = argv[1];


//  int main( ) {
//    const char *path_to_eml = "./btests/emails/broken-ctype.eml";
    FILE *eml = fopen(path_to_eml, "r");
    
    emlparse(eml);

    return 0;
}
