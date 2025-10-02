#ifndef LEARNING_CPP_VECTOR_IPP
#define LEARNING_CPP_VECTOR_IPP

#include "vector.hpp"

template<typename T>
T *Vector<T>::allocate(std::size_t size) {
    if (size == 0) {
        return nullptr;
    }
    void *memory = ::operator new(size * sizeof(T));
    return static_cast<T *>(memory);
}

template<typename T>
void Vector<T>::deallocate(T *pointer) noexcept {
    if (pointer) {
        ::operator delete(static_cast<void *>(pointer));
    }
}

template<typename T>
void Vector<T>::destroyRange(T *begin, T *end) noexcept {
    while (begin != end) {
        (--end)->~T();
    }
}

template<typename T>
std::size_t Vector<T>::grow(std::size_t size, std::size_t capacity) noexcept {
    if (capacity == 0) {
        return 1;
    }

    std::size_t newCapacity = capacity + (capacity >> 1);
    if (newCapacity < size + 1) {
        newCapacity = size + 1;
    }

    return newCapacity;
}

template<typename T>
void Vector<T>::reallocateAndMove(std::size_t newCapacity) {
    T *newStart = allocate(newCapacity);
    T *current = newStart;
    T *oldStart = start;
    T *oldFinish = finish;

    try {
        for (T *it = oldStart; it != oldFinish; ++it, ++current) {
            ::new(static_cast<void *>(current)) T(std::move(*it));
        }
    } catch (...) {
        destroyRange(newStart, current);
        deallocate(newStart);
        throw;
    }

    if (oldStart) {
        destroyRange(oldStart, oldFinish);
    }
    deallocate(oldStart);

    std::size_t oldSize = static_cast<std::size_t>(oldFinish - oldStart);
    start = newStart;
    finish = newStart + oldSize;
    endCapacity = newStart + newCapacity;
}

template<typename T>
Vector<T>::Vector(std::size_t size) {
    if (size == 0) {
        return;
    }

    start = allocate(size);
    T *current = start;

    try {
        for (std::size_t i = 0; i < size; ++i, ++current) {
            ::new(static_cast<void *>(current)) T();
        }
    } catch (...) {
        destroyRange(start, current);
        deallocate(start);
        start = finish = endCapacity = nullptr;
        throw;
    }

    finish = start + size;
    endCapacity = start + size;
}

template<typename T>
Vector<T>::Vector(const Vector &other) {
    std::size_t size = other.size();
    if (size == 0) {
        return;
    }

    start = allocate(size);
    T *current = start;
    try {
        for (T *it = other.start; it != other.finish; ++it, ++current) {
            ::new(static_cast<void *>(current)) T(*it);
        }
    } catch (...) {
        destroyRange(start, current);
        deallocate(start);
        start = finish = endCapacity = nullptr;
        throw;
    }

    finish = start + size;
    endCapacity = start + size;
}

template<typename T>
Vector<T>::Vector(Vector &&other) noexcept : start(other.start), finish(other.finish), endCapacity(other.endCapacity) {
    other.start = other.finish = other.endCapacity = nullptr;
}

template<typename T>
Vector<T>::Vector(std::initializer_list<T> initializers) {
    std::size_t size = initializers.size();
    if (size == 0) {
        return;
    }

    start = allocate(size);
    T *current = start;
    try {
        for (const T &value: initializers) {
            ::new(static_cast<void *>(current)) T(value);
            ++current;
        }
    } catch (...) {
        destroyRange(start, current);
        deallocate(start);
        start = finish = endCapacity = nullptr;
        throw;
    }

    finish = start + size;
    endCapacity = start + size;
}

template<typename T>
Vector<T>::~Vector() noexcept {
    clear();
    deallocate(start);
    start = finish = endCapacity = nullptr;
}

template<typename T>
Vector<T> &Vector<T>::operator=(const Vector &other) {
    if (this == &other) {
        return *this;
    }

    Vector temp(other);
    swap(temp);
    return *this;
}

template<typename T>
Vector<T> &Vector<T>::operator=(Vector &&other) noexcept {
    if (this == &other) {
        return *this;
    }
    clear();
    deallocate(start);

    start = other.start;
    finish = other.finish;
    endCapacity = other.endCapacity;

    other.start = other.finish = other.endCapacity = nullptr;
    return *this;
}

template<typename T>
void Vector<T>::swap(Vector &other) noexcept {
    std::swap(start, other.start);
    std::swap(finish, other.finish);
    std::swap(endCapacity, other.endCapacity);
}

template<typename T>
void Vector<T>::clear() noexcept {
    destroyRange(start, finish);
    finish = start;
}

template<typename T>
std::size_t Vector<T>::size() const noexcept {
    if (!start) {
        return 0;
    }

    return static_cast<std::size_t>(finish - start);
}

template<typename T>
std::size_t Vector<T>::capacity() const noexcept {
    if (!start) {
        return 0;
    }

    return static_cast<std::size_t>(endCapacity - start);
}

template<typename T>
bool Vector<T>::empty() const noexcept {
    return start == finish;
}

template<typename T>
void Vector<T>::reserve(std::size_t newCapacity) {
    if (newCapacity > capacity()) {
        reallocateAndMove(newCapacity);
    }
}

template<typename T>
T &Vector<T>::operator[](std::size_t index) noexcept {
    return start[index];
}

template<typename T>
T &Vector<T>::at(std::size_t index) {
    if (index >= size()) {
        throw std::out_of_range("Vector::at");
    }

    return start[index];
}

template<typename T>
const T &Vector<T>::at(std::size_t index) const {
    if (index >= size()) {
        throw std::out_of_range("Vector::at");
    }

    return start[index];
}

template<typename T>
const T &Vector<T>::operator[](std::size_t index) const {
    if (index >= size()) {
        throw std::out_of_range("Vector::at");
    }
    return start[index];
}

template<typename T>
T *Vector<T>::data() noexcept {
    return start;
}

template<typename T>
const T *Vector<T>::data() const noexcept {
    return start;
}

template<typename T>
template<typename... Args>
void Vector<T>::emplace_back(Args &&... args) {
    if (finish == endCapacity) {
        reserve(grow(size(), capacity()));
    }
    ::new(static_cast<void *>(finish++)) T(std::forward<Args>(args)...);
}

template<typename T>
void Vector<T>::push_back(const T &value) {
    emplace_back(value);
}

template<typename T>
void Vector<T>::push_back(T &&value) {
    emplace_back(std::move(value));
}

template<typename T>
void Vector<T>::pop_back() noexcept {
    if (finish != start) {
        (--finish)->~T();
    }
}

template<typename T>
T *Vector<T>::begin() noexcept {
    return start;
}

template<typename T>
void Vector<T>::resize(std::size_t newSize, const T &value) noexcept {
    std::size_t oldSize = size();
    if (newSize < oldSize) {
        destroyRange(start + newSize, finish);
        finish = start + newSize;
    } else if (newSize > oldSize) {
        reserve(newSize);
        while (oldSize < newSize) {
            ::new(static_cast<void *>(finish)) T(value);
            ++finish;
            ++oldSize;
        }
    }
}

template<typename T>
void Vector<T>::shrink_to_fit() noexcept {
    std::size_t realSize = size();

    if (realSize == 0) {
        clear();
        deallocate(start);
        start = finish = endCapacity = nullptr;
        return;
    }

    if (capacity() == realSize) {
        return;
    }

    reallocateAndMove(realSize);
}

template<typename T>
T *Vector<T>::end() noexcept {
    return finish;
}

template<typename T>
const T *Vector<T>::begin() const noexcept {
    return start;
}

template<typename T>
const T *Vector<T>::end() const noexcept {
    return finish;
}

#endif // LEARNING_CPP_VECTOR_IPP