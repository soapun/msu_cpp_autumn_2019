#include <iostream>
#include <limits.h>
#include "BigInt.h"

void check(int64_t x, int64_t y)
{
    const BigInt bigX = x;
    const BigInt bigY = y;

    if (bigX + bigY != BigInt(x + y))
    {
        std::cout << x << " + " << y << " != " << x + y << " got " << bigX + bigY << '\n';
    }

    if (bigX - bigY != BigInt(x - y))
    {
        std::cout << x << " - " << y << " != " << x - y << " got " << bigX - bigY << '\n';
    }
}

#define checkTrue(cond) if (!(cond)) std::cout << "at line " << __LINE__ << ": " << #cond << '\n';

int main()
{
    BigInt x = 1;
    checkTrue(x == BigInt(1));
    BigInt y = x;
    checkTrue(y == BigInt(1));
    BigInt z;
    checkTrue(z == BigInt(0));

    checkTrue(x == y);
    checkTrue(y == x);
    checkTrue(x != z);
    checkTrue(z != x);

    z = y;
    checkTrue(z == BigInt(1));

    x = 1;
    checkTrue(x == BigInt(1));

    checkTrue(!(x < x));
    checkTrue(x < 2);
    checkTrue(!(BigInt(3) < x));
    checkTrue(BigInt(-3) < x);
    checkTrue(BigInt(-3) < BigInt(-2));

    checkTrue(!(x > x));
    checkTrue(BigInt(2) > x);
    checkTrue(!(x > BigInt(3)));
    checkTrue(x > BigInt(-3));
    checkTrue(BigInt(-2) > BigInt(-3));

    checkTrue(x <= x);
    checkTrue(x <= 2);
    checkTrue(!(BigInt(3) <= x));
    checkTrue(BigInt(-3) <= x);
    checkTrue(BigInt(-3) <= BigInt(-2));

    checkTrue(x >= x);
    checkTrue(BigInt(2) >= x);
    checkTrue(!(x >= BigInt(3)));
    checkTrue(x >= BigInt(-3));
    checkTrue(BigInt(-2) >= BigInt(-3));
    checkTrue(BigInt(0) == -BigInt(0));

    checkTrue(BigInt(10) + BigInt(10) == BigInt(20));
    checkTrue(BigInt(-10) + BigInt(10) == BigInt(0));
    checkTrue(BigInt(10) + BigInt(-10) == BigInt(0));
    checkTrue(BigInt(-10) + BigInt(-10) == BigInt(-20));

    checkTrue(BigInt(10) - BigInt(10) == BigInt(0));
    checkTrue(BigInt(-10) - BigInt(10) == BigInt(-20));
    checkTrue(BigInt(10) - BigInt(-10) == BigInt(20));
    checkTrue(BigInt(-10) - BigInt(-10) == BigInt(0));

    checkTrue(BigInt(0) + BigInt(-1) == BigInt(-1));
    checkTrue(BigInt(0) - BigInt(1) == BigInt(-1));

    checkTrue(BigInt(100) - BigInt(100) ==  BigInt(0));
    checkTrue(BigInt(99) - BigInt(100) == BigInt(-1));
    checkTrue(BigInt(10) - BigInt(11) == BigInt(-1));
    checkTrue(BigInt(20) - BigInt(19) == BigInt(1));

    for (int i = -100; i <= 100; ++i)
    {
        for (int j = -100; j <= 100; ++j)
        {
            check(i, j);
        }
    }


    const BigInt big1 = LLONG_MAX;
    checkTrue(big1 == BigInt(9223372036854775807));

    const BigInt big2 = big1 + big1;
    const BigInt big3 = big2 - big1;
    checkTrue(big3 == BigInt(9223372036854775807));

    std::cout << "Done.\n";

    return 0;
}