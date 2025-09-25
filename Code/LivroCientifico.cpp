#include "LivroCientifico.h"

using namespace std;

LivroCientico::LivroCientico(string _id, string _titulo, string _autor, string _anoPub, string edi, string categoria)
        : Livro(_id, _titulo, _autor, _anoPub){
    _edi = edi;
    _categoria = categoria;
}

void LivroCientico::showLivro() {
    Livro::showLivro();
    cout << "EDICAO:" << _edi
         << "|" << "CATEGORIA: " << _categoria << endl;
}

string LivroCientico::getInfoExtra() {
    return _edi;
}

string LivroCientico::getInfo() {
    return Livro::getInfo() + "|" + _edi + "|" + _categoria;
}

string LivroCientico::getCategoria() {
    return _categoria;
}

void LivroCientico::atribuirCat(std::string _cat) {
    _categoria = _cat;
}

void LivroCientico::atribuirInfoExtra(std::string _infoextra) {
    _edi = _infoextra;
}