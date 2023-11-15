#ifndef NODE_H 
#define NODE_H

class Node {
private:
    //Creates a private pointer to a char
    char* data;
    //Private pointer to the next node
    Node* next;
public: 

    
    //Constructor for the node class
    Node(char value) 
    {
        data = new char;
        *data = value;
        next = nullptr;
    }

    //Returns the data stored in the node
    char getData() const {
        return *data;
    }

    //Returns the data stored in the next node
    char getNextData() const {
        return next->getData();
    }

    //Returns the address of the next node
    Node* getNextAddress() const {
        return next;
    }
    
    //Sets the next node
    void setNext(Node* node) {
        next = node;
    }

    //Destructor for the node class
    ~Node() 
    {
        delete data;
    }

};


#endif