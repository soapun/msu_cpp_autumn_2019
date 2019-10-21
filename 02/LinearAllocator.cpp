#include <iostream>
#include "LinearAllocator.h"

LinearAllocator::LinearAllocator(size_t maxSize)
{
    beg = new char[maxSize];
    cur = beg;
    end = beg + maxSize;

}

char* LinearAllocator::alloc(size_t size)
{
    if (size > end - cur) {
        return nullptr;
    } else {
        char *buf = cur;
        cur += size;
        return buf;
    }
}

void LinearAllocator::reset()
{
    cur = beg;
}

LinearAllocator::~LinearAllocator()
{
    delete[] beg;
}
