/* 
 * File:   stack.hpp
 * Author: nikos
 *
 * Created on December 9, 2016, 2:34 AM
 */

#ifndef STACK_HPP
#define	STACK_HPP

#include <iostream>
#include <string>

class Stack {
private:
    int top;
    int capacity;
    uint32_t *storage;
public:
    Stack(int);
    int push(uint32_t);    
    uint32_t peek();
    void pop();
    bool isEmpty();
    int getTop();
    ~Stack();
};

#endif	/* STACK_HPP */

