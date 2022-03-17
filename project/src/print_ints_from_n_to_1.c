#include "print_ints_from_n_to_1.h"
#include <stdio.h>


void print_ints_from_n_to_1(int number) {
    if (number != 1) {
        print_ints_from_n_to_1(number > 1 ? number - 1 : number + 1);
        printf(" %i", number);
    } else {
        printf("1");
        return;
    }
}
