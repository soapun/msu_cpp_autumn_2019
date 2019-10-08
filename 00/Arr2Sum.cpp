#include <iostream>
#include "Arr2Sum.h"

Arr2Sum::Arr2Sum(size_t _rows, size_t _cols) : rows(_rows), cols(_cols)
{
    arr = (int **)malloc(rows * sizeof(*arr) + rows * cols * sizeof(**arr));
    int * buf = (int *)(arr + rows);
    for (size_t i = 0; i < rows; ++i){
        arr[i] = buf + i * cols;
        for (size_t j = 0; j < cols; ++j)
            arr[i][j] = i + j;
    }
}

uint64_t Arr2Sum::sum_by_rows() const
{
    uint64_t sum = 0;
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            sum += arr[i][j];
    return sum;
}

uint64_t Arr2Sum::sum_by_cols() const
{
    uint64_t sum = 0;
    for (size_t j = 0; j < cols; ++j)
        for (size_t i = 0; i < rows; ++i)
            sum += arr[i][j];
    return sum;
}

Arr2Sum::~Arr2Sum()
{
    free (arr);
}