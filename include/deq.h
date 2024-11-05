#ifndef DEQUE_H
#define DEQUE_H

#include <cstdint>
#include <stdexcept>

template<typename T>
struct DequeNode {
    T data;
    DequeNode* next;
    DequeNode* prev;

    DequeNode(const T& value) : data(value), next(nullptr), prev(nullptr) {}
};

template<typename T>
struct Deque {
    DequeNode<T>* head;
    DequeNode<T>* tail;
    size_t count;

    Deque() : head(nullptr), tail(nullptr), count(0) {}

    
    Deque(size_t size, const T& value = T()) : head(nullptr), tail(nullptr), count(0) {
        for (size_t i = 0; i < size; ++i) {
            push_back(value); 
        }
    }

    ~Deque() {
        while (!empty()) {
            pop_front();
        }
    }

    void push_back(const T& value) {
        DequeNode<T>* newNode = new DequeNode<T>(value);
        if (empty()) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        count++;
    }

    void push_front(const T& value) {
        DequeNode<T>* newNode = new DequeNode<T>(value);
        if (empty()) {
            head = tail = newNode;
        } else {
            head->prev = newNode;
            newNode->next = head;
            head = newNode;
        }
        count++;
    }

    void pop_back() {
        if (empty()) throw std::out_of_range("Deque is empty");
        
        DequeNode<T>* temp = tail;
        if (head == tail) {
            delete head;
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            delete temp;
            tail->next = nullptr;
        }
        count--;
    }

    void pop_front() {
        if (empty()) throw std::out_of_range("Deque is empty");
        
        DequeNode<T>* temp = head;
        if (head == tail) {
            delete head;
            head = tail = nullptr;
        } else {
            head = head->next;
            delete temp;
            if (head) {
                head->prev = nullptr;
            }
        }
        count--;
    }

    T& front() {
        if (empty()) throw std::out_of_range("Deque is empty");
        return head->data;
    }

    T& back() {
        if (empty()) throw std::out_of_range("Deque is empty");
        return tail->data;
    }

    size_t size() const {
        return count;
    }

    bool empty() const {
        return count == 0;
    }

    T& operator[](size_t index) {
        if (index >= count) throw std::out_of_range("Index out of range");

        DequeNode<T>* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }

    const T& operator[](size_t index) const {
        if (index >= count) throw std::out_of_range("Index out of range");

        DequeNode<T>* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }
};

#endif 