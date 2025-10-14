#pragma once

#include <vector>
#include "Aluno.h"

struct BSTNode {
        double pontuacao;
        Aluno aluno;
        BSTNode* left;
        BSTNode* right;

        BSTNode(const double& p, const Aluno& a) : pontuacao(p), aluno(a), left(nullptr), right(nullptr) {}
};

class BST {
private:
    BSTNode* root;

    BSTNode* insert(BSTNode* node, double pontuacao, const Aluno& aluno);
    void inOrderDesc(BSTNode* node, std::vector<Aluno>& result);

public:
    BST();
    ~BST(); 

    void insert(double pontuacao, const Aluno& aluno);
    std::vector<Aluno> getAlunosEmOrdemDesc();
};
