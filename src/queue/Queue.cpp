#include "Queue.h"
#include <stdexcept>

Queue::Queue() : head(nullptr), tail(nullptr) {}

bool Queue::isEmpty() {
    return head == nullptr;
}

void Queue::enqueue(const Aluno& aluno) {
    Node* newNode = new Node(aluno);
    if (isEmpty()) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

Aluno Queue::dequeue() {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty");
    }
    Node* temp = head;
    Aluno aluno = head->aluno;
    head = head->next;
    if (head == nullptr) {
        tail = nullptr;
    }
    delete temp;
    return aluno;
}

Aluno Queue::front() {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty");
    }
    return head->aluno;
}