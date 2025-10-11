# Versão mínima do CMake
cmake_minimum_required(VERSION 3.10)

# Nome do projeto
project(CR_RANKER)

# Define o padrão C++ (17 ou superior é recomendado)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Adiciona o executável principal e lista todos os arquivos .cpp
add_executable(CR_RANKER 
    main.cpp 
    src/bst/BST.cpp 
    src/queue/Queue.cpp
)

# Informa ao compilador onde encontrar os arquivos de cabeçalho (.h)
target_include_directories(CR_RANKER PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)