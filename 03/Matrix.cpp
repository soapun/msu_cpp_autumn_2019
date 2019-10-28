#include <iostream>
#include "Matrix.h"


Matrix::Row::Row(Matrix &_parent, size_t _row) : parent(_parent), row(_row) {}

int &Matrix::Row::operator[](size_t col) {
    if (col >= parent.cols)
        throw std::out_of_range("");
    return parent.arr[row][col];
}

const int &Matrix::Row::operator[](size_t col) const {
    if (col >= parent.cols)
        throw std::out_of_range("");
    return parent.arr[row][col];
}


Matrix::Matrix(size_t _rows, size_t _cols) : rows(_rows), cols(_cols) {
    arr = (int **) malloc(rows * sizeof(*arr) + rows * cols * sizeof(**arr));
    int *buf = (int *) (arr + rows);
    for (size_t i = 0; i < rows; ++i) {
        arr[i] = buf + i * cols;
        for (size_t j = 0; j < cols; ++j)
            arr[i][j] = i + j;
    }
}

size_t Matrix::getRows() const {
    return rows;
}

size_t Matrix::getColumns() const {
    return cols;
}

bool Matrix::operator==(const Matrix &a) const {
    for (size_t i = 0; i < a.rows; ++i) {
        for (size_t j = 0; j < a.cols; ++j) {
            if (arr[i][j] != a.arr[i][j])
                return false;
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix &a) const {
    return !(*this == a);
}

void Matrix::operator*=(int x) {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            arr[i][j] *= x;
        }
    }
}

void Matrix::print() const {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j)
            std::cout << arr[i][j] << " ";
        std::cout << std::endl;
    }
}

Matrix::Row Matrix::operator[](size_t row) {
    if (row >= rows)
        throw std::out_of_range("");
    return Row(*this, row);
}

Matrix::~Matrix() {
    free(arr);
}