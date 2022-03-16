#include "utils.h"

size_t timer_from(int from) {
    size_t counter = 0;
    for (int i = from; i >= 0; --i) {
        ++counter;
        printf("%d", i);
        if (i > 0) {
          printf(" ");
        } else {
          printf("\n");
        }
    }
    return counter;
}

//     OLD  IMPLIMENTATION O(n)
//
// int custom_pow(int base, int power) {
//   int answ = 1;
//   for (; power > 0; power--) {
//     answ *= base;
//   }
//   return answ;
// }

//      NEW  IMPLIMENTATION O(log(n)) (( наверное... ))
//
int custom_pow(int base, int power) {
  int answer = 1;
  while ( power > 0 ) {
    if (power % 2 == 1) {
      answer *= base;
      power--;
    }
      power /= 2;
      base *= base;
  }
  return answer;
}
