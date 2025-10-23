#ifndef LEARNING_CPP_STRING_HPP
#define LEARNING_CPP_STRING_HPP

#include <cstddef>
#include <utility>
#include <atomic>

class String {
private:
    struct representation_reference {
        std::atomic<std::size_t> references;
    };

    struct small_string{
        uint8_t info;
        char data[23];
    };

    struct big_string {
        representation_reference* reference;
        size_t size;
        size_t capacity;
    };

    alignas(alignof(small_string) > alignof(big_string) ? alignof(small_string) : alignof(big_string)) char buffer[24];

    small_string& as_small_string();
    const small_string& as_small_string() const;
    big_string& as_big_string();
    const big_string& as_big_string() const;

    void make_unique_copy();
public:
    String() noexcept;
    explicit String(const char* data);
    String(const String& other);
    String& operator=(const String& other);
    String(String&& other) noexcept;
    String& operator=(String&& other) noexcept;
    ~String();

    bool is_small() const noexcept;
    std::size_t size() const noexcept;
    std::size_t capacity() const noexcept;
    bool empty() const noexcept;
};

#include "string.ipp"

#endif //LEARNING_CPP_STRING_HPP
