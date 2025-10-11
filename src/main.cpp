#include <iostream>
#include <vector>
#include <iomanip>

#include "Aluno.h"
#include "Turma.h"
#include "BST.h"
#include "Queue.h"

// Função auxiliar para calcular a pontuação de um aluno para uma turma específica
double calcularPontuacao(const Aluno& aluno, const Turma& turma) {
    double pontuacao = aluno.coeficienteRendimento * turma.pesos.pesoCR;
    pontuacao += aluno.periodo * turma.pesos.pesoPeriodo;
    
    if (aluno.curso == turma.cursoPrioritario) {
        pontuacao += turma.pesos.pesoCursoBonus;
    }
    
    return pontuacao;
}

// Função principal de processamento
void processarMatriculas(
    std::vector<Aluno>& todosAlunos, 
    Turma& turma,
    std::vector<Aluno>& convocadosPrioridade,
    std::vector<Aluno>& convocadosRanking,
    Queue& listaDeEspera) 
{
    // Etapa 1: Alocação de Vagas Reservadas
    for (Aluno& aluno : todosAlunos) {
        if (turma.vagasOcupadas >= turma.totalVagas) break;

        if (aluno.curso == turma.cursoPrioritario && aluno.periodo == turma.periodoPrioritario) {
            convocadosPrioridade.push_back(aluno);
            turma.vagasOcupadas++;
            aluno.processado = true;
        }
    }

    // Etapa 2: Ranqueamento dos Candidatos Restantes na BST
    BST rankingBst;
    for (const Aluno& aluno : todosAlunos) {
        if (!aluno.processado) {
            double pontuacao = calcularPontuacao(aluno, turma);
            rankingBst.insert(pontuacao, aluno);
        }
    }

    // Obter lista ordenada de candidatos
    std::vector<Aluno> candidatosOrdenados = rankingBst.getAlunosEmOrdemDesc();

    // Etapa 3 e 4: Preenchimento das vagas por ranking e criação da lista de espera
    for (const Aluno& candidato : candidatosOrdenados) {
        if (turma.vagasOcupadas < turma.totalVagas) {
            // Etapa 3
            convocadosRanking.push_back(candidato);
            turma.vagasOcupadas++;
        } else {
            // Etapa 4
            listaDeEspera.enqueue(candidato);
        }
    }
}


int main() {
    // --- DADOS DE TESTE ---

    Turma turmaSI101 = {
        /*codigoDisciplina*/ "SI101 - Algoritmos Avançados",
        /*totalVagas*/       5,
        /*vagasOcupadas*/    0, // Valor inicial padrão
        /*pesos*/            { 
                            /*pesoCR*/ 10.0, 
                            /*pesoPeriodo*/ 5.0, 
                            /*pesoCursoBonus*/ 20.0 
                            },
        /*cursoPrioritario*/ "Sistemas de Informacao",
        /*periodoPrioritario*/ 3
    };

    std::vector<Aluno> alunos = {
        {101, "Ana Silva", 8.5, 3, "Sistemas de Informacao"},      // Prioritário
        {102, "Bruno Costa", 9.2, 3, "Sistemas de Informacao"},      // Prioritário
        {103, "Carlos Dias", 7.8, 2, "Engenharia de Software"},
        {104, "Daniela Rocha", 9.5, 4, "Sistemas de Informacao"},    // Alta pontuação
        {105, "Eduardo Lima", 8.9, 3, "Ciencia da Computacao"},
        {106, "Fernanda Alves", 9.1, 5, "Sistemas de Informacao"},   // Alta pontuação
        {107, "Gabriel Santos", 7.0, 3, "Sistemas de Informacao"},      // Prioritário (mas CR baixo)
        {108, "Heloisa Matos", 9.8, 6, "Engenharia de Software"},   // Maior CR
        {109, "Igor Pereira", 8.2, 1, "Sistemas de Informacao"},
        {110, "Julia Andrade", 8.8, 4, "Ciencia da Computacao"}
    };

    // --- EXECUÇÃO ---
    std::vector<Aluno> convocadosPrioridade;
    std::vector<Aluno> convocadosRanking;
    Queue listaDeEspera;

    std::cout << "Processando matrículas para a turma: " << turmaSI101.codigoDisciplina << std::endl;
    std::cout << "Total de Vagas: " << turmaSI101.totalVagas << std::endl << std::endl;

    processarMatriculas(alunos, turmaSI101, convocadosPrioridade, convocadosRanking, listaDeEspera);

    // --- APRESENTAÇÃO DOS RESULTADOS ---
    std::cout << "--- ALUNOS CONVOCADOS (VAGA PRIORITARIA) ---" << std::endl;
    if (convocadosPrioridade.empty()) {
        std::cout << "Nenhum aluno convocado por prioridade." << std::endl;
    } else {
        for(const auto& aluno : convocadosPrioridade) {
            std::cout << "Matricula: " << aluno.matricula << ", Nome: " << aluno.nome << std::endl;
        }
    }
    std::cout << std::endl;

    std::cout << "--- ALUNOS CONVOCADOS (RANKING GERAL) ---" << std::endl;
    if (convocadosRanking.empty()) {
        std::cout << "Nenhum aluno convocado por ranking." << std::endl;
    } else {
        for(const auto& aluno : convocadosRanking) {
            double pontuacao = calcularPontuacao(aluno, turmaSI101);
            std::cout << "Matricula: " << aluno.matricula << ", Nome: " << aluno.nome 
                      << ", Pontuacao: " << std::fixed << std::setprecision(2) << pontuacao << std::endl;
        }
    }
    std::cout << std::endl;

    std::cout << "--- LISTA DE ESPERA (POR ORDEM DE CLASSIFICACAO) ---" << std::endl;
    if (listaDeEspera.isEmpty()) {
        std::cout << "Nao ha alunos na lista de espera." << std::endl;
    } else {
        int pos = 1;
        while(!listaDeEspera.isEmpty()) {
            Aluno aluno = listaDeEspera.dequeue();
            double pontuacao = calcularPontuacao(aluno, turmaSI101);
            std::cout << pos++ << ".: Matricula: " << aluno.matricula << ", Nome: " << aluno.nome
                      << ", Pontuacao: " << std::fixed << std::setprecision(2) << pontuacao << std::endl;
        }
    }
    std::cout << std::endl;
    std::cout << "Total de Vagas Ocupadas: " << turmaSI101.vagasOcupadas << "/" << turmaSI101.totalVagas << std::endl;

    return 0;
}