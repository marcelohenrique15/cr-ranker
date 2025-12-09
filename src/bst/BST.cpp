#include <iostream>
#include "BST.h"
#include "Student.h"

using namespace std;

BST::BST() : root(nullptr) {}

BSTNode* BST::getMinValueNode(BSTNode* node)
{
    BSTNode* current = node;
    while(current->left != nullptr)
    {
        current = current->left;
    }

    return current;
}

BSTNode* BST::insertHelper(BSTNode* node, const Student& key)
{
    if(node == nullptr)
    {
        return new BSTNode(key);
    }

    if(key.registration < node->key.registration)
    {
        node->left = insertHelper(node->left, key);
    }

    else if(key.registration > node->key.registration)
    {
        node->right = insertHelper(node->right, key);
    }

    return node;
}

BSTNode* BST::removeHelper(BSTNode* node, const Student& key)
{
    if(node == nullptr)
    {
        return node;
    }

    if(key.registration < node->key.registration)
    {
        node->left = removeHelper(node->left, key);
    }

    else if(key.registration > node->key.registration)
    {
        node->right = removeHelper(node->right, key);
    }

    else
    {
        if(node->left == nullptr)
        {
            BSTNode* temp = node->right;
            delete node;
            return temp;
        }

        else if(node->right == nullptr)
        {
            BSTNode* temp = node->left;
            delete node;
            return temp;
        }

        BSTNode* temp = getMinValueNode(node->right);
        node->key = temp->key;
        node->right = removeHelper(node->right, temp->key);
    }

    return node;
}

BSTNode* BST::searchHelper(BSTNode* node, const int& key)
{
    if(node == nullptr || node->key.registration == key)
    {
        return node;
    }

    if(key < node->key.registration)
    {
        return searchHelper(node->left, key);
    }

    else
    {
        return searchHelper(node->right, key);
    }
}

void BST::insert(const Student& student)
{
    root = insertHelper(root, student);
}

void BST::remove(const Student& student)
{
    root = removeHelper(root, student);
}

Student* BST::search(const int& key)
{
    BSTNode* node = searchHelper(root, key);
    if (node == nullptr) return nullptr;
    return &(node->key);
}
