#include "Estudante.h"

Estudante::Estudante(std::string _id, std::string _nome, std::string data_nasc, std::string tipo)
        :Pessoa(_id, _nome, data_nasc) {
    Tipo = tipo;
}

string Estudante::getTipoPessoa() {
    return Tipo;
}

void Estudante::showPessoa(){
    Pessoa::showPessoa();
    cout << " Categoria: Estudante" << endl;
}

void Estudante::atribuirTipo(std::string tipo) {
    Tipo = tipo;
}