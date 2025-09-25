#include <iostream>
#include <string>
#include <map>
#include <list>

#include "LeitorComum.h"

LeitorComum::LeitorComum(std::string _id, std::string _nome, std::string data_nasc, std::string tipo)
        :Pessoa(_id, _nome, data_nasc) {
    Tipo = tipo;
}

string LeitorComum::getTipoPessoa() {
    return Tipo;
}

void LeitorComum::showPessoa(){
    Pessoa::showPessoa();
    cout << "Categoria:" << "Leitor Comum" << endl;
}

void LeitorComum::atribuirTipo(std::string tipo) {
    Tipo = tipo;
}