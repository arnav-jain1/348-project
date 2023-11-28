#ifndef STACK_H
#define STACK_H
#include "node.h"

class Stack {
private:
    Node* top;
    int size;

public:
    Stack();
    void push(char value);
    char pop();
    char peek() const;
    void print() const;
    int getSize() const;
    ~Stack();
    bool empty() const;

    friend std::ostream& operator<<(std::ostream& os, const Stack& stack);

    Stack reverse();
};

#endif