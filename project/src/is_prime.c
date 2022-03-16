#include "is_prime.h"

#define PRIME       1  // True
#define NOT_PRIME   0  // False

int is_prime(int number) {
    for (int i = 2; i <= number - 1; i++) {
        if (number % i == 0) {
            return NOT_PRIME;
        }
    }
    return number < 2 ? NOT_PRIME : PRIME;  // Because 0 and 1 are not prime
}
