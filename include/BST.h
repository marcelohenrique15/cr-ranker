#ifndef BST_H
#define BST_H

#include <vector>
#include "Aluno.h"

class BST {
private:
    struct Node {
        double pontuacao;
        Aluno aluno;
        Node* left;
        Node* right;

        Node(double p, const Aluno& a) : pontuacao(p), aluno(a), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* insert(Node* node, double pontuacao, const Aluno& aluno);
    void inOrderDesc(Node* node, std::vector<Aluno>& result);

public:
    BST();
    // Destrutor para liberar memória (não implementado para simplicidade)
    // ~BST(); 

    void insert(double pontuacao, const Aluno& aluno);
    std::vector<Aluno> getAlunosEmOrdemDesc();
};

#endif