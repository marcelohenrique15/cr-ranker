#pragma once

#include <string>

struct Aluno 
{
    int matricula;
    std::string nome;
    double coeficienteRendimento;
    int periodo;
    std::string curso;
    bool processado = false; // Flag para controlar se o aluno já foi alocado/considerado
};
