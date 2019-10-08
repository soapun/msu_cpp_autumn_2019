class Arr2Sum
{
    size_t rows;
    size_t cols;
    int **arr;
public:
    Arr2Sum(size_t _rows = 10, size_t _cols = 10);
    uint64_t sum_by_rows() const;
    uint64_t sum_by_cols() const;
    ~Arr2Sum();
};