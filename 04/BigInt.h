#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>

class BigInt {
    char *data;
    bool sign = false;
    size_t idx = 0;
    size_t len = 64;

public:
    void push_back(char a);

    BigInt();

    BigInt(const BigInt &a);

    BigInt(int64_t a);

    BigInt &operator=(const BigInt &a);

    BigInt(BigInt &&moved);

    BigInt &operator=(BigInt&& moved);

    ~BigInt();

    friend std::ostream &operator<<(std::ostream &out, const BigInt &a);

    BigInt operator-() const;

    bool operator==(const BigInt &a) const;

    bool operator!=(const BigInt &a) const;

    bool operator<(const BigInt &a) const;

    bool operator>(const BigInt &a) const;

    bool operator<=(const BigInt &a) const;

    bool operator>=(const BigInt &a) const;

    BigInt abs() const;

    BigInt operator+(const BigInt &a) const;

    BigInt operator-(const BigInt &a) const;
};

#endif