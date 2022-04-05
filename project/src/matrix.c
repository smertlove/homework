#include <stdio.h>
#include <malloc.h>

#include "matrix.h"

#define ERROR_NO_FILE_ACCESS "--- FILE ACCESS ERROR ---"

Matrix* create_matrix(size_t rows, size_t cols) {
    Matrix *matrix = malloc(sizeof(Matrix));
    if (matrix == NULL)
    {
        puts("you fucked up");
    }
    
    printf("%zu\n", sizeof(matrix));
    matrix->data = calloc(rows * cols,  sizeof(double));
    if (matrix->data == NULL)
    {
        puts("you fucked up");
    }
    printf("%zu %zu\n---\n", sizeof(matrix->data), sizeof(double));
    matrix->row_count = rows;
    matrix->col_count = cols;
    return matrix;
}

void free_matrix(Matrix* matrix){
    free(matrix->data);
    free(matrix);
}

Matrix* create_matrix_from_file(const char* path_file) {
    size_t rows = 0;
    size_t cols = 0;
    
    FILE *file = fopen(path_file, "r");
    if (file == NULL) {
        puts(ERROR_NO_FILE_ACCESS);
    }
    
    fscanf(file, "%zu %zu", &rows, &cols);
    Matrix *matrix = create_matrix(rows, cols);
    matrix->row_count = rows;
    matrix->col_count = cols;
    for (size_t i = 0; i < matrix->row_count; i++) {
        for (size_t j = 0; j < matrix->col_count; j++) {
            fscanf(file, "%lf", &matrix->data[i*8+j]);
        }
    }

    fclose(file);
    return matrix;
}

int get_rows(const Matrix* matrix, size_t* rows) {
    *rows = matrix->row_count;
    return 0;
}

int get_cols(const Matrix* matrix, size_t* cols) {
    *cols = matrix->col_count;
    return 0;
}

int get_elem(const Matrix* matrix, size_t row, size_t col, double* val) {
    *val = matrix->data[row * sizeof(val) + col];
    return 0;
}

int set_elem(Matrix* matrix, size_t row, size_t col, double val) {
    matrix->data[row * sizeof(val) + col] = val;
    return 0;
}

Matrix* copy_matrix(const Matrix* old_matrix) {
    Matrix *new_matrix = create_matrix(old_matrix->row_count, old_matrix->col_count);
    for (size_t i = 0; i < old_matrix->row_count; i++) {
        for (size_t j = 0; j < old_matrix->col_count; j++) {
            double cur_value = 0.0;
            get_elem(old_matrix, i, j, &cur_value);
            set_elem(new_matrix, i, j, cur_value);
        }  
    }  
    return new_matrix;
}

/***********************************/
Matrix* mul_scalar(const Matrix* matrix, double val) {
    
    Matrix *new_matrix = copy_matrix(matrix);
    for (size_t i = 0; i < matrix->row_count; i++) {
        for (size_t j = 0; j < matrix->col_count; j++) {
            double cur_value = 0.0;
            get_elem(matrix, i, j, &cur_value);
            set_elem(new_matrix, i, j, cur_value * val);
        }
    }
    return new_matrix;
}

Matrix* transp(const Matrix* matrix) {
    size_t cols = matrix->col_count;
    size_t rows = matrix->row_count;
    Matrix *new_matrix = create_matrix(cols, rows);
    for (size_t i = 0; i < matrix->row_count; i++) {
        for (size_t j = 0; j < matrix->col_count; j++) {
            double cur_value = 0.0;
            get_elem(matrix, i, j, &cur_value);
            set_elem(new_matrix, j, i, cur_value);
        }
    } 
    return new_matrix;
}





void pprint(Matrix* matrix) {  // pretty print
    for (size_t i = 0; i < matrix->row_count; i++) {
        for (size_t j = 0; j < matrix->col_count; j++) {
            printf("%2f\t", matrix->data[i*8+j]);
        }
        printf("\n");
    }
}