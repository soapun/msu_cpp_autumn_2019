#ifndef VECTOR_H
#define VECTOR_H

template<class T>
class Allocator {
public:
    T *allocate(size_t n) {
        return static_cast<T *>(operator new[](n * sizeof(T)));
    }

    void deallocate(T *ptr, size_t n) {
        operator delete[](ptr, n * sizeof(T));
    }

    template<class... Args>
    void construct(T *ptr, Args &&... args) {
        ::new(ptr) T(std::forward<Args>(args)...);
    }

    void destruct(T *ptr) {
        ptr->~T();
    }

    size_t max_size() const noexcept {
        return std::numeric_limits<size_t>::max();
    }
};

template<class T>
class Iterator : public std::iterator<std::random_access_iterator_tag, T> {
    T *ptr_;
public:
    template<T>
    friend Iterator<T> operator+(int step, Iterator<T> it);

    explicit Iterator(T *ptr) : ptr_(ptr) {}

    T &operator*() const {
        return *ptr_;
    }

    bool operator==(const Iterator<T> &other) const {
        return ptr_ == other.ptr_;
    }

    bool operator!=(const Iterator<T> &other) const {
        return !(*this == other);
    }

    bool operator<(const Iterator<T> &other) {
        return (operator-(other) > 0);
    }

    bool operator>(const Iterator<T> &other) {
        return other < *this;
    }

    bool operator>=(const Iterator<T> &other) {
        return !(*this < other);
    }

    bool operator<=(const Iterator<T> &other) {
        return !(*this > other);
    }

    Iterator<T> &operator++() {
        ++ptr_;
        return *this;
    }

    Iterator<T> &operator--() {
        --ptr_;
        return *this;
    }

    Iterator<T> &operator[](int idx) {
        return *(ptr_ + idx);
    }

    Iterator<T> &operator+=(int step) {
        ptr_ += step;
        return *this;
    }

    Iterator<T> operator-=(int step) {
        return *this += -step;
    }

    std::ptrdiff_t operator-(const Iterator<T> &other) {
        return ptr_ - other.ptr_;
    }
};

template<class T>
Iterator<T> operator+(int step, Iterator<T> it) {
    return Iterator<T>(it.ptr_ + step);
}


template<class T, class Alloc = Allocator<T>>
class Vector {
private:
    Alloc alloc_;
    T *data_;
    size_t size_;
    size_t max_size_;

public:
    Vector() : size_(0), max_size_(5) {
        data_ = alloc_.allocate(max_size_);
    }

    Vector(size_t size) : size_(size), max_size_(size + 5) {
        data_ = alloc_.allocate(max_size_);
        for (size_t i = 0; i < size; ++i)
            alloc_.construct(data_[i]);
    }

    Vector(const Vector &other) : size_(other.size_), max_size_(other.max_size_) {
        data_ = alloc_.allocate(max_size_);
        for (size_t i = 0; i < size_; ++i) {
            alloc_.construct(data_ + i, other.data_[i]);
        }
    }

    Vector(Vector &&other) :
            size_(other.size_),
            max_size_(other.max_size_),
            data_(other.data_) {
        other.data_ = nullptr;
    }

    void clear() {
        for (size_t i = 0; i < size_; ++i) {
            alloc_.destruct(data_ + i);
        }
        size_ = 0;
    }

    ~Vector() {
        clear();
        alloc_.deallocate(data_, max_size_);
    }

    Iterator<T> begin() {
        return Iterator<T>(data_);
    }

    Iterator<T> end() {
        return Iterator<T>(data_ + size_);
    }

    std::reverse_iterator <Iterator<T>> rbegin() {
        return std::reverse_iterator<Iterator<T>>(this->end());
    }

    std::reverse_iterator <Iterator<T>> rend() {
        return std::reverse_iterator<Iterator<T>>(this->begin());
    }

    size_t size() const {
        return size_;
    }

    bool empty() const {
        return !size_;
    }

    size_t capacity() const {
        return max_size_;
    }

    T &operator[](size_t idx) {
        if (idx < size_)
            return data_[idx];
        throw std::out_of_range("index is out of range");
    }

    const T &operator[](size_t idx) const {
        if (idx < size_)
            return data_[idx];
        throw std::out_of_range("index is out of range");
    }

    void reserve(size_t new_size) {
        if (new_size > max_size_) {
            T *tmp = alloc_.allocate(new_size);
            for (size_t i = 0; i < size_; ++i) {
                alloc_.construct(tmp + i, std::forward<T>(*(data_ + i)));
                alloc_.destruct(data_ + i);
            }
            alloc_.deallocate(data_, max_size_);
            max_size_ = new_size;
            data_ = tmp;
        }
    }

    void resize(size_t new_size) {
        if (new_size < size_)
            for (size_t i = new_size; i < size_; ++i)
                alloc_.destruct(data_ + i);
        else {
            if (new_size > max_size_)
                reserve(new_size);

            for (size_t i = size_; i < new_size; ++i) {
                alloc_.construct(data_ + i);
            }
        }
        size_ = new_size;
    }

    void push_back(const T &elem) {
        if (size_ >= max_size_)
            reserve(max_size_ << 1);
        alloc_.construct(data_ + size_, std::move(elem));
        ++size_;
    }

    void push_back(T &&elem) {
        if (size_ >= max_size_)
            reserve(max_size_ << 1);
        alloc_.construct(data_ + size_, std::move(elem));
        ++size_;
    }

    void pop_back() {
        if (size_)
            alloc_.destruct(data_ + --size_);
    }
};

#endif //VECTOR_H
