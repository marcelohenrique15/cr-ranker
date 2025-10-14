@echo off
REM ==============================
REM Build e execução do projeto CMake no Windows
REM ==============================

echo.
echo ==== Limpando e criando build ====
if not exist build mkdir build
cd build

echo.
echo ==== Gerando arquivos CMake ====
cmake .. -G "MinGW Makefiles"

echo.
echo ==== Compilando projeto ====
mingw32-make

if %errorlevel% neq 0 (
    echo.
    echo [ERRO] Falha na compilação.
    pause
    exit /b %errorlevel%
)

echo.
echo ==== Preparando arquivos de dados ====
copy ..\alunos.txt .

if %errorlevel% neq 0 (
    echo [AVISO] O arquivo alunos.txt nao foi encontrado no diretorio raiz e nao foi copiado.
)

echo.
echo ==== Executando programa ====
CR_RANKER.exe

echo.
pause
