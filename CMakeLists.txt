cmake_minimum_required(VERSION 3.10)

# Nome do projeto
project(cr-ranker LANGUAGES CXX)

# Define a versão do C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Diretórios de cabeçalhos
include_directories(include)


# Fontes do projeto
set(SOURCES
    src/main.cpp
    src/bst/BST.cpp
    src/queue/Queue.cpp
)

# Cria o executável
add_executable(${PROJECT_NAME} ${SOURCES})