#include "Professor.h"

Professor::Professor(std::string _id, std::string _nome, std::string data_nasc, std::string tipo)
        : Pessoa(_id, _nome, data_nasc) {
    Tipo = tipo;
}

string Professor::getTipoPessoa() {
    return Tipo;
}

void Professor::showPessoa() {
    Pessoa::showPessoa();
    cout << " Categoria: Professor" << endl;
}

void Professor::atribuirTipo(std::string tipo) {
    Tipo = tipo;
}