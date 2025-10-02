#ifndef LEARNING_CPP_LIST_HPP
#define LEARNING_CPP_LIST_HPP

template <typename T>
class List {
private:
    struct Node {
        T value;
        Node* next;
        Node* previous;

        Node(const T& value);
        Node(T&& value);
    };

    Node* head;
    Node* tail;
    std::size_t listSize;
public:
    class Iterator;
    class ConstIterator;

    List();
    ~List();
    List(const List<T>& other);
    List& operator=(const List<T>& other);

    T& front();
    T& back();

    Iterator begin();
    Iterator end();
    ConstIterator begin() const;
    ConstIterator end() const;

    bool empty() const noexcept;
    std::size_t size() const noexcept;

    void push_front(const T& value);
    void push_front(T&& value);
    void push_back(const T& value);
    void push_back(T&& value);

    void pop_front();
    void pop_back();

    Iterator insert(Iterator position, const T& value);
    Iterator insert(Iterator position, T&& value);
    Iterator erase(Iterator position);

    void clear();
};


template <typename T>
class List<T>::Iterator {
private:
    Node* node;
public:
    Iterator(Node* node = nullptr);

    T& operator*() const;
    T* operator->() const;

    Iterator& operator++();
    Iterator operator++(int);
    Iterator& operator--();
    Iterator operator--(int);

    bool operator==(const Iterator& other) const;
    bool operator!=(const Iterator& other) const;

    Node* getNode() const;
};

template <typename T>
class List<T>::ConstIterator {
private:
    const Node* node;
public:
    ConstIterator(const Node* node = nullptr);
    ConstIterator(const Iterator& iterator);

    const T& operator*() const;
    const T* operator->() const;

    ConstIterator& operator++();
    ConstIterator operator++(int);
    ConstIterator& operator--();
    ConstIterator operator--(int);

    bool operator==(const ConstIterator& other) const;
    bool operator!=(const ConstIterator& other) const;

    const Node* getNode() const;
};

#include "list.ipp"

#endif //LEARNING_CPP_LIST_HPP