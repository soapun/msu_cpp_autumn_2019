#include <iostream>
#include "Matrix.h"
#include <cassert>

using namespace std;

int main() {
    Matrix m(3, 3);
    Matrix g(3, 3);
    const Matrix c(3, 3);
    assert(c[2][2] == 4);
    assert(m == g);

    m[2][2] = 1337;

    assert(m[2][2] == 1337);
    assert(m != g);

    assert(m.getRows() == 3);
    assert(m.getColumns() == 3);

    m *= 3;
    assert(g[1][1] == m[1][1] / 3);

    bool flag = false;
    try {
        double x = m[1337][1];
    } catch (out_of_range e) {
        flag = true;
    }

    assert(flag);
    flag = false;

    try {
        double x = m[1][1337];
    } catch (out_of_range e) {
        flag = true;
    }
    assert(flag);
}