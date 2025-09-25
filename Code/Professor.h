#ifndef PROJETO_POO_EXP_PROFESSOR_H
#define PROJETO_POO_EXP_PROFESSOR_H

#include <iostream>
#include <string>
#include <list>
#include <map>

#include "Livro.h"
#include "Uteis.h" // Adicionado

#include <iostream>
#include <string>
#include <map>

#include "Pessoa.h"

using namespace std;

class Professor : public Pessoa{
private:
    string Tipo;
public:
    Professor(string _id, string _nome, string data_nasc, string tipo);
    ~Professor(){}

    void showPessoa();
    void atribuirTipo(string tipo);

    string getTipoPessoa();
};


#endif //PROJETO_POO_EXP_PROFESSOR_H
