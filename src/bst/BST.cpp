#include "BST.h"

BST::BST() : root(nullptr) {}

// Método público
void BST::insert(double pontuacao, const Aluno& aluno) {
    root = insert(root, pontuacao, aluno);
}

// Método privado recursivo
BST::Node* BST::insert(Node* node, double pontuacao, const Aluno& aluno) {
    if (node == nullptr) {
        return new Node(pontuacao, aluno);
    }

    if (pontuacao < node->pontuacao) {
        node->left = insert(node->left, pontuacao, aluno);
    } else { // >= para tratar pontuações iguais
        node->right = insert(node->right, pontuacao, aluno);
    }
    return node;
}

// Método público
std::vector<Aluno> BST::getAlunosEmOrdemDesc() {
    std::vector<Aluno> result;
    inOrderDesc(root, result);
    return result;
}

// Método privado recursivo para travessia em ordem decrescente
void BST::inOrderDesc(Node* node, std::vector<Aluno>& result) {
    if (node == nullptr) {
        return;
    }
    // 1. Visita a sub-árvore direita (maiores pontuações)
    inOrderDesc(node->right, result);
    // 2. Adiciona o nó atual
    result.push_back(node->aluno);
    // 3. Visita a sub-árvore esquerda (menores pontuações)
    inOrderDesc(node->left, result);
}