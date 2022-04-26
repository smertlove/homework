#include <cmath>
#include <limits>

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



size_t Matrix::getRows() const {
    return row_count;
}

size_t Matrix::getCols() const {
    return col_count;
}

double Matrix::operator()(size_t i, size_t j) const {
    return data[i * col_count + j];
}

double& Matrix::operator()(size_t i, size_t j) {
    return data[i * col_count + j];
}

// Matrix::Matrix(const Matrix& rhs) {
//     row_count = rhs.getRows();
//     col_count = rhs.getCols();
//     init_data();
//     for (size_t i = 0; i < row_count; i++) {
//         for (size_t j = 0; j < col_count; i++) {
//             this->operator()(i, j) = rhs(i, j);
//         }
//     }
// }


bool Matrix::operator==(const Matrix& rhs) const {
    if (row_count != rhs.getRows() || col_count != rhs.getCols()) {
        return false;
    }
    for (size_t i = 0; i < row_count; i++) {
        for (size_t j = 0; j < col_count; j++) {
            if ( std::fabs(operator()(i, j) - rhs(i, j)) >= 1e-07 ) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix& rhs) const {
    return !(operator==(rhs));
}

Matrix Matrix::operator+(const Matrix& rhs) const {
    Matrix new_matrix = Matrix(row_count, col_count);
    for (size_t i = 0; i < row_count; i++) {
        for (size_t j = 0; j < col_count; j++) {
            new_matrix(i, j) = operator()(i, j) + rhs(i, j);
        }
    }
    return new_matrix;
}

Matrix Matrix::operator-(const Matrix& rhs) const {
    Matrix new_matrix = Matrix(row_count, col_count);
    for (size_t i = 0; i < row_count; i++) {
        for (size_t j = 0; j < col_count; j++) {
            new_matrix(i, j) = operator()(i, j) - rhs(i, j);
        }
    }
    return new_matrix;
}

Matrix Matrix::operator*(const Matrix& rhs) const {
    Matrix new_matrix = Matrix(row_count, rhs.getCols());
    for (size_t i = 0; i < row_count; i++) {
        for (size_t j = 0; j < rhs.getCols(); j++) {
            double total = 0.0;
            for (size_t k = 0; k < col_count; k++) {
                total = total + operator()(i, k) * rhs(k, j);
            }
            new_matrix(i, j) = total;
        }
    }
    return new_matrix;
}

Matrix Matrix::operator*(double val) const {
    Matrix new_matrix = Matrix(row_count, col_count);
    for (size_t i = 0; i < row_count; i++) {
        for (size_t j = 0; j < col_count; j++) {
            new_matrix(i, j) = operator()(i, j) * val;
        }
    }
    return new_matrix;
}

Matrix operator*(double val, const Matrix& matrix) {
    return matrix * val;
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    os << "Matrix( " << matrix.getRows() << "x" << matrix.getCols() << " )" << std::endl;
    for (size_t i = 0; i < matrix.getRows(); i++) {
        for (size_t j = 0; j < matrix.getCols(); j++) {
            os << matrix(i, j) << "  \t";
        }
        os << std::endl;
    }
    return os;
}


Matrix Matrix::transp() const {
    return Matrix(row_count, col_count);
}

double Matrix::det() const {
    return 10.0;
}

Matrix Matrix::adj() const {
    return Matrix(row_count, col_count);
}

Matrix Matrix::inv() const {
    return Matrix(row_count, col_count);
}

}  // namespace prep
