#pragma once

template<typename T>
struct Node
{
    T data;
    Node* head;

    Node(const T& value) : data(value), next(nullptr){}
};

template<typename T>
class Queue
{
    private:
        Node<T>* head;
        Node<T>* tail;

    public:
        Queue();
        ~Queue();

        void push(const T& value); 
        T pop();   
        
        T front();
        bool isEmpty(); 
        int size(); 
        void clear();   
};