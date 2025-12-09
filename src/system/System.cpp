#include "System.h"

using namespace std;

AcademicSystem::AcademicSystem(){}

void AcademicSystem::merge(vector<Student>& arr, int left, int mid, int right) 
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Student> L(n1);
    vector<Student> R(n2);

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int i = 0; i < n2; i++) R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) 
    {
        if (L[i].score >= R[j].score) 
        {
            arr[k++] = L[i++];
        } 
        
        else 
        {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void AcademicSystem::mergeSort(vector<Student>& arr, int left, int right) 
{
    if (left < right) 
    {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

void AcademicSystem::sort(vector<Student>& arr) 
{
    if (!arr.empty())
    {
        mergeSort(arr, 0, arr.size() - 1);
    }
}

void AcademicSystem::registerStudent()
{
    int opcao;
    cout << "Como deseja cadastrar estudantes?\n";
    cout << "1. Cadastrar apenas um estudante\n";
    cout << "2. Importar lista de estudantes via CSV\n";
    cout << "Escolha: ";
    cin >> opcao;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // ----------------------------------------------------------
    // MODO 1 — CADASTRO MANUAL
    // ----------------------------------------------------------
    if (opcao == 1)
    {
        Student currentStudent;

        cout << "Nome do Estudante: ";
        getline(cin, currentStudent.name);

        cout << "Matrícula do Estudante: ";
        cin >> currentStudent.registration;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Curso do Estudante: ";
        getline(cin, currentStudent.course);

        cout << "Período do Estudante: ";
        cin >> currentStudent.semester;

        cout << "Coeficiente de Rendimento do Estudante: ";
        cin >> currentStudent.yieldCoefficient;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        students.insert(currentStudent);
        studentsList.push_back(currentStudent);

        cout << "\nEstudante cadastrado com sucesso!\n";
        cout << "Aperte ENTER para continuar...";
        cin.get();
        return;
    }

    // ----------------------------------------------------------
    // MODO 2 — IMPORTAR CSV COM VÁRIOS ESTUDANTES
    // ----------------------------------------------------------
    else if (opcao == 2)
    {
        cout << "Selecione o arquivo CSV contendo: \n";
        cout << "matricula,nome,curso,semestre,coeficiente\n\n";

        FILE* pipe = popen("zenity --file-selection --title=\"Selecione CSV de estudantes\" 2>/dev/null", "r");

        if (!pipe)
        {
            cout << "Erro ao abrir seletor de arquivos.\n";
            return;
        }

        char buffer[512];
        string filePath;

        if (fgets(buffer, sizeof(buffer), pipe) != nullptr)
        {
            filePath = buffer;
            filePath.erase(filePath.find_last_not_of("\n") + 1);
        }

        pclose(pipe);

        if (filePath.empty())
        {
            cout << "Nenhum arquivo selecionado.\n";
            return;
        }

        cout << "Arquivo selecionado: " << filePath << "\n";

        ifstream file(filePath);

        if (!file.is_open())
        {
            cout << "Erro ao abrir o arquivo CSV!\n";
            return;
        }

        string line;
        int imported = 0;
        bool firstLine = true;

        while (getline(file, line))
        {
            if (line.empty()) continue;

            // Remover espaços extras
            line.erase(remove_if(line.begin(), line.end(), 
                                 [](unsigned char c){ return c == '\r'; }),
                       line.end());

            // Pular cabeçalho
            if (firstLine)
            {
                firstLine = false;
                continue;
            }

            stringstream ss(line);
            string regStr, name, course, semStr, coefStr;

            if (!getline(ss, regStr, ',')) continue;
            if (!getline(ss, name, ',')) continue;
            if (!getline(ss, course, ',')) continue;
            if (!getline(ss, semStr, ',')) continue;
            if (!getline(ss, coefStr, ',')) continue;

            // Remover espaços extras de cada campo
            auto trim = [&](string& s) {
                s.erase(0, s.find_first_not_of(" \t"));
                s.erase(s.find_last_not_of(" \t") + 1);
            };
            trim(regStr);
            trim(name);
            trim(course);
            trim(semStr);
            trim(coefStr);

            // Verificar se campos numéricos são válidos
            try {
                int reg = stoi(regStr);
                int sem = stoi(semStr);
                double coef = stod(coefStr);

                Student s;
                s.registration = reg;
                s.name = name;
                s.course = course;
                s.semester = sem;
                s.yieldCoefficient = coef;

                students.insert(s);
                studentsList.push_back(s);

                imported++;
            }
            catch (...)
            {
                cout << "Linha inválida ignorada: " << line << "\n";
                continue;
            }
        }

        file.close();

        cout << "\n" << imported << " estudantes importados com sucesso!\n";
        cout << "Aperte ENTER para continuar...";
        cin.get();
        return;
    }

    // ----------------------------------------------------------
    // OPÇÃO INVÁLIDA
    // ----------------------------------------------------------
    else
    {
        cout << "Opção inválida!\n";
        cout << "Aperte ENTER para continuar...";
        cin.get();
    }
}

void AcademicSystem::registerSubject()
{
    Subject* subject = new Subject();

    cout << "Código da Disciplina: ";
    cin >> subject->code;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  

    cout << "Nome da Disciplina: ";
    getline(cin, subject->name);   

    cout << "Curso da Disciplina: ";
    getline(cin, subject->course); 

    cout << "Número de Vagas da Disciplina: ";
    cin >> subject->vacancyNum;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    subjects.insert(subject);
    subjectsList.push_back(subject);

    cout << "\nDisciplina cadastrada com sucesso!\n";
    cout << "Aperte ENTER para continuar...";
    cin.get();
}

void AcademicSystem::showStudents()
{
    cout << "Matrícula, Nome, Coeficiente de Rendimento, Curso, Período\n";

    for(Student s : studentsList)
    {
        cout << s.registration << ", " << s.name << ", " << s.yieldCoefficient << ", " << s.course << ", " << s.semester << endl;
    }

    cout << "Aperte ENTER para continuar...";
    cin.get();
}

void AcademicSystem::showSubjects()
{
    cout << "Código da Disciplina, Nome, Curso, Número de Vagas\n";

    for(Subject* s : subjectsList)
    {
        cout << s->code << ", " << s->name << ", " << s->course << ", " << s->vacancyNum << endl;
    }

    cout << "Aperte ENTER para continuar...";
    cin.get();
}

void AcademicSystem::showApprovedStudents()
{
    int pos = 1;

    while (!approvedStudents.isEmpty())
    {
        Student s = approvedStudents.dequeue();
        cout << pos++ << "°: " << s.name << " (CR: " << s.yieldCoefficient << ", SCORE: " << s.score << ")\n";
    }

    cout << "\nAperte ENTER para continuar...";

    // LIMPAR BUFFER ANTES DE ESPERAR O ENTER
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void AcademicSystem::proccessRanking()
{
    // ----------------------------
    // 1. Abrir explorador de arquivos (zenity)
    // ----------------------------
    FILE* pipe = popen("zenity --file-selection --title=\"Selecione o CSV de matrículas\" 2>/dev/null", "r");

    if (!pipe) {
        std::cout << "Erro ao abrir janela de seleção.\n";
        return;
    }

    char buffer[512];
    std::string filePath;

    if (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        filePath = buffer;
        // zenity adiciona uma quebra de linha no final
        filePath.erase(filePath.find_last_not_of("\n") + 1);
    }

    pclose(pipe);

    if (filePath.empty()) {
        std::cout << "Nenhum arquivo selecionado.\n";
        return;
    }

    std::cout << "Arquivo selecionado: " << filePath << "\n";

    // --------------------------------------
    // 2. Ler CSV contendo apenas matrículas
    // --------------------------------------
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cout << "Erro ao abrir arquivo CSV.\n";
        return;
    }

    std::vector<int> candidateRegistrations;
    std::string line;

    while (std::getline(file, line))
    {
        if (line.empty()) continue;

        int reg = std::stoi(line);
        candidateRegistrations.push_back(reg);
    }

    file.close();

    // -------------------------------
    // 3. Solicitar a disciplina
    // -------------------------------
    std::string subjectCode;
    std::cout << "Digite o código da disciplina: ";
    std::cin >> subjectCode;

    Subject* currentSubject = subjects.search(subjectCode);

    if (!currentSubject) {
        std::cout << "Disciplina não encontrada!\n";
        return;
    }

    // ------------------------------------------
    // 4. Buscar alunos na BST e calcular scores
    // ------------------------------------------
    std::vector<Student> rankedStudents;

    for (int reg : candidateRegistrations)
    {
        Student* st = students.search(reg);

        if (st)
        {
            rankedStudents.push_back(*st);
        }
        else
        {
            std::cout << "Aluno com matrícula " << reg << " não encontrado.\n";
        }
    }

    // ------------------------------------------
    // 5. Calcular score
    // ------------------------------------------
    for (Student& st : rankedStudents)
    {
        double cr = st.yieldCoefficient;
        double semesterNorm = st.semester / 10.0;
        double sameCourseBonus = (st.course == currentSubject->course) ? 0.20 : 0.0;

        st.score = (cr * 0.60) + (semesterNorm * 0.30) + sameCourseBonus;
    }

    // ------------------------------------------
    // 6. Ordenar (usar seu merge sort)
    // ------------------------------------------
    sort(rankedStudents);

    // ------------------------------------------
    // 7. Limitar ao número de vagas
    // ------------------------------------------
    if (rankedStudents.size() > currentSubject->vacancyNum)
    {
        rankedStudents.resize(currentSubject->vacancyNum);
    }

    // ------------------------------------------
    // 8. Enfileirar aprovados
    // ------------------------------------------
    for (const Student& st : rankedStudents)
    {
        approvedStudents.enqueue(st);
    }

    // ------------------------------------------
    // 9. Mostrar aprovados
    // ------------------------------------------
    showApprovedStudents();
}

void AcademicSystem::menu()
{
    int opcao;

    do
    {
        system("clear");
        
        cout << "\n==== SISTEMA ACADÊMICO ====\n";
        cout << "1. Cadastrar estudante\n";
        cout << "2. Cadastrar disciplina\n";
        cout << "3. Listar estudantes\n";
        cout << "4. Listar disciplinas\n";
        cout << "5. Gerar ranking de aprovados em uma disciplina\n";
        cout << "6. Encerrar programa\n";
        cout << "Escolha: ";

        cin >> opcao;

        system("clear");

        if (cin.fail()) 
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada inválida!\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(opcao)
        {
            case 1: registerStudent(); break;
            case 2: registerSubject(); break;
            case 3: showStudents(); break;
            case 4: showSubjects(); break;
            case 5: proccessRanking(); break;
        }

    } while(opcao != 6);
}
