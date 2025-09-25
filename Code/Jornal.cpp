#include "Jornal.h"

Jornal::Jornal(string _id, string _titulo, string _autor, string _anoPub, string formato, string categoria)
        : Livro(_id, _titulo, _autor, _anoPub){
    _formato = formato;
    _categoria = categoria;
}

void Jornal::showLivro() {
    Livro::showLivro();
    cout << "FORMATO: " << _formato
         << "|" << "CATEGORIA: " << _categoria << endl;
}

string Jornal::getInfoExtra() {
    return _formato;
}

string Jornal::getInfo() {
    return Livro::getInfo() + "|" + _formato + "|" + _categoria;
}

string Jornal::getCategoria() {
    return _categoria;
}

void Jornal::atribuirInfoExtra(std::string _infoextra) {
    _formato = _infoextra;
}

void Jornal::atribuirCat(std::string _cat) {
    _categoria = _cat;
}