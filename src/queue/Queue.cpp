#include "Queue.h"
#include <string>

#include "Aluno.h"

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
bool Queue<T>::isEmpty() const
{
    return head == nullptr;
}

//MÉTODO: enqueue()
template<typename T>
void Queue<T>::enqueue(const T& value)
{
    QueueNode<T>* newNode = new QueueNode<T>(value);
    
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

//MÉTODO: dequeue()
template<typename T>
T Queue<T>::dequeue()
{
    if (isEmpty()) {
        throw std::runtime_error("Erro: Tentativa de remover de uma fila vazia.");
    }

    QueueNode<T>* temp = head;
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
T& Queue<T>::front()
{
    if (isEmpty()) {
        throw std::runtime_error("Erro: Tentativa de acessar o início de uma fila vazia.");
    }
    return head->data;
}

template<typename T>
const T& Queue<T>::front() const
{
    if (isEmpty()) {
        throw std::runtime_error("Erro: Tentativa de acessar o início de uma fila vazia.");
    }
    return head->data;
}


//MÉTODO: size()
template<typename T>
int Queue<T>::size() const
{
    return queueSize;
}

//MÉTODO: clear()
template<typename T>
void Queue<T>::clear()
{
    while(!isEmpty())
    {
        dequeue();
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
template class Queue<Aluno>;