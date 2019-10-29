#ifndef MATRIX_H
#define MATRIX_H

class Matrix {
    size_t rows;
    size_t cols;
    int **arr;

    class Row {
        friend class Matrix;

        int **parent;
        size_t row;
        size_t col;

        Row(int **_parent, size_t _row, size_t _col);

    public:
        int &operator[](size_t col);

        const int &operator[](size_t col) const;
    };

public:

    Matrix(size_t _rows = 10, size_t _cols = 10);

    ~Matrix();

    size_t getRows() const;

    size_t getColumns() const;

    bool operator==(const Matrix &) const;

    bool operator!=(const Matrix &) const;

    Matrix &operator*=(int x);

    Row operator[](size_t row);

    const Row operator[](size_t row) const;

    void print() const;
};

#endif
