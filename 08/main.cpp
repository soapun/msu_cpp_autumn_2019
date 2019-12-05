#include <iostream>
#include "ThreadPool.h"

int main() {
    ThreadPool pool(8);

    for (int i = 0; i < 20; ++i) {
        cout<<pool.exec([i]() { return i; }).get() << endl;
    }
}