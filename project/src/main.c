#include <stdio.h>
#include "matrix.h"


int main(void) {
    Matrix *m = create_matrix_from_file("./ff.txt");
    set_elem(m, 3, 0, 23.0);
    // set_elem(m, 2, 3, 5.7);
    // m->data[4] = 2.3;
    Matrix *mm = mul_scalar(m, 7.0);
    free_matrix(m);
    Matrix *mmm = transp(mm);
    pprint(mmm);

    size_t v1 = 0;
    size_t v2 = 0;
    get_rows(m, &v1);
    get_cols(m, &v2);
    printf("%zu %zu\n", v1, v2);

    double v3 = 0;
    double v4 = 0;
    get_elem(m, 1, 1, &v3);
    get_elem(m, 3, 0, &v4);
    printf("%lf %lf\n", v3, v4);


    free_matrix(m);
    // printf("%d\n", get_rows(m, m->row_count));
    return 0;
}



