
#ifndef Queue_h
#define Queue_h

#include "Queue.h"

class Queue {
private:
    Stock data[MAX_SIZE];
    int front, rear;
public:
    Queue() {
        front = rear = -1;
    }
    bool isFull() {
        return rear == MAX_SIZE - 1;
    }
    bool isEmpty() {
        return front == -1 || front > rear;
    }
    void enqueue(Stock s) {
        if (!isFull()) {
            rear++;
            data[rear] = s;
            if (front == -1) front = 0;
        }
    }
    void dequeue() {
        if (!isEmpty()) {
            
            front = (front + 1)% MAX_SIZE;
            
        }
    }
    Stock peekQueue() {
        return data[front];
        
    }
};


#endif /* Queue_h */
