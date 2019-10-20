#include <iostream>
#include "LinearAllocator.h"

using namespace std;

int main(void) {
    LinearAllocator x = LinearAllocator(6);
    std::cout << static_cast<void *>(x.alloc(3)) << ' ' << static_cast<void *>(x.alloc(4)) << std::endl;
    x.reset();
    std::cout << static_cast<void *>(x.alloc(4)) << std::endl;

}