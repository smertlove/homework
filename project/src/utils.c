#include "../include/utils.h"

size_t timer_from(unsigned char from) {
    size_t counter = 0;
    for (unsigned char i = from; i != 0; --i) {
        ++counter;
        printf("%c", i);
    }
    printf("0\n");
    return counter;
}


// TODO(Kirill Soloshenko): Implement `power of` function
int custom_pow(int base, int power) {
  int answ = 1;
  for (; power > 0; power--) {
    answ *= base;
  }
  return answ;
}
