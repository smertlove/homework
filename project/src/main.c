#include <stdio.h>
#include "matrix.h"



void case1(void) {
    Matrix *m = create_matrix_from_file("./ff.txt");
    pprint(m);
    Matrix *mm = create_matrix_from_file("./fff.txt");
    pprint(mm);
}

void case2(void) {
    Matrix *m = create_matrix_from_file("./ff.txt");
    set_elem(m, 0, 3, 9.0);
    set_elem(m, 3, 0, 7.0);
    set_elem(m, 3, 3, 9.0);
    set_elem(m, 0, 1, 6.0);
    set_elem(m, 0, 2, 5.0);
    pprint(m);
    Matrix *mm = mul_scalar(m, 2.0);
    pprint(mm);

    Matrix *mmm = mul_scalar(mm, 3.0);
    pprint(mmm);
}


int main(void) {
    case1();
    // case2();
    return 0;
}



