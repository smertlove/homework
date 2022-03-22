#include "utils.h"
#include "is_prime.h"
#include "print_from_n_to_1.h"
#include <stdio.h>

#define ERR_ARGS_COUNT          -1
#define ERR_WRONG_FLG           -2
#define ERR_STRTOL_FAIL         -3

#define TST_TIMER_FIX            1
#define TST_TIMER_IMPL           2
#define TST_CUSTOM_POWER_IMPL    3
#define TST_RECURSIVE_PRINT_IMPL 4


int main(int argc, const char** argv) {
    if (argc < 3) {
        return ERR_ARGS_COUNT;
    }
    char* end = NULL;
    int test_case = strtol(argv[1], &end, 10);
    if (*end != '\0') {
        return ERR_STRTOL_FAIL;
    }
    const char* data;
    data = argv[2];

    switch (test_case) {
        case TST_TIMER_FIX: {
            int to = strtol(data, &end, 10);
            if (*end != '\0') {
                return ERR_STRTOL_FAIL;
            }
            size_t ticks_count = timer_from(to);
            printf("%zu\n", ticks_count);
            break;
        }
        case TST_TIMER_IMPL: {
            if (argc == 4) {
                int base = strtol(data, &end, 10);
                if (*end != '\0') {
                    return ERR_STRTOL_FAIL;
                }
                int pow =  strtol(argv[3], &end, 10);
                if (*end != '\0') {
                    return ERR_STRTOL_FAIL;
                }
                int res = custom_pow(base, pow);
                printf("%i\n", res);
                break;
            } else {
                return ERR_ARGS_COUNT;
            }
        }
        case TST_CUSTOM_POWER_IMPL: {
            int num = strtol(data, &end, 10);
            if (*end != '\0') {
                return ERR_STRTOL_FAIL;
            }
            int res = is_prime(num);
            printf("%i", res);
            break;
        }
        case TST_RECURSIVE_PRINT_IMPL: {
            int num = strtol(data, &end, 10);
            if (*end != '\0') {
                return ERR_STRTOL_FAIL;
            }
            print_from_n_to_1(num);
            break;
        }
        default: {
            return ERR_WRONG_FLG;
        }
    }
}
