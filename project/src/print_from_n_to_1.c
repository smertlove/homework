#include <stdio.h>

#include "print_from_n_to_1.h"

void print_from_n_to_1(int number) {
    if (number != 1) {
        print_from_n_to_1(number > 1 ? number - 1 : number + 1);
        printf(" %i", number);
    } else {
        printf("1");
    }
}
