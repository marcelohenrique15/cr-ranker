#pragma once
#include <cstdlib> 
#include <new>     

template<typename T>
struct QueueNode
{
    T data;
    QueueNode* next;

    QueueNode(const T& value) : data(value), next(nullptr) {}

    void* operator new(size_t size)
    {
        return malloc(size);
    }

    void operator delete(void* pointer)
    {
        free(pointer);
    }
};

template<typename T>
class Queue
{
private:
    QueueNode<T>* head;
    QueueNode<T>* tail;
    int queueSize;

public:
    Queue();
    ~Queue();

    bool isEmpty();
    void push(const T& value);
    T pop();
    T front();
    int size();
    void clear();
};