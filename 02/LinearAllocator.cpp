#include <iostream>
#include "LinearAllocator.h"

LinearAllocator::LinearAllocator(size_t maxSize)
{
    beg = new char [maxSize];
    //std::cout << static_cast<void *>( beg) << std::endl;
    cur = beg;
    end = beg + maxSize;
    //std::cout << static_cast<void *> (end )<< std::endl;

}

char* LinearAllocator::alloc(size_t size)
{
    //std::cout << static_cast<void*>(beg) << " " << static_cast<void *>(cur) << " " << static_cast<void *>(end) << std::endl;
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
