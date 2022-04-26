#include "matrix.h"
#include "exceptions.h"

namespace prep {


void Matrix::init_data(){
    data =  new double[row_count * col_count];
}

Matrix::Matrix(size_t rows, size_t cols) {
    row_count = rows;
    col_count = cols;
    init_data();
    for (size_t i = 0; i < row_count * col_count; i++) {
        data[i] = 0.0;
    }
}

Matrix::Matrix(std::istream& is) {
    is >> row_count >> col_count;
    init_data();
    for (size_t i = 0; i < (row_count * col_count); i++) {
        is >> data[i];
    }
}

Matrix::getRows() {
    return row_count;
}

Matrix::getCols() {
    return col_count;
}

Matrix::operator()(size_t i, size_t j) {
    return &data[i * col_count + j];
}

Matrix::operator()(size_t i, size_t j) const {
    return data[i * col_count + j];
}

Matrix::operator==(const Matrix& rhs) const {
    if (this->row_count != rhs::getRows() || this->col_count != rhs::getCols()) {
        return false;
    }
    for (size_t i = 0; i < row_count; i++) {
        for (size_t i = 0; i < col_count; i++) {
            if (this(i, j) != rhs(i, j)) {
                return false;
            }
        }
    }
    return true;
}

Matrix::operator!=(const Matrix& rhs) {
    return !(this->operator==(rhs));
}

Matrix::operator+(const Matrix& rhs) const {
    Matrix new_matrix = new Matrix(row_count, col_count);
    for (size_t i = 0; i < row_count; i++) {
        for (size_t j = 0; j < col_count; j++) {
            new_matrix(i, j) = this(i, j) + rhs(i, j);
        }
    }
    return new_matrix;
}

Matrix::operator-(const Matrix& rhs) const {
    Matrix new_matrix = new Matrix(row_count, col_count);
    for (size_t i = 0; i < row_count; i++) {
        for (size_t j = 0; j < col_count; j++) {
            new_matrix(i, j) = this(i, j) - rhs(i, j);
        }
    }
    return new_matrix;
}

Matrix::operator*(const Matrix& rhs) const {
    Matrix new_matrix = new Matrix(row_count, rhs::getCols());
    for (size_t i = 0; i < row_count; i++) {
        for (size_t j = 0; j < rhs::getCols(); j++) {
            double total = 0.0;
            for (size_t k = 0; k < col_count; k++) {
                total = total + this(i, k) * rhs(k, j);
            }
            new_matrix(i, j) = total;
        }
    }
    return new_matrix;
}

Matrix::operator*(double val) const {
    Matrix new_matrix = new Matrix(row_count, rhs::getCols());
    for (size_t i = 0; i < row_count; i++) {
        for (size_t j = 0; j < col_count; j++) {
            new_matrix(i, j) = this(i, j) * val;
        }
    }
}

Matrix operator*(double val, const Matrix& matrix) {
    return matrix * val;
}

Matrix::transp() const {
    return this;
}

Matrix::det() const {
    return this;
}

Matrix::adj() const {
    return this;
}

Matrix inv() {
    return this;
}

}  // namespace prep
