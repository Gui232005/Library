#ifndef PROJETO_POO_EXP_SENIOR_H
#define PROJETO_POO_EXP_SENIOR_H

#include <iostream>
#include <map>
#include <string>

#include "Pessoa.h"
#include "Uteis.h"

using namespace std;

class Senior : public Pessoa {
    string Tipo;
public:
    Senior(string _id, string _nome, string data_nasc, string tipo);
    ~Senior() {}

    void showPessoa();
    void atribuirTipo(string Tipo);

    string getTipoPessoa();
};

#endif //PROJETO_POO_EXP_SENIOR_H
