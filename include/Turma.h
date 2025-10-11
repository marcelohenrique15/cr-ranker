#pragma once

#include <string>
#include "Aluno.h"

// Struct para agrupar os pesos que serão usados no cálculo
struct PesosCriterios {
    double pesoCR;
    double pesoPeriodo;
    double pesoCursoBonus;
};

struct Turma {
    std::string codigoDisciplina;
    int totalVagas;
    int vagasOcupadas = 0;
    
    // Critérios para o Ranking
    PesosCriterios pesos;

    // Critérios para Vaga Reservada
    std::string cursoPrioritario;
    int periodoPrioritario;
};