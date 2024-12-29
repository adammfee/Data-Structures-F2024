#ifndef WAITLISTQUEUE_H__
#define WAITLISTQUEUE_H__

#include <string>
#include <iostream>

using namespace std;

class WaitlistQueue {

    private:
        string* queue;                      // the array container
        int qCapacity;                      // the size of the array
        int qFront;                         // queueFront's index
        int qEnd;                           // qEnd's index

    public:
        WaitlistQueue(int qSize=5);         // parameterized constructor
        ~WaitlistQueue();                   // destructor

        void enqueue(string value);         // add a value to the queue 
        void dequeue();                     // remove a value from the queue
        string peek();                      // get a value from the queue

        void resize(int new_size);          // resize the queue container
        int size();                         // get the number of elements in the queue
        int capacity();                     // the total size of the queue container
        bool isEmpty();                     // return whether the queue is empty
        bool isFull();                      // return whether the queue is full

        int getQueueFront() { return qFront; }
        int getQueueEnd() { return qEnd; }
        string* getQueue() { return queue; }
};
#endif