#include <iostream>
#include <stdexcept>

using namespace std;

/*
    Expression :=  Term { ("+" | "-") Term }
    Term       := Factor { ( "*" | "/" ) Factor }
    Factor     := {'-'}Digit{Digit}
    Digit      := "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
*/
int Digit(const string &src, size_t &i) {
    return src[i] - '0';
}

int Factor(const string &src, size_t &i) {
    int mul = 1;
    int res = 0;
    int sign = 0;

    while (isspace(src[i]))
        ++i;

    while (src[i] == '-') {
        sign = 1 - sign;
        ++i;
        while (isspace(src[i]))
            ++i;
    }

    if (!(isdigit(src[i])))
        throw invalid_argument("String is not an expression.");
    while (isdigit(src[i])) {
        res *= mul;
        res += Digit(src, i);
        mul = 10;
        ++i;
    }

    while (isspace(src[i]))
        ++i;
    return sign ? -res : res;
}

int Term(const string &src, size_t &i) {
    int res;
    res = Factor(src, i);
    while (src[i] == '*' || src[i] == '/') {
        if (src[i] == '*') {
            ++i;
            res *= Factor(src, i);
        } else if (src[i] == '/') {
            ++i;
            int buf = Factor(src, i);
            if (!buf)
                throw runtime_error("Division by zero attempted.");
            res /= buf;
        }
    }
    return res;
}

int Expression(const string &src, size_t &i) {
    int res = Term(src, i);
    while (src[i] == '-' || src[i] == '+') {
        if (src[i] == '-') {
            ++i;
            res -= Term(src, i);
        } else {
            ++i;
            res += Term(src, i);
        }
    }
    if (src[i] != '\0')
        throw invalid_argument("String is not an expression.");
    return res;
}

int main(int argc, char **argv) {
    int res;
    size_t i = 0;
    string src(argv[1]);
    try {
        res = Expression(src, i);
        cout << res;
    }
    catch (const invalid_argument &msg) {
        cout << msg.what();
    }
    catch (const runtime_error &msg) {
        cout << msg.what();
    }
    return 0;
}