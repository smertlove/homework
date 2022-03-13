#include "../include/utils.h"

size_t timer_from(unsigned char from) {
    size_t counter = 0;
    for (unsigned char i = from; i != 0; --i) {
        ++counter;
        printf("%c", i);
    }
    return counter;
}


// TODO(Kirill Soloshenko): Implement `power of` function
/*
int custom_pow(int base, int power) {
    return 0;
}
*/
