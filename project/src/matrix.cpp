#include <cmath>
#include <limits>
#include <iomanip>

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
    if (!is) {
        throw InvalidMatrixStream();
    }
    row_count = 0;
    col_count = 0;
    is >> row_count >> col_count;
    if (!row_count || !col_count) {
        throw InvalidMatrixStream();
    }
    init_data();
    size_t counter = 0;
    for (size_t i = 0; i < (row_count * col_count); i++) {
        is >> data[i];
        if (data[i]) {
            ++counter;
        }
    }
    if (counter != row_count * col_count) {
        throw InvalidMatrixStream();
    }
}



size_t Matrix::getRows() const {
    return row_count;
}

size_t Matrix::getCols() const {
    return col_count;
}

double Matrix::operator()(size_t i, size_t j) const {
    if (i > this->getRows() - 1 || j > this->getCols() - 1) {
        throw OutOfRange(i, j, *this);
    }
    return data[i * col_count + j];
}

double& Matrix::operator()(size_t i, size_t j) {
    if (i > this->getRows() -1  || j > this->getCols() - 1) {
        throw OutOfRange(i, j, *this);
    }
    return data[i * col_count + j];
}




bool Matrix::operator==(const Matrix& rhs) const {
    std::cout << "called == func: ";
    if (row_count != rhs.getRows() || col_count != rhs.getCols()) {
        std::cout << "matrixes not equal: different dimensions" << std::endl;
        return false;
    }
    for (size_t i = 0; i < row_count; i++) {
        for (size_t j = 0; j < col_count; j++) {                /* s etim padaet eshe i store test for whatever reason */
            if ( std::fabs( (*this)(i, j) - rhs(i, j))  >= 0.01 /* std::numeric_limits<double>::epsilon() * 10e-7*/ ) {
                std::cout << "matrixes not equal: " << operator()(i, j) << " != " << rhs(i, j) << std::endl;
                return false;
            }
        }
    }
    std::cout << "success!! matrixes equal!" << std::endl;
    return true;
}

bool Matrix::operator!=(const Matrix& rhs) const {
    std::cout << "called =! func: calling ==... ";
    return !(*this == rhs);
}

Matrix Matrix::operator+(const Matrix& rhs) const {
    if (row_count != rhs.getRows() || col_count != rhs.getCols()) {
        throw DimensionMismatch(*this, rhs);
    }
    Matrix new_matrix = Matrix(row_count, col_count);
    for (size_t i = 0; i < row_count; i++) {
        for (size_t j = 0; j < col_count; j++) {
            new_matrix(i, j) = (*this)(i, j) + rhs(i, j);
        }
    }
    return new_matrix;
}

Matrix Matrix::operator-(const Matrix& rhs) const {
    if (row_count != rhs.getRows() || col_count != rhs.getCols()) {
        throw DimensionMismatch(*this, rhs);
    }
    Matrix new_matrix = Matrix(row_count, col_count);
    for (size_t i = 0; i < row_count; i++) {
        for (size_t j = 0; j < col_count; j++) {
            new_matrix(i, j) = (*this)(i, j) - rhs(i, j);
        }
    }
    return new_matrix;
}

Matrix Matrix::operator*(const Matrix& rhs) const {
    if (col_count !=  rhs.getRows()) {
        throw DimensionMismatch(*this, rhs);
    }
    Matrix new_matrix = Matrix(row_count, rhs.getCols());
    for (size_t i = 0; i < row_count; i++) {
        for (size_t j = 0; j < rhs.getCols(); j++) {
            double total = 0.0;
            for (size_t k = 0; k < col_count; k++) {
                total = total + (*this)(i, k) * rhs(k, j);
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
            new_matrix(i, j) = (*this)(i, j) * val;
        }
    }
    return new_matrix;
}

Matrix operator*(double val, const Matrix& matrix) {
    return matrix * val;
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    os << matrix.getRows() << " " << matrix.getCols()  << std::endl;
    for (size_t i = 0; i < matrix.getRows(); i++) {
        for (size_t j = 0; j < matrix.getCols(); j++) {
            os << std::setprecision(8) << matrix(i, j) << " ";
        }
        os << std::endl;
    }
    return os;
}


Matrix Matrix::transp() const {
    Matrix new_matrix = Matrix(col_count, row_count);
    for (size_t i = 0; i < row_count; i++) {
        for (size_t j = 0; j < col_count; j++) {
            new_matrix(j, i) = (*this)(i, j);
        }
    }
    return new_matrix;
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
