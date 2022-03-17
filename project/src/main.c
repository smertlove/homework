#include "utils.h"
#include "is_prime.h"
#include "print_from_n_to_1.h"

#define ERR_ARGS_COUNT (-1)
#define ERR_WRONG_FLG (-2)

#define TST_TIMER_FIX            1
#define TST_TIMER_IMPL           2
#define TST_CUSTOM_POWER_IMPL    3
#define TST_RECURSIVE_PRINT_IMPL 4


int main(int argc, const char** argv) {
    if (argc < 3) {
        return ERR_ARGS_COUNT;
    }

    int Test_case = strtol(argv[1], NULL, 10);
    const char* data;
    data = argv[2];

    switch (Test_case) {
        case TST_TIMER_FIX: {
            int to = strtol(data, NULL, 10);
            size_t ticks_count = timer_from(to);
            printf("%zu\n", ticks_count);
            break;
        }
        case TST_TIMER_IMPL: {
            if (argc == 4) {
                int base = strtol(data, NULL, 10);
                int pow =  strtol(argv[3], NULL, 10);
                int res = custom_pow(base, pow);
                printf("%i\n", res);
                break;
            } else {
                return ERR_ARGS_COUNT;
            }
        }
        case TST_CUSTOM_POWER_IMPL: {
            int num = strtol(data, NULL, 10);
            int res = is_prime(num);
            printf("%i", res);
            break;
        }
        case TST_RECURSIVE_PRINT_IMPL: {
            int num = strtol(data, NULL, 10);
            print_from_n_to_1(num);
            break;
        }
        default: {
            return ERR_WRONG_FLG;
        }
    }
}
