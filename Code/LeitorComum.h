#ifndef PROJETO_POO_EXP_LEITORCOMUM_H
#define PROJETO_POO_EXP_LEITORCOMUM_H

#include <iostream>
#include <map>
#include <list>
#include <string>

#include "Pessoa.h"

using namespace std;

class LeitorComum : public Pessoa {
    string Tipo;
public:
    LeitorComum(string _id, string _nome, string data_nasc, string tipo);
    ~LeitorComum(){}

    void showPessoa();
    void atribuirTipo(string tipo);

    string getTipoPessoa();
};


#endif //PROJETO_POO_EXP_LEITORCOMUM_H
