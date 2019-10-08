#include <iostream>
#include "timer.h"
#include "Arr2Sum.h"

int main() {
    size_t ROWS = 10000;
    size_t COLS = 10000;

    Arr2Sum a = Arr2Sum(ROWS, COLS);

    {
        Timer timer("sum_by_rows: ");
        cout << a.sum_by_rows() << endl;
    }

    {
        Timer timer("sum_by_cols: ");
        cout << a.sum_by_cols() << endl;
    }
    
    return 0;
}