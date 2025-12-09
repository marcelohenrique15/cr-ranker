#pragma once

#include <vector>
#include <iostream>

#include "Subject.h"

struct Node
{
    Subject* key;
    Node* next;

    Node(Subject* k) : key(k), next(nullptr) {}
};

class Hashtable
{
    private:
        std::vector<Node*> table;
        size_t capacity;
        size_t size;

        size_t hash(const std::string& key);
    
    public:
        Hashtable(size_t cap = 16);
        ~Hashtable();

        void insert(Subject* key);
        void remove(const Subject& key);
        Subject* search(const std::string& key);
        size_t getSize();
};