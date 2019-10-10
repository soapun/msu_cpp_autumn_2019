#include <iostream>
using namespace std;
/*
    Expression :=  Term { ("+" | "-") Term }
    Term       := Factor { ( "*" | "/" ) Factor }
    Factor     := {'-'}Digit{Digit}
    Digit      := "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
 *
*/
int Digit(char **s) {
    return **s - '0';
}

int Factor(char **s) {
    int mul = 1;
    int res = 0;
    int sign = 0;

    while (isspace(**s))
        ++(*s);

    while (**s == '-') {
        sign = 1 - sign;
        ++(*s);
        while (isspace(**s))
            ++(*s);
    }
    while (isdigit(**s)) {
        res *= mul;
        res += Digit(s);
        mul = 10;
        ++(*s);
    }

    while (isspace(**s))
        ++(*s);
    return sign ? -res : res;
}

int Term(char **s) {
    int res;
    res = Factor(s);
    while (**s == '*' || **s == '/') {
        if (**s == '*') {
            ++(*s);
            res *= Factor(s);
        } else if (**s == '/'){
            ++(*s);
            int buf = Factor(s);
            if (res < 0)
                if (buf < 0)
                    res = -res / -buf;
                else
                    res = -(-res / buf) - (-res % buf != 0 ? 1 : 0);
            else if (buf < 0)
                res = -(res / -buf) - (res % -buf != 0 ? 1 : 0);
            else
                res = res / buf;
        }
    }
    return res;
}

int Expression(char **s) {
    int res = Term(s);
    while (**s == '-' || **s == '+') {
        if (**s == '-') {
            ++(*s);
            res -= Term(s);
        } else {
            ++(*s);
            res += Term(s);
        }
    }
    return res;
}

int main(int argc, char **argv) {
    cout << Expression(&argv[1]);
    return 0;
}