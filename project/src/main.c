#include <stdio.h>
#include "matrix.h"


int main(void) {
    Matrix *test_matrix_1 = create_matrix(5, 5);
    for (size_t i = 0; i < test_matrix_1->row_count; i++) {
        set_elem(test_matrix_1, i, i, 6.0);
    }
    pprint(test_matrix_1);
    free_matrix(test_matrix_1);
    Matrix *test_matrix_2 = create_matrix_from_file("./testfile_1.txt");
    Matrix *test_matrix_3 = create_matrix_from_file("./testfile_2.txt");
    Matrix *test_matrix_4 = mul(test_matrix_2, test_matrix_3);
    free_matrix(test_matrix_2);
    free_matrix(test_matrix_3);
    pprint(test_matrix_4);
    puts("\n\nААААА //\\(*w*)/\\\\ ПАВУК");
    return 0;
}



