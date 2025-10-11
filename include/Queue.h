#ifndef QUEUE_H
#define QUEUE_H

#include "Aluno.h"

class Queue {
private:
    struct Node {
        Aluno aluno;
        Node* next;
        Node(const Aluno& a) : aluno(a), next(nullptr) {}
    };

    Node* head;
    Node* tail;

public:
    Queue();
    // Destrutor (não implementado para simplicidade)
    // ~Queue(); 
    
    bool isEmpty();
    void enqueue(const Aluno& aluno);
    Aluno dequeue();
    Aluno front();
};

#endif 