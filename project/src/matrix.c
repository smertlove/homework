#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#include "matrix.h"

#define ERROR_NO_FILE_ACCESS "--- FILE ACCESS ERROR ---"
#define MEMORY_ALLOCATION_ERROR "--- PROBLEMS WITH MEMORY ALLOCATION---"

/***************** INIT/RELEASE OPERATIONS *****************/

void free_matrix(Matrix* matrix){
    free(matrix->data);
    free(matrix);
}

Matrix* create_matrix(size_t rows, size_t cols) {
    Matrix *matrix = calloc(1, sizeof(Matrix));
    if (matrix == NULL) {
        puts(MEMORY_ALLOCATION_ERROR);
        free(matrix);
        return NULL;
    } 
    matrix->data = calloc(rows * cols,  sizeof(double));
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
    size_t rows = 0;
    size_t cols = 0;
    
    FILE *file = fopen(path_file, "r");
    if (file == NULL) {
        puts(ERROR_NO_FILE_ACCESS);
        return NULL;
    }
    
    fscanf(file, "%zu %zu", &rows, &cols);
    Matrix *matrix = create_matrix(rows, cols);
    for (size_t i = 0; i < matrix->row_count; i++) {
        for (size_t j = 0; j < matrix->col_count; j++) {
            fscanf(file, "%lf", &matrix->data[i*sizeof(double)+j]);
        }
    }

    fclose(file);
    return matrix;
}


/***************** BASIC OPERATIONS *****************/

int get_rows(const Matrix* matrix, size_t* rows) {
    *rows = matrix->row_count;
    return 0;
}

int get_cols(const Matrix* matrix, size_t* cols) {
    *cols = matrix->col_count;
    return 0;
}

int get_elem(const Matrix* matrix, size_t row, size_t col, double* val) {
    *val = matrix->data[row*sizeof(double)+col];
    return 0;
}

int set_elem(Matrix* matrix, size_t row, size_t col, double val) {
    matrix->data[row*33+col] = val;
    return 0;
}

/***************** MATH OPERATIONS *****************/

Matrix* mul_scalar(const Matrix* matrix, double val) { 
    Matrix *new_matrix = create_matrix(matrix->row_count, matrix->col_count);
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
    size_t rows = matrix->col_count;
    size_t cols = matrix->row_count;
    Matrix *new_matrix = create_matrix(rows, cols);
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            double elem = 0.0;
            get_elem(matrix, i, j, &elem);
            set_elem(new_matrix, j, i, elem);
        }
    } 
    return new_matrix;
}

static Matrix* double_variable_action(const Matrix* l, const Matrix* r, double (*to_do_action)(double, double)) {
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

static double subtract(double a, double b) {
    return a - b;
}

static double add(double a, double b) {
    return a + b;
}

Matrix* sum(const Matrix* l, const Matrix* r) {
    return double_variable_action(l, r, add);
}

Matrix* sub(const Matrix* l, const Matrix* r) {
    return double_variable_action(l, r, subtract);
}

Matrix* mul(const Matrix* l, const Matrix* r) {
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
// not implemented yet

int det(const Matrix* matrix, double* val) {
    printf("%zu%lf", matrix->col_count, *val);
    return 0;
}
Matrix* adj(const Matrix* matrix) {
    return create_matrix(matrix->row_count, matrix->col_count);
}
Matrix* inv(const Matrix* matrix) {
    return create_matrix(matrix->row_count, matrix->col_count);
}

/***************** PRETTY PRINT *****************/

void pprint(Matrix* matrix) {  // pretty print
    for (size_t i = 0; i < matrix->row_count; i++) {
        for (size_t j = 0; j < matrix->col_count; j++) {    
            printf("%lf\t", matrix->data[i*sizeof(double)+j]);
        }
        printf("\n");
    }
}
