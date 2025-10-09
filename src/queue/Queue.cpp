#include "Queue.h"
#include <iostream>

using namespace std;

// ############# PUBLIC #############
//CONSTRUCTOR
template<typename T>
Queue<T>::Queue() : head(nullptr), tail(nullptr), queueSize(0) {}

//DESTRUCTOR
template<typename T>
Queue<T>::~Queue()
{
    clear();
}

//MÉTODO: isEmpty()
template<typename T>
bool Queue<T>::isEmpty()
{
    if(head == nullptr)
    {
        return true;
    }

    return false;
}

//MÉTODO: push()
template<typename T>
void Queue<T>::push(const T& value)
{
    Node<T>* newNode = new Node<T>(value);
    
    if(isEmpty())
    {
        head = tail = newNode;
    }

    else
    {
        tail->next = newNode;
        tail = newNode;
    }

    queueSize++;
}

//MÉTODO: pop()
template<typename T>
T Queue<T>::pop()
{
    if(isEmpty())
    { 
        throw out_of_range("ERROR: Void Queue");
    }

    Node<T>* temp = head;
    T value = head->data;
    head = head->next;

    if(head == nullptr)
    {
        tail = nullptr;
    }

    delete temp;
    queueSize--;

    return value;
}

//MÉTODO: front()
template<typename T>
T Queue<T>::front()
{
    if(isEmpty())
    { 
        throw out_of_range("ERROR: Void Queue");
    }

    return head->data;
}

//MÉTODO: size()
template<typename T>
int Queue<T>::size()
{
    return queueSize;
}

//MÉTODO: clear()
template<typename T>
void Queue<T>::clear()
{
    while(!isEmpty())
    {
        pop();
    }
}

// ################ TEMPLATES ###############
template class Queue<char>;
template class Queue<signed char>;
template class Queue<unsigned char>;
template class Queue<short>;
template class Queue<unsigned short>;
template class Queue<int>;
template class Queue<unsigned int>;
template class Queue<long>;
template class Queue<unsigned long>;
template class Queue<long long>;
template class Queue<unsigned long long>;
template class Queue<float>;
template class Queue<double>;
template class Queue<long double>;
template class Queue<bool>;
template class Queue<std::string>;