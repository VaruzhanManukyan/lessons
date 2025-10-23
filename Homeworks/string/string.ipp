#ifndef LEARNING_CPP_STRING_IPP
#define LEARNING_CPP_STRING_IPP

#include <cstring>

#include "string.hpp"

inline String::small_string& String::as_small_string() {
    return *reinterpret_cast<small_string*>(this->buffer);
}

inline const String::small_string& String::as_small_string() const {
    return *reinterpret_cast<const small_string*>(this->buffer);
}

inline String::big_string& String::as_big_string() {
    return *reinterpret_cast<big_string*>(this->buffer);
}

inline const String::big_string& String::as_big_string() const {
    return *reinterpret_cast<const big_string*>(this->buffer);
}

inline void String::make_unique_copy() {
    if (is_small()) {
        return;
    }

    big_string& buffer = as_big_string();
    if (!buffer.reference) {
        return;
    }

    std::size_t references = buffer.reference->references.load(std::memory_order_acquire);
    if (references <= 1) {
        return;
    }

    char* raw = new char[sizeof(representation_reference) + buffer.size];
    representation_reference* reference = reinterpret_cast<representation_reference*>(raw);
    new (reference) representation_reference();
    reference->references.store(references + 1, std::memory_order_relaxed);

    char* new_payload = raw + sizeof(representation_reference);
    char* old_payload = reinterpret_cast<char*>(buffer.reference) + sizeof(representation_reference);
    std::memcpy(new_payload, old_payload, buffer.size + 1);

    std::size_t previous = buffer.reference->references.fetch_sub(1, std::memory_order_acq_rel);
    if (previous <= 1) {
        std::atomic_thread_fence(std::memory_order_acquire);
        buffer.reference->~representation_reference();
        delete[] reinterpret_cast<char*>(buffer.reference);
    }

    buffer.reference = reference;
    buffer.capacity = buffer.size;
}

inline String::String() noexcept {
    small_string& buffer = as_small_string();
    buffer.info = 1;
    buffer.data[0] = '\0';
}

inline String::String(const char* data) {
    if (!data) {
        small_string& buffer = as_small_string();
        buffer.info = 1;
        buffer.data[0] = '\0';
        return;
    }

    std::size_t length = strlen(data);
    if (length > sizeof(as_small_string().data)) {
        char* raw = new char[sizeof(representation_reference) + length];
        representation_reference* reference = reinterpret_cast<representation_reference*>(raw);
        new (reference) representation_reference();
        reference->references.store(1, std::memory_order_relaxed);

        char* payload = raw + sizeof(representation_reference);
        std::memcpy(payload, data, length);
        payload[length] = '\0';

        big_string& buffer = as_big_string();
        buffer.reference = reference;
        buffer.capacity = length;
        buffer.size = length;
    } else {
        small_string& buffer = as_small_string();
        buffer.info = 1;
        std::memcpy(buffer.data, data, length);
        buffer.data[length] = '\0';
    }
}

inline String::String(const String& other) {
    if (other.is_small()) {
        const small_string& other_buffer = other.as_small_string();
        small_string& buffer = as_small_string();
        buffer.info = 1;
        std::memcpy(buffer.data, other_buffer.data, std::strlen(other_buffer.data) + 1);
    } else {
        const big_string& other_buffer = other.as_big_string();
        big_string& buffer = as_big_string();
        buffer.reference = other_buffer.reference;
        buffer.capacity = other_buffer.capacity;
        buffer.size = other_buffer.size;
        if (buffer.reference) {
            buffer.reference->references.fetch_add(1, std::memory_order_relaxed);
        }
    }
}

inline String& String::operator=(const String& other) {
    if (this == &other) {
        return *this;
    }

    String temp(other);
    char temp_buffer[24];
    std::memcpy(temp_buffer, this->buffer, sizeof(buffer));
    std::memcpy(this->buffer, temp.buffer, sizeof(buffer));
    std::memcpy(temp.buffer, temp_buffer, sizeof(buffer));
    return *this;
}

inline String::String(String&& other) noexcept {
    std::memcpy(this->buffer, other.buffer, sizeof(this->buffer));
    small_string& buffer = other.as_small_string();
    buffer.info = 1;
    buffer.data[0] = '\0';
}

inline String& String::operator=(String&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    this->~String();
    std::memcpy(this->buffer, other.buffer, sizeof(this->buffer));
    small_string& buffer = other.as_small_string();
    buffer.info = 1;
    buffer.data[0] = '\0';
    return *this;
}

inline String::~String() {
    if (!is_small()) {
        big_string buffer = as_big_string();
        if (buffer.reference) {
            std::size_t previous = buffer.reference->references.fetch_sub(1, std::memory_order_acq_rel);
            if (previous <= 1) {
                std::atomic_thread_fence(std::memory_order_acq_rel);
                buffer.reference->~representation_reference();
                delete[] reinterpret_cast<char*>(buffer.reference);
            }
        }
    }
}

inline bool String::is_small() const noexcept {
    return (static_cast<unsigned char>(this->buffer[0]) & 1) == 1;
}

inline std::size_t String::size() const noexcept {
    if (is_small()) {
        return std::strlen(as_small_string().data);
    }
    return as_big_string().size;
}

inline std::size_t String::capacity() const noexcept {
    if (is_small()) {
        return sizeof(as_small_string().data);
    }
    return as_big_string().capacity;
}

inline bool String::empty() const noexcept {
    return size() == 0;
}

#endif //LEARNING_CPP_STRING_IPP