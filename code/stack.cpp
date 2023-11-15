#include <iostream>
#include "stack.h"



Stack::Stack() {
    //Stack class constructor, makes an empty stack with the top pointer pointing to nullptr
    this->top = nullptr;
    this->size = 0;
}

void Stack::push(char value) {
    //Creates a new node with the value passed in
    Node* node = new Node(value);
    //Sets the next node to the current top
    node->setNext(this->top); 
    //Sets the top to the new node
    this->top = node;
    //Increments the size of the stack
    this->size++;
    
}

char Stack::pop() {
    //Creates a temporary node to store the current top
    Node* temp = this->top;
    //Sets the top to the next node
    this->top = this->top->getNextAddress();
    //Gets the data from the temporary node
    char c = temp->getData();
    //Deletes the temporary node
    delete temp;
    //Decrements the size of the stack
    this->size--;
    //Returns the data from the temporary node
    return c;

}
char Stack::peek() const {
    //Returns the data from the top node
    return this->top->getData();
}

int Stack::getSize() const {
    //Returns the size of the stack
    return this->size;
}

void Stack::print() const {
    //Gets the pointer to the top node
    Node* current = this->top;
    //While the current node is not nullptr
    while (current != nullptr) {
        //Prints the data from the current node
        std::cout << current->getData() << ' ';
        //Sets the current node to the next node
        current = current->getNextAddress();
    }
    //Adds a new line after the stack is printed
    std::cout << std::endl;
}

Stack::~Stack() {
    //Destructor with same logic as print but for deleting the nodes
    Node* current = this->top;
    while (current != nullptr) {
        Node* temp = current;
        current = current->getNextAddress();
        delete temp;
    }

}