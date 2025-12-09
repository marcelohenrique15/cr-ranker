#pragma once

#include <vector>
#include "Student.h"

struct BSTNode {
    Student key;
    BSTNode* left;
    BSTNode* right;

    BSTNode(const Student& k) : key(k), left(nullptr), right(nullptr) {}
};

class BST {
    private:
        BSTNode* root;

        // Helpers
        BSTNode* insertHelper(BSTNode* node, const Student& student);
        BSTNode* removeHelper(BSTNode* node, const Student& student);
        BSTNode* searchHelper(BSTNode* node, const int& key);

        // Utils
        BSTNode* getMinValueNode(BSTNode* node);
        void merge(std::vector<Student>& arr, int left, int mid, int right);
        void mergeSort(std::vector<Student>& arr, int left, int right);
        
    public:
        BST();

        void insert(const Student& student);
        void remove(const Student& student);
        Student* search(const int& key);
        void sort(std::vector<Student>& arr);
};
