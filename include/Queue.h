#pragma once
#include <stdexcept>

template <typename T>
struct QueueNode
{
    T data;
    QueueNode* next;

    QueueNode(const T& value) : data(value), next(nullptr) {}

};

template <typename T>
class Queue
{
private:
    QueueNode<T>* head;
    QueueNode<T>* tail;
    int queueSize;

public:
    Queue();
    ~Queue();

    bool isEmpty() const;
    void enqueue(const T& value); 
    T dequeue();                  
    T& front();
    const T& front() const;
    int size() const;
    void clear();
};