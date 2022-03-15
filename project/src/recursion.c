#include "recursion.h"

void recursive_print(int number){
    if (number != 1)
    {
        recursive_print(number > 1 ? number - 1 : number + 1);
        printf("%i ", number);    
    } else {
        printf("1 ");
        return;
    }  
}