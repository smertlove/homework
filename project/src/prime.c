#include "prime.h"

int is_prime(int number) {
    long counter = 0;
    for (int i = 2; i <= number - 1; i++) {
        if ( number % i == 0) {
            return 0;
        }    
    }
    return number < 2 ? 0 : 1; 
    
}