#include <iostream>
#include "BigInt.h"
#include <limits.h>
#include <sstream>
#include <limits>

using namespace std;

int main()
{
    BigInt x=LLONG_MAX;
    BigInt y=LLONG_MAX;
    x = BigInt(10);
    cout<<x<<endl;
    cout << x + y << endl;

}