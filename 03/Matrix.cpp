#include <iostream>
#include "Matrix.h"


Matrix::Row::Row(int **_parent, size_t _row, size_t _col) : parent(_parent), row(_row), col(_col) {}

int &Matrix::Row::operator[](size_t _col) {
    if (_col >= col)
        throw std::out_of_range("");
    return parent[row][_col];
}

const int &Matrix::Row::operator[](size_t _col) const {
    if (_col >= col)
        throw std::out_of_range("");
    return parent[row][_col];
}


Matrix::Matrix(size_t _rows, size_t _cols) : rows(_rows), cols(_cols) {
    arr = new int *[rows];
    for (size_t i = 0; i < rows; ++i) {
        arr[i] = new int[cols];
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

Matrix &Matrix::operator*=(int x) {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            arr[i][j] *= x;
        }
    }
    return *this;
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
    return Row(arr, row, cols);
}

const Matrix::Row Matrix::operator[](size_t row) const {
    if (row >= rows)
        throw std::out_of_range("");
    return Row(arr, row, cols);
}

Matrix::~Matrix() {
    for (size_t i = 0; i < rows; ++i)
        delete[] arr[i];
    delete[] arr;
}