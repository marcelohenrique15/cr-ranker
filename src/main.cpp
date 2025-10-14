#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>

#include "Aluno.h"
#include "Turma.h"
#include "BST.h"
#include "Queue.h"
#define VAGAS_SI101 5

using namespace std;

vector<Aluno> carregarAlunos(const string& nomeArquivo) {
    vector<Aluno> alunos;
    ifstream arquivo_entrada(nomeArquivo);
    string linha;

    if (!arquivo_entrada.is_open()){
        cerr << "Não foi possível abrir o arquivo " << nomeArquivo << endl;
        return alunos;
    }

    while (getline(arquivo_entrada, linha)) {
        stringstream ss(linha);
        string campo;
        Aluno novoAluno;

        if (linha.empty() || linha[0] == '#') {
            continue; // Pula para a próxima linha se vazio ou comentário
        }

        // Matricula (int)
        getline(ss, campo, ',');
        try { novoAluno.matricula = stoi(campo); } catch (...) { continue; }

        // Nome (str)
        getline(ss, novoAluno.nome, ',');

        // Coeficiente de Rendimento (double)
        getline(ss, campo, ',');
        try { novoAluno.coeficienteRendimento = stod(campo); } catch (...) { continue; }

        // Periodo (int)
        getline(ss, campo, ',');
        try { novoAluno.periodo = stoi(campo); } catch (...) { continue; }

        // Curso (str)
        getline(ss, novoAluno.curso);

        alunos.push_back(novoAluno);
    }

    arquivo_entrada.close();
    return alunos;
}

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
    vector<Aluno>& todosAlunos, 
    Turma& turma,
    vector<Aluno>& convocadosPrioridade,
    vector<Aluno>& convocadosRanking,
    Queue<Aluno>& listaDeEspera) 
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
    vector<Aluno> candidatosOrdenados = rankingBst.getAlunosEmOrdemDesc();

    // Etapa 3 e 4: Preenchimento das vagas por ranking e criação da lista de espera
    for (const Aluno& candidato : candidatosOrdenados) {
        if (turma.vagasOcupadas < turma.totalVagas) {
            // Etapa 3
            convocadosRanking.push_back(candidato);
            turma.vagasOcupadas++;
        } else {
            // Etapa 4
            listaDeEspera.push(candidato);
        }
    }
}


int main() {
    ofstream saida("../resultado_matricula.txt");

    if (!saida.is_open()){
        cerr << "Nao foi possivel criar o arquivo de saida" << endl;
        return 1;
    }

    vector<Aluno> alunos = carregarAlunos("alunos.txt");

    Turma turmaSI101 = {
        "SI101 - Algoritmos Avançados", // Codigo Disciplina
        VAGAS_SI101, // Total Vagas
        0, // Vagas Ocupadas (0 por padrão)
        { // Pesos
            10.0, // Peso CR
            5.0, // Peso Periodo
            20.0 // Peso Bonus de Curso
        },
        "Sistemas de Informacao", // Curso Prioritario
        3 // Periodo Prioritario
    };

    // --- EXECUÇÃO ---
    vector<Aluno> convocadosPrioridade;
    vector<Aluno> convocadosRanking;
    Queue<Aluno> listaDeEspera;

    cout << "Processando matrículas para a turma: " << turmaSI101.codigoDisciplina << endl;
    cout << "Total de Vagas: " << turmaSI101.totalVagas << endl << endl;

    processarMatriculas(alunos, turmaSI101, convocadosPrioridade, convocadosRanking, listaDeEspera);

    // --- APRESENTAÇÃO DOS RESULTADOS ---
    // --- APRESENTAÇÃO DOS RESULTADOS (TODOS OS COUT TROCADOS POR 'SAIDA') ---
    saida << "--- ALUNOS CONVOCADOS (VAGA PRIORITARIA) ---" << endl;
    if (convocadosPrioridade.empty()) {
        saida << "Nenhum aluno convocado por prioridade." << endl;
    } else {
        for(const auto& aluno : convocadosPrioridade) {
            saida << "Matricula: " << aluno.matricula << ", Nome: " << aluno.nome << endl;
        }
    }
    saida << endl;

    saida << "--- ALUNOS CONVOCADOS (RANKING GERAL) ---" << endl;
    if (convocadosRanking.empty()) {
        saida << "Nenhum aluno convocado por ranking." << endl;
    } else {
        for(const auto& aluno : convocadosRanking) {
            double pontuacao = calcularPontuacao(aluno, turmaSI101);
            saida << "Matricula: " << aluno.matricula << ", Nome: " << aluno.nome 
                          << ", Pontuacao: " << fixed << setprecision(2) << pontuacao << endl;
        }
    }
    saida << endl;

    saida << "--- LISTA DE ESPERA (POR ORDEM DE CLASSIFICACAO) ---" << endl;
    if (listaDeEspera.isEmpty()) {
        saida << "Nao ha alunos na lista de espera." << endl;
    } else {
        int pos = 1;
        while(!listaDeEspera.isEmpty()) {
            Aluno aluno = listaDeEspera.pop();
            double pontuacao = calcularPontuacao(aluno, turmaSI101);
            saida << pos++ << ".: Matricula: " << aluno.matricula << ", Nome: " << aluno.nome
                          << ", Pontuacao: " << fixed << setprecision(2) << pontuacao << endl;
        }
    }
    saida << endl;
    saida << "Total de Vagas Ocupadas: " << turmaSI101.vagasOcupadas << "/" << turmaSI101.totalVagas << endl;

    // 2. FECHAR ARQUIVO DE SAÍDA
    saida.close();
    
    // Informa o usuário no console que a operação foi concluída.
    cout << "Processamento concluido. Resultados salvos em 'resultado_matricula.txt'." << endl;

    return 0;
}