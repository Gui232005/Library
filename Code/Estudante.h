#ifndef PROJETO_POO_EXP_ESTUDANTE_H
#define PROJETO_POO_EXP_ESTUDANTE_H

#include <iostream>
#include <string>

#include "Pessoa.h"

using namespace std;

class Estudante : public Pessoa{
    string Tipo;
public:
    Estudante(string _id, string _nome, string data_nasc, string tipo);
    ~Estudante(){}

    void showPessoa();
    void atribuirTipo(string tipo);

    string getTipoPessoa();
};

#endif //PROJETO_POO_EXP_ESTUDANTE_H
