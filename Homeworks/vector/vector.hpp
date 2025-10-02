#ifndef LEARNING_CPP_VECTOR_HPP
#define LEARNING_CPP_VECTOR_HPP

template <typename T>
class Vector {
private:
    T* start = nullptr;
    T* finish = nullptr;
    T* endCapacity = nullptr;

    static T* allocate(std::size_t size);
    static void deallocate(T* pointer) noexcept;

    void destroyRange(T* begin, T* end) noexcept;
    std::size_t grow(std::size_t size, std::size_t capacity) noexcept;
    void reallocateAndMove(std::size_t newCapacity);
public:
    Vector() noexcept = default;

    explicit Vector(std::size_t size);
    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;
    Vector(std::initializer_list<T> initializers);

    ~Vector() noexcept;

    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other) noexcept;

    std::size_t size() const noexcept;
    std::size_t capacity() const noexcept;

    void swap(Vector& other) noexcept;
    void clear() noexcept;
    bool empty() const noexcept;
    void reserve(std::size_t newCapacity);

    T& operator[](std::size_t index) noexcept;
    const T& operator[](std::size_t index) const;

    T& at(std::size_t index);
    const T& at(std::size_t index) const;

    T* data() noexcept;
    const T* data() const noexcept;

    template <typename... Args>
    void emplace_back(Args&&... args);

    void push_back(const T& value);
    void push_back(T&& value);

    void pop_back() noexcept;

    void resize(std::size_t newSize, const T& value) noexcept;
    void shrink_to_fit() noexcept;

    T* begin() noexcept;
    T* end() noexcept;

    const T* begin() const noexcept ;
    const T* end() const noexcept;
};

#include "vector.ipp"

#endif //LEARNING_CPP_VECTOR_HPP
