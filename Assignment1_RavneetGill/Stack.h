
#ifndef Stack_h
#define Stack_h

#include "Stock.h"

class Stack {
private:
    Stock data[MAX_SIZE];
    int top;
public:
    Stack() {
        top = -1;
    }
    bool isFull() {
        return top == MAX_SIZE - 1;
    }
    bool isEmpty() {
        return top == -1;
    }
    void push(Stock s) {
        if (!isFull()) {
            top++;
            data[top] = s;
        }
    }
    void pop() {
        if (!isEmpty()) {
            top--;
        }
    }
    Stock peekStack() {
        return data[top];
    }
};

#endif /* Stack_h */
