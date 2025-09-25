#ifndef PROJETO_POO_EXP_PESSOA_H
#define PROJETO_POO_EXP_PESSOA_H

#include <iostream>
#include <string>
#include <list>
#include <map>

#include "Livro.h"
#include "Uteis.h"

using namespace std;

class Pessoa {
private:
    string ID;
    string Nome;
    string Data_Nasc;
public:
    Pessoa(){}
    Pessoa(string _id, string _nome, string data_nasc) {
        ID = _id;
        Nome = _nome;
        Data_Nasc = data_nasc;
    }
    ~Pessoa() {}

    string getID() { return ID; }
    string getNome() { return Nome; }
    string getDataNasc() { return Data_Nasc; }

    virtual string getTipoPessoa(){ }

    virtual void atribuitTipo(string tipo){}/*FAZER O VIRTUAL E ALTERAR CLASS A CLASS*/

    void escolherInfoPessoa(); /*FUNCIONAL*/

    virtual void showPessoa(); /*FAZER O VIRTUAL E ALTERAR CLASS A CLASS*/
};

#endif //PROJETO_POO_EXP_PESSOA_H
