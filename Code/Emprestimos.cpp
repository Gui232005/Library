#include <iostream>
#include <string>
#include <regex>
#include <chrono>
#include <ctime>

#include "Emprestimos.h"

Emprestimos::Emprestimos(string IDP, string IDL, string _dataI, string _dataF) {
    idP = IDP;
    idL = IDL;
    dataInicio = _dataI;
    dataFim = _dataF;
}

void Emprestimos::show() {
    cout << "ID Pessoa: " << idP << "\t"
              << "ID Livro: " << idL << "\t"
              << "Data Inicio: " << dataInicio << "\t"
              << "Data Fim: " << dataFim << endl;
}

string Emprestimos::getInfo() {
    string idP = getIDReq();
    string idL = getIDLivro();
    string dataI = getDataIncio();
    string dataF = getDataFim();

    string info = idP + "|" + idL + "|" + dataI + "|" + dataF;
    return info;
}

bool Emprestimos::isAtrasado() {

    auto agora = chrono::system_clock::now();

    time_t tempoAtual = chrono::system_clock::to_time_t(agora);
    tm localTime;
    localtime_s(&localTime, &tempoAtual);

    string dataFim = getDataFim();
    int diaAtual = localTime.tm_mday;
    int mesAtual = localTime.tm_mon + 1;
    int anoAtual = localTime.tm_year + 1900;

    regex del("-");
    sregex_token_iterator it(dataFim.begin(), dataFim.end(), del, -1);
    vector<string> partes(it, {});

    if (partes.size() != 3) {
        cerr << "Erro: Data inválida no formato esperado (dd-mm-aaaa): " << dataFim << endl;
        return false;
    }

    int diaFim = stoi(partes[0]);
    int mesFim = stoi(partes[1]);
    int anoFim = stoi(partes[2]);

    if (anoFim < anoAtual || (anoFim == anoAtual && mesFim < mesAtual) ||
        (anoFim == anoAtual && mesFim == mesAtual && diaFim < diaAtual)) {
        return true;
    }
    return false;
}