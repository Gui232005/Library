#include <ctime>
#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <iomanip>
#include <sstream>

#include "Uteis.h"

size_t Uteis::memoria_alocada = 0;

using namespace std;

void Uteis::pausarTela() {
#ifdef _WIN32
    system("pause"); // Pausa a execução no Windows
#else
    cout << "Pressione Enter para continuar...";
    cin.ignore();
    cin.get();
#endif
}

void Uteis::delay(int s) {
    using namespace this_thread;
    using namespace chrono;

    //this_thread::chrono::sleep_for(seconds(s))
    sleep_for(seconds(s));
}

int Uteis::calcularDiferencaDias(string data1, string data2) {

    int dia1 = stoi(data1.substr(0, 2));
    int mes1 = stoi(data1.substr(3, 2));
    int ano1 = stoi(data1.substr(6, 4));

    int dia2 = stoi(data2.substr(0, 2));
    int mes2 = stoi(data2.substr(3, 2));
    int ano2 = stoi(data2.substr(6, 4));

    tm tmData1 = {};
    tmData1.tm_year = ano1 - 1900;
    tmData1.tm_mon = mes1 - 1;
    tmData1.tm_mday = dia1;

    tm tmData2 = {};
    tmData2.tm_year = ano2 - 1900;
    tmData2.tm_mon = mes2 - 1;
    tmData2.tm_mday = dia2;

    time_t tData1 = mktime(&tmData1);
    time_t tData2 = mktime(&tmData2);

    double diffSegundos = difftime(tData2, tData1);
    int diffDias = static_cast<int>(diffSegundos / (60 * 60 * 24));

    return diffDias;
}

string Uteis::dataAtual() {
    time_t now = time(0);
    tm ltm;
    localtime_s(&ltm, &now); // Usando localtime_s

    ostringstream oss;
    oss << std::setw(2) << setfill('0') << ltm.tm_mon + 1; // Mês com dois dígitos

    string data = to_string(ltm.tm_mday) + "-" +
                       oss.str() + "-" +
                       to_string(1900 + ltm.tm_year);
    return data;
}

bool Uteis::anoBissexto(int ano) {
    // Verifica se o ano é bissexto
    return (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0));
}

int Uteis::diasNoMes(int mes, int ano) {
    // Retorna o número de dias no mês, considerando anos bissextos para fevereiro
    switch (mes) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
        case 4: case 6: case 9: case 11: return 30;
        case 2: return anoBissexto(ano) ? 29 : 28;
        default: return 0;  // Meses inválidos
    }
}

/*====MEMORIA ALOCACAO====*/

// Variável estática para rastrear memória
static size_t memoria_alocada = 0;

void Uteis::adicionarMemoria(size_t tamanho) {
    memoria_alocada += tamanho;
}

void Uteis::removerMemoria(size_t tamanho) {
    memoria_alocada -= tamanho;
}

size_t Uteis::memoriaAtual() {
    return memoria_alocada;
}

void Uteis::exibirMemoriaFinal() {
    cout << "\nMemoria total alocada: " << memoriaAtual() << " bytes\n";
    if (memoriaAtual() != 0) {
        cout << "Aviso: Existe memoria nao libertada!\n";
    }
}
