#include "Senior.h"

Senior::Senior(std::string _id, std::string _nome, std::string data_nasc, std::string tipo)
        :Pessoa(_id, _nome, data_nasc){
    Tipo = tipo;
}

string Senior::getTipoPessoa() {
    return Tipo;
}

void Senior::showPessoa(){
    Pessoa::showPessoa();
    cout << "Categoria: Senior" << endl;
}

void Senior::atribuirTipo(std::string tipo) {
    Tipo = tipo;
}