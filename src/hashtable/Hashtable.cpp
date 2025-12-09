#include <Hashtable.h>

using namespace std;

Hashtable::Hashtable(size_t cap) : capacity(cap), size(0) 
{
    table.resize(capacity);

    for(size_t i = 0; i < capacity; i++)
    {
        table[i] = nullptr;
    }
}

Hashtable::~Hashtable()
{
    for(Node*& head : table)
    {
        while(head)
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
}

size_t Hashtable::hash(const string& key)
{
    unsigned long hash = 5381;

    for(char c : key)
    {
        hash = ((hash << 5) + hash) + c;
    }

    return hash % capacity;
}

void Hashtable::insert(Subject* key)
{
    size_t index = hash(key->code);
    string value = key->code;
    Node* head = table[index];

    while(head)
    {
        if(head->key->code == value)
        {
            head->key->code = value;
            return;
        }

        head = head->next;
    }

    Node* newNode = new Node(key);
    newNode->next = table[index];
    table[index] = newNode;
    size++;
}

void Hashtable::remove(const Subject& key)
{
    size_t index = hash(key.code);
    string value = key.code;
    Node* head = table[index];
    Node* prev = nullptr;

    while(head)
    {
        if(head->key->code == value)
        {
            if(prev) prev->next = head->next;
            else table[index] = head->next;

            delete head;
            size--;
            return;
        }

        prev = head;
        head = head->next;
    }

    return;
}

Subject* Hashtable::search(const string& key)
{
    size_t index = hash(key);
    string value = key;
    Node* head = table[index];

    while(head)
    {
        if(head->key->code == value)
        {
            Subject* subject = head->key;
            return subject;
        }

        head = head->next;
    }
    return nullptr;
}

size_t Hashtable::getSize()
{
    return size;
}