#include <iostream>
#include "Matrix.h"
#include <cassert>

using namespace std;

int main(void) {
    const size_t rows = 5;
    const size_t cols = 3;

    Matrix m(rows, cols);

    assert(m.getRows() == 5);
    assert(m.getColumns() == 3);

    m[1][2] = 5;
    double x = m[4][1];

    m *= 3;

    Matrix m1(rows, cols);

    if (m1 == m)
    {
    }
}