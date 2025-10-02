#ifndef LEARNING_CPP_LIST_IPP
#define LEARNING_CPP_LIST_IPP

#include "list.hpp"

template <typename T>
List<T>::Node::Node(const T& value): value(value), next(nullptr), previous(nullptr) {}

template <typename T>
List<T>::Node::Node(T&& value): value(std::move(value)), next(nullptr), previous(nullptr) {}

template <typename T>
List<T>::List(): listSize(0) {
    head = new Node(T{});
    tail = new Node(T{});
    head->next = tail;
    tail->previous = head;
}

template <typename T>
List<T>::List(const List& other): List() {
    for (const T& item : other) {
        push_back(item);
    }
}

template <typename T>
List<T>::~List() {
    clear();
    delete head;
    delete tail;
}

template <typename T>
List<T>& List<T>::operator=(const List& other) {
    if (this != &other) {
        clear();
        for (const T& item : other) {
            push_back(item);
        }
    }
    return *this;
}

template <typename T>
T& List<T>::front() {
    return head->next->value;
}

template <typename T>
T& List<T>::back() {
    return tail->previous->value;
}

template <typename T>
typename List<T>::Iterator List<T>::begin() {
    return Iterator(head->next);
}

template <typename T>
typename List<T>::Iterator List<T>::end() {
    return Iterator(tail);
}

template <typename T>
typename List<T>::ConstIterator List<T>::begin() const {
    return ConstIterator(head->next);
}

template <typename T>
typename List<T>::ConstIterator List<T>::end() const {
    return ConstIterator(tail);
}

template <typename T>
bool List<T>::empty() const noexcept {
    return listSize == 0;
}

template <typename T>
std::size_t List<T>::size() const noexcept {
    return listSize;
}

template <typename T>
void List<T>::push_front(const T& value) {
    insert(begin(), value);
}

template <typename T>
void List<T>::push_front(T&& value) {
    insert(begin(), std::move(value));
}

template <typename T>
void List<T>::push_back(const T& value) {
    insert(end(), value);
}

template <typename T>
void List<T>::push_back(T&& value) {
    insert(end(), std::move(value));
}

template <typename T>
void List<T>::pop_front() {
    if (!empty()) {
        erase(Iterator(head->next));
    }
}

template <typename T>
void List<T>::pop_back() {
    if (!empty()) {
        erase(Iterator(tail->previous));
    }
}

template <typename T>
typename List<T>::Iterator List<T>::insert(Iterator position, const T& value) {
    Node* positionNode = position.getNode();
    if (!positionNode) {
        return end();
    }

    Node* previousNode = positionNode->previous;
    Node* newNode = new Node(value);

    newNode->next = positionNode;
    newNode->previous = previousNode;
    previousNode->next = newNode;
    positionNode->previous = newNode;
    ++listSize;

    return Iterator(newNode);
}

template <typename T>
typename List<T>::Iterator List<T>::insert(Iterator position, T&& value) {
    Node* positionNode = position.getNode();
    if (!positionNode) {
        return end();
    }

    Node* previousNode = positionNode->previous;
    Node* newNode = new Node(std::move(value));

    newNode->next = positionNode;
    newNode->previous = previousNode;
    previousNode->next = newNode;
    positionNode->previous = newNode;
    ++listSize;

    return Iterator(newNode);
}

template <typename T>
typename List<T>::Iterator List<T>::erase(Iterator position) {
    Node* node = position.getNode();
    if (!node || node == head || node == tail) {
        return Iterator(tail);
    }

    Node* previousNode = node->previous;
    Node* nextNode = node->next;

    previousNode->next = nextNode;
    nextNode->previous = previousNode;

    delete node;
    --listSize;
    return Iterator(nextNode);
}

template <typename T>
void List<T>::clear() {
    Node* current = head->next;
    while(current != tail) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
    head->next = tail;
    tail->previous = head;
    listSize = 0;
}

// ITERATOR IMPLEMENTATION
template <typename T>
List<T>::Iterator::Iterator(Node* node): node(node) {}

template <typename T>
T& List<T>::Iterator::operator*() const {
    return node->value;
}

template <typename T>
T* List<T>::Iterator::operator->() const {
    return &node->value;
}

template <typename T>
typename List<T>::Iterator& List<T>::Iterator::operator++() {
    if (node) {
        node = node->next;
    }
    return *this;
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator++(int) {
    Iterator temp(*this);
    if (node) {
        node = node->next;
    }
    return temp;
}

template <typename T>
typename List<T>::Iterator& List<T>::Iterator::operator--() {
    if (node) {
        node = node->previous;
    }
    return *this;
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator--(int) {
    Iterator temp(*this);
    if (node) {
        node = node->previous;
    }
    return temp;
}

template <typename T>
bool List<T>::Iterator::operator==(const Iterator& other) const {
    return node == other.node;
}

template <typename T>
bool List<T>::Iterator::operator!=(const Iterator& other) const {
    return node != other.node;
}

template <typename T>
typename List<T>::Node* List<T>::Iterator::getNode() const {
    return node;
}

// === CONST ITERATOR IMPLEMENTATION ===
template <typename T>
List<T>::ConstIterator::ConstIterator(const Node* node): node(node) {}

template <typename T>
List<T>::ConstIterator::ConstIterator(const Iterator& iterator): node(iterator.getNode()) {}

template <typename T>
const T& List<T>::ConstIterator::operator*() const {
    return node->value;
}

template <typename T>
const T* List<T>::ConstIterator::operator->() const {
    return &node->value;
}

template <typename T>
typename List<T>::ConstIterator& List<T>::ConstIterator::operator++() {
    if (node) {
        node = node->next;
    }
    return *this;
}

template <typename T>
typename List<T>::ConstIterator List<T>::ConstIterator::operator++(int) {
    ConstIterator temp(*this);
    if (node) {
        node = node->next;
    }
    return temp;
}

template <typename T>
typename List<T>::ConstIterator& List<T>::ConstIterator::operator--() {
    if (node) {
        node = node->previous;
    }
    return *this;
}

template <typename T>
typename List<T>::ConstIterator List<T>::ConstIterator::operator--(int) {
    ConstIterator temp(*this);
    if (node) {
        node = node->previous;
    }
    return temp;
}

template <typename T>
bool List<T>::ConstIterator::operator==(const ConstIterator& other) const {
    return node == other.node;
}

template <typename T>
bool List<T>::ConstIterator::operator!=(const ConstIterator& other) const {
    return node != other.node;
}

template <typename T>
const typename List<T>::Node* List<T>::ConstIterator::getNode() const {
    return node;
}

#endif //LEARNING_CPP_LIST_IPP