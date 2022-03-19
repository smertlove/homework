#include "is_prime.h"

bool is_prime(int number) {
    if (number == 2) {
        return true;
    }
    for (int i = 3; i * i <= number - 1; i+=2) {
        if (number % i == 0) {
            return false;
        }
    }
    return number < 2 ? false : true;  // Because 0 and 1 are not prime
}
