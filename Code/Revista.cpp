#include <iostream>
#include <map>

#include "Revista.h"

using namespace std;

Revista::Revista(string _id, string _titulo, string _autor, string _anoPub, string edi, string categoria)
        : Livro(_id, _titulo, _autor, _anoPub) {
    _edi = edi;
    _categoria = categoria;
}

void Revista::showLivro() {
    Livro::showLivro();
    cout << "EDICAO:" << _edi
         << "|" << "CATEGORIA: " << _categoria << endl;
}

string Revista::getInfo() {
    return Livro::getInfo() + "|" + _edi + "|" + _categoria;
}

string Revista::getInfoExtra() {
    return _edi;
}

void Revista::atribuirCat(std::string _cat) {
    _categoria = _cat;
}

void Revista::atribuirInfoExtra(std::string _infoextra) {
    _edi = _infoextra;
}

string Revista::getCategoria() {
    return _categoria;
}