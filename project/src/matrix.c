#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#include "matrix.h"

#define ERROR_NO_FILE_ACCESS    "--- FILE ACCESS ERROR ---"
#define MEMORY_ALLOCATION_ERROR "--- PROBLEMS WITH MEMORY ALLOCATION---"
#define FILE_SCAN_ERROR         "dirty data in file, aborting..."

enum status {
    STATUS_INVALID_INPUT = -1,
    STATUS_OK
};

/***************** INIT/RELEASE OPERATIONS *****************/

void free_matrix(Matrix* matrix) {
    if (matrix == NULL) {
        return;
    }
    free(matrix->data);
    free(matrix);
}

Matrix* create_matrix(size_t rows, size_t cols) {
    if (rows < 1 || cols < 1) {
        return NULL;
    }
    Matrix *matrix = malloc(sizeof(Matrix));
    if (matrix == NULL) {
        puts(MEMORY_ALLOCATION_ERROR);
        free(matrix);
        return NULL;
    }
    matrix->data = calloc(rows * cols, sizeof(double));
    if (matrix->data == NULL) {
        puts(MEMORY_ALLOCATION_ERROR);
        free_matrix(matrix);
        return NULL;
    }
    matrix->row_count = rows;
    matrix->col_count = cols;
    return matrix;
}



Matrix* create_matrix_from_file(const char* path_file) {
    if (!*path_file) {
        return NULL;
    }
    size_t rows = 0;
    size_t cols = 0;
    FILE *file = fopen(path_file, "r");
    if (file == NULL) {
        puts(ERROR_NO_FILE_ACCESS);
        return NULL;
    }
    fscanf(file, "%zu %zu", &rows, &cols);
    Matrix *matrix = create_matrix(rows, cols);
    double *ptr = matrix->data;
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            if (fscanf(file, "%lf", ptr) != -1) {
                ptr++;
            } else {
                puts(FILE_SCAN_ERROR);
                free_matrix(matrix);
                return NULL;
            }
        }
    }
    fclose(file);
    return matrix;
}


/***************** BASIC OPERATIONS *****************/

int get_rows(const Matrix* matrix, size_t* rows) {
    if (matrix == NULL) {
        return STATUS_INVALID_INPUT;
    }
    *rows = matrix->row_count;
    return STATUS_OK;
}

int get_cols(const Matrix* matrix, size_t* cols) {
    if (matrix == NULL) {
        return STATUS_INVALID_INPUT;
    }
    *cols = matrix->col_count;
    return STATUS_OK;
}

int get_elem(const Matrix* matrix, size_t row, size_t col, double* val) {
    if (matrix == NULL) {
        return STATUS_INVALID_INPUT;
    }
    *val = *(matrix->data + (row * matrix->col_count + col));
    return STATUS_OK;
}

int set_elem(Matrix* matrix, size_t row, size_t col, double val) {
    if (matrix == NULL) {
        return STATUS_INVALID_INPUT;
    }
    *(matrix->data + (row * matrix->col_count + col)) = val;
    return STATUS_OK;
}

/***************** MATH OPERATIONS *****************/



Matrix* mul_scalar(const Matrix* matrix, double val) {
    if (matrix == NULL) {
        return NULL;
    }
    Matrix *new_matrix = create_matrix(matrix->row_count, matrix->col_count);
    if (val == 0.0) {
        return new_matrix;
    }
    for (size_t i = 0; i < matrix->row_count; i++) {
        for (size_t j = 0; j < matrix->col_count; j++) {
            double elem = 0;
            get_elem(matrix, i, j, &elem);
            set_elem(new_matrix, i, j, elem * val);
        }
    }
    return new_matrix;
}



Matrix* transp(const Matrix* matrix) {
    if (matrix == NULL) {
        return NULL;
    }
    size_t rows = matrix->col_count;
    size_t cols = matrix->row_count;
    Matrix *new_matrix = create_matrix(rows, cols);
    for (size_t i = 0; i < cols; i++) {
        for (size_t j = 0; j < rows; j++) {
            double elem = 0.0;
            get_elem(matrix, i, j, &elem);
            set_elem(new_matrix, j, i, elem);
        }
    }
    return new_matrix;
}

static Matrix* double_variable_action(const Matrix* l,
                                      const Matrix* r,
                                      double (*to_do_action)(double, double)) {
    if (l == NULL || r == NULL) {  // assuming "to_do_action" func is always there
        return NULL;
    }
    Matrix *new_matrix = create_matrix(l->row_count, l->col_count);
    for (size_t i = 0; i < l->row_count; i++) {
        for (size_t j = 0; j < l->col_count; j++) {
            double elem1 = 0.0;
            double elem2 = 0.0;
            get_elem(l, i, j, &elem1);
            get_elem(r, i, j, &elem2);
            set_elem(new_matrix, i, j, to_do_action(elem1, elem2));
        }
    }
    return new_matrix;
}

static double subtract(double a, double b) {  // assuming both doubles are always there
    return a - b;
}

static double add(double a, double b) {  // assuming both doubles are always there
    return a + b;
}

Matrix* sum(const Matrix* l, const Matrix* r) {  // all input checks in "double_variable_action" func
    return double_variable_action(l, r, add);
}

Matrix* sub(const Matrix* l, const Matrix* r) {  // all input checks in "double_variable_action" func
    return double_variable_action(l, r, subtract);
}

Matrix* mul(const Matrix* l, const Matrix* r) {
    if (l == NULL || r == NULL) {
        return NULL;
    }
    size_t rows = l->row_count;
    size_t cols = r->col_count;
    Matrix *new_matrix = create_matrix(rows, cols);
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            double total = 0.0;
            for (size_t k = 0; k < l->col_count; k++) {
                double elem1 = 0.0;
                double elem2 = 0.0;
                get_elem(l, i, k, &elem1);
                get_elem(r, k, j, &elem2);
                total = total + elem1 * elem2;
            }
            set_elem(new_matrix, i, j, total);
        }
    }
    return new_matrix;
}

/***************** EXTRA OPERATIONS *****************/

static double return_elem(const Matrix* matrix, size_t row, size_t col) {  // intentionally made "risky"
    double *val = matrix->data + (row * matrix->col_count + col);
    return *val;
}

static Matrix* del_row_n_col(const Matrix *matrix, size_t row, size_t col) {
    size_t rows = matrix->row_count - 1;
    size_t cols = matrix->col_count - 1;
    Matrix *new_matrix = create_matrix(rows, cols);
    double *new_matrix_data_ptr = new_matrix->data;
    for (size_t i = 0; i < matrix->row_count; i++) {
        for (size_t j = 0; j < matrix->col_count; j++) {
            if (i != row && j != col) {
                *new_matrix_data_ptr = return_elem(matrix, i, j);
                new_matrix_data_ptr++;
            }
        }  
    }
    return new_matrix;
}


static double return_det(const Matrix* matrix) {  // intentionally made "risky". "det" func is "safe"
    if (matrix->row_count == 1) {
        return return_elem(matrix, 0, 0);
    } else if (matrix->row_count == 2) {
        double answ = (return_elem(matrix, 0, 0) * return_elem(matrix, 1, 1)) -
                      (return_elem(matrix, 0, 1) * return_elem(matrix, 1, 0));
        return answ;
    } else {
        double sign = 1.0;
        double answ = 0.0;
        for (size_t j = 0; j < matrix->col_count; j++) {
            
            Matrix *minor = del_row_n_col(matrix, 0, j);
            double multiplicator = return_elem(matrix, 0, j);
            double buf = return_det(minor);
            answ += (sign * multiplicator * buf);
            sign *= -1.0;
            free_matrix(minor);
        }
        return answ;  
    }
    
}

int det(const Matrix* matrix, double* val) {   
    if (matrix == NULL || matrix->row_count != matrix->col_count) {
        return STATUS_INVALID_INPUT;
    }

    *val = return_det(matrix);
    return STATUS_OK;
}

Matrix* adj(const Matrix* matrix) {
    if (matrix == NULL || matrix->row_count != matrix->col_count) {
        return NULL;
    } else if (matrix->row_count < 2) {
        return transp(matrix);
    } else {
        size_t rows = matrix->row_count;
        size_t cols = matrix->col_count;
        Matrix *new_matrix = create_matrix(rows, cols);
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                double sign = (i + j) % 2 == 0 ? 1.0 : -1.0;
                Matrix *minor = del_row_n_col(matrix, i, j);
                set_elem(new_matrix, j, i, sign * return_det(minor));
                free_matrix(minor);
            }
        }
        return new_matrix;
    }
}

Matrix* inv(const Matrix* matrix) {
    if (matrix == NULL || matrix->row_count != matrix->col_count){
        return NULL;
    } else if (matrix->row_count == 1) {
        Matrix *inversed = create_matrix(1, 1);
        set_elem(inversed, 0, 0, 1 / return_elem(matrix, 0, 0));  // det always equals 1
        return inversed;
    } else {
        Matrix *adjugate = adj(matrix);
        Matrix *inversed = mul_scalar(adjugate, 1 / return_det(matrix));
        free_matrix(adjugate);
        return inversed;
    }
}



/***************** PRETTY PRINT *****************/
//
// this func has been used during development
//

void pprint(Matrix* matrix) {
    double *ptr = matrix->data;
    for (size_t i = 0; i < matrix->row_count; i++) {
        for (size_t j = 0; j < matrix->col_count; j++) {
            printf("%lf\t", *ptr);
            ptr++;
        }
        printf("\n");
    }
    puts("\n\n");
}
