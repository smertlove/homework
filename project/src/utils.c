#include "utils.h"

size_t timer_from(int from) {
    size_t counter = 0;
    for (int i = from; i >= 0; --i) {
        ++counter;
        printf("%d", i);
        
        if (i > 0) {
          printf(" ");
        }else{
          printf("\n");
        }
        
    }
    
    return counter;
}


// TODO(Kirill Soloshenko): Implement `power of` function
int custom_pow(int base, int power) {
  long counter = 0;
  int answ = 1;
  for (; power > 0; power--) {
    answ *= base;
    counter++;
    if (counter > 400000)
    {
      printf("%d", power);
      return 12;
    }
    
  }
  return answ;
}
