#include <iostream>
#include <cstring>
#include "BigInt.h"

BigInt::BigInt() {
    data = new char[len];
    push_back(0);
}

void BigInt::push_back(char a) {
    data[idx] = a;
    ++idx;

    if (idx == len) {
        char *tmp = new char[len << 1];
        for (size_t i = 0; i < len; ++i)
            tmp[i] = data[i];
        len <<= 1;
        delete[] data;
        data = tmp;
    }
}


BigInt::BigInt(const BigInt &a) : sign(a.sign), len(a.len), idx(a.idx) {
    data = new char[len];
    for (size_t i = 0; i < idx; ++i)
        data[i] = a.data[i];
}

BigInt::BigInt(int64_t a = 0) {
    if (a < 0) {
        sign = true;
    }

    data = new char[len];

    if (!a) {
        push_back(0);
        return;
    }

    push_back(a < 0 ? -(a % 10) : (a % 10));
    a /= 10;
    if (a < 0)
        a = -a;

    while (a) {
        push_back(a % 10);
        a /= 10;
    }
}

BigInt &BigInt::operator=(const BigInt &a) {
    if (this == &a)
        return *this;

    idx = a.idx;
    len = a.len;
    sign = a.sign;

    delete[] data;
    data = new char[len];
    std::memcpy(data, a.data, idx);
    return *this;
}

BigInt::BigInt(BigInt &&moved)
        : sign(std::move(moved.sign)), idx(std::move(moved.idx)), len(std::move(moved.len)) {
    using std::swap;
    data = nullptr;
    swap(data, moved.data);
}

BigInt &BigInt::operator=(BigInt &&moved) {
    if (this == &moved)
        return *this;

    sign = std::move(moved.sign);
    idx = std::move(moved.idx);
    len = std::move(moved.len);


    using std::swap;
    swap(data, moved.data);


    return *this;
}

BigInt::~BigInt() {
    delete[] data;
}

std::ostream &operator<<(std::ostream &out, const BigInt &a) {
    if (a.sign) {
        out << '-';
    }

    for (int i = a.idx - 1; i >= 0; --i) {
        out << char('0' + a.data[i]);
    }
    return out;
}

BigInt BigInt::operator-() const {
    BigInt res(*this);
    if (idx == 1 && !data[0])
        return res;
    res.sign = !res.sign;
    return res;
}

bool BigInt::operator==(const BigInt &a) const {
    if (idx != a.idx || sign != a.sign)
        return false;

    for (size_t i = 0; i < idx; ++i) {
        if (data[i] != a.data[i])
            return false;
    }

    return true;
}

bool BigInt::operator!=(const BigInt &a) const {
    return !operator==(a);
}

bool BigInt::operator<(const BigInt &a) const {
    if (sign && !a.sign)
        return true;
    if (a.sign && !sign)
        return false;

    if (idx < a.idx) {
        return !sign;
    } else if (a.idx < idx) {
        return sign;
    }

    for (int i = idx - 1; i >= 0; --i) {
        if (data[i] < a.data[i]) {
            return !sign;
        } else if (data[i] > a.data[i]) {
            return sign;
        }
    }

    return false;
}

bool BigInt::operator>(const BigInt &a) const {
    return !operator<(a) && operator!=(a);
};

bool BigInt::operator<=(const BigInt &a) const {
    return !operator>(a);
}

bool BigInt::operator>=(const BigInt &a) const {
    return !operator<(a);
}

BigInt BigInt::abs() const {
    BigInt res(*this);
    res.sign = false;
    return res;
}


BigInt BigInt::operator+(const BigInt &a) const {
    if (!sign && a.sign) {
        return *this - a.abs();
    } else if (sign && !a.sign) {
        return a - (*this).abs();
    }

    BigInt res(*this);
    char carry = 0;
    if (a.idx > res.idx) {
        for (size_t i = res.idx; i < a.idx; ++i) {
            res.push_back(0);
        }
    }

    for (size_t i = 0; i < a.idx; ++i) {
        char sum = res.data[i] + a.data[i] + carry;
        res.data[i] = sum % 10;
        carry = sum / 10;

    }
    if (a.idx < res.idx) {
        for (size_t i = a.idx; i < res.idx; ++i) {
            char sum = res.data[i] + carry;
            res.data[i] = sum % 10;
            carry = sum / 10;
        }
    }
    if (carry)
        res.push_back(carry);

    if (res.idx == 1 && !res.data[0])
        res.sign = false;

    return res;
}

BigInt BigInt::operator-(const BigInt &a) const {
    if (!sign && a.sign) {
        return *this + a.abs();
    }

    if (sign && !a.sign) {
        return -(abs() + a);
    }

    if (sign && a.sign) {
        return a.abs() + *this;
    }

    if (*this < a) {
        return -(a - *this);
    }

    BigInt res(*this);
    char carry = 0;

    for (size_t i = 0; i < a.idx; ++i) {
        char dif = res.data[i] - a.data[i] - carry;
        res.data[i] = dif + ((dif < 0) ? 10 : 0);

        carry = (dif < 0);
    }

    for (size_t i = a.idx; i < res.idx; ++i) {
        char dif = res.data[i] - carry;

        res.data[i] = dif + ((dif < 0) ? 10 : 0);
        carry = (dif < 0);
    }

    for (size_t i = res.idx - 1; i > 0; --i) {
        if (res.data[i] > 0) {
            break;
        }

        res.idx--;
    }

    if (res.idx == 1 && !res.data[0])
        res.sign = false;

    return res;
}

