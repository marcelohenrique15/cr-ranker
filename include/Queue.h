#pragma once

template<typename T>
struct Node
{
    T data;
    Node* next;

    Node(const T& value) : data(value), next(nullptr){}
};

template<typename T>
class Queue
{
    private:
        Node<T>* head;
        Node<T>* tail;
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