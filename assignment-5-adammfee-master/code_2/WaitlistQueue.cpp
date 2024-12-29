#include "WaitlistQueue.hpp"

using namespace std;

WaitlistQueue::WaitlistQueue(int qSize)
{
    /* Already implemented, don't change */
    qFront = qEnd = -1;
    qCapacity = qSize;
    queue = new string[qSize];
}

WaitlistQueue::~WaitlistQueue()
{
    //TODO
    delete[] queue;
}

void WaitlistQueue::enqueue(string value)
{
    //TODO
    if (isFull()) {
        cout << "Waitlist is full. Cannot enqueue." << endl;
        return;
    }

    if (isEmpty()) {
        qFront = 0;
    }
    
    qEnd = (qEnd + 1) % qCapacity;
    queue[qEnd] = value;
}

void WaitlistQueue::dequeue()
{
    //TODO
    if (isEmpty()) {
        cout << "Waitlist is empty. Cannot dequeue." << endl;
        return;
    }

    if (qFront == qEnd) {
        qFront = qEnd = -1;
    } else {
        qFront = (qFront + 1) % qCapacity;
    }
}

string WaitlistQueue::peek()
{
    //TODO
    if (isEmpty()) {
        return "<EMPTY QUEUE>";
    }

    return queue[qFront];
}

void WaitlistQueue::resize(int newSize)
{
    //TODO
    string* newQ = new string[newSize];

    int currentSize = size();
    for (int i = 0; i < currentSize; i++) {
        newQ[i] = queue[(qFront + i) % qCapacity];
    }

    delete[] queue;
    queue = newQ;
    qFront = 0;
    qEnd = currentSize - 1;
    qCapacity = newSize;
}

int WaitlistQueue::size()
{
    //TODO
    if (isEmpty()) {
        return 0;
    }
    if (qEnd >= qFront) {
        return qEnd - qFront + 1;
    } else {
        return qCapacity - qFront + qEnd + 1;
    }
}

int WaitlistQueue::capacity()
{
    //TODO
    return qCapacity;
}

bool WaitlistQueue::isEmpty()
{
    //TODO
    if(qFront == -1){
        return true;
    }
    return false;
}

bool WaitlistQueue::isFull()
{
    //TODO
    if ((qEnd + 1) % qCapacity == qFront) {
        return true;
    }
    return false;
}