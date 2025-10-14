# 🎓🚀 CR Ranker - Algorithms

Este projeto é uma solução para a cadeira de Algoritmos do CIn/UFPE que consiste em um Ranqueador para a matrícula em cadeiras da faculdade por meio de um algoritmo de ordenação.

## 📝 Descrição

O objetivo é desenvolver um algoritmo que faça a ordenação dos alunos para a matrícula em uma determinada cadeira, fazendo uso de estruturas de dados para aprofundar o conhecimento. Os principais pontos usados para a ordenação são:
- CR
- Curso
- Período

## ⚙️ Como Rodar o Projeto

1.  **Clone o Repositório**

    ```bash
    git clone https://github.com/marcelohenrique15/cr-ranker.git
    cd cr-ranker
    ```

2.  **Instale as Dependências**

    ```bash
    # Instalar o CMAKE (Linux)
    sudo apt update && sudo apt install cmake
    ```

3.  **Ajuste o Arquivo de Entrada**

    ```bash
    # Coloque os alunos da forma que quiser, seguindo o seguinte padrão:
    # Formato: Matricula, Nome, CR, Periodo, Curso
    # Exemplo:
    101,Ana Silva,8.5,3,Sistemas de Informacao
    102,Bruno Costa,9.2,3,Sistemas de Informacao
    103,Carlos Dias,7.8,2,Engenharia de Software
    104,Daniela Rocha,9.5,4,Sistemas de Informacao
    105,Eduardo Lima,8.9,3,Ciencia da Computacao
    106,Fernanda Alves,9.1,5,Sistemas de Informacao
    107,Gabriel Santos,7.0,3,Sistemas de Informacao
    108,Heloisa Matos,9.8,6,Engenharia de Software
    109,Igor Pereira,8.2,1,Sistemas de Informacao
    110,Julia Andrade,8.8,4,Ciencia da Computacao
    ```

4.  **Execute o Programa**
    ```bash
    # No Linux
    ./run_linux.sh

    # No Windows
    mkdir src\output
    g++ -Wall -Wextra -g3 -std=c++17 -I include src/main.cpp src/bst/BST.cpp src/queue/Queue.cpp -o src/output/main.exe
    src\output\main.exe
    ```

## 👤 Autores

| <img src="https://avatars.githubusercontent.com/u/151575079?s=400&u=96fac0907f9100c143dc9f46242cacdf17af240f&v=4" alt="Lucas Torres" width="150" height="150"> | <img src="https://avatars.githubusercontent.com/u/174950521?v=4" alt="Guilherme Máximo" width="150" height="150"> | <img src="https://avatars.githubusercontent.com/u/84104129?v=4" alt="Lucas Francisco" width="150" height="150"> | <img src="https://avatars.githubusercontent.com/u/83303964?v=4" alt="Marcelo Henrique" width="150" height="150"> | <img src="https://avatars.githubusercontent.com/u/204962998?v=4" alt="Felipe Berardo" width="150" height="150"> |
| --- | --- | --- | --- | --- |
| [Lucas Torres](https://github.com/lucaastorres7)  | [Guilherme Máximo](https://github.com/guifmax) | [Lucas Francisco](https://github.com/Lucasesaraujo) | [Marcelo Henrique](https://github.com/marcelohenrique15) | [Felipe Berardo](https://github.com/FelipeBerardo) |