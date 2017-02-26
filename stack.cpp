#include "stack.hpp"

Stack::Stack(int capacity) {
    this->storage = (uint32_t*) malloc(sizeof(uint32_t) * capacity);
    this->capacity = capacity;
    top = -1;
}
    
int Stack::push(uint32_t value) {
    if (top == capacity)
        return -1;
    else {
        top++;
        storage[top] = value;
        return 0;
    }
}

uint32_t Stack::peek() {
    return storage[top];
}

void Stack::pop() {
    top--;
}

bool Stack::isEmpty() {
    return (top == -1);
}

int Stack::getTop() {
    return this->top;
}

Stack::~Stack() {
    delete[] storage;
}
