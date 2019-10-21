#ifndef LINEARALLOCATOR_H
#define LINEARALLOCATOR_H


class LinearAllocator {
    char *beg;
    char *end;
    char *cur;
public:
    LinearAllocator(size_t maxSize = 0);

    char *alloc(size_t size);

    void reset();

    ~LinearAllocator();
};

#endif