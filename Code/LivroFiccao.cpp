#include "LivroFiccao.h"

LivroFiccao::LivroFiccao(string _id, string _titulo, string _autor, string _anoPub, string edi, string categoria)
        : Livro(_id, _titulo, _autor, _anoPub){
    _edi = edi;
    _categoria = categoria;
}

void LivroFiccao::showLivro() {
    Livro::showLivro();
    cout << "EDICAO:" << _edi
         << "|" << "CATEGORIA: " << _categoria << endl;
}

string LivroFiccao::getInfoExtra() {
    return _edi;
}

string LivroFiccao::getInfo() {
    return Livro::getInfo() + "|" + _edi + "|" + _categoria;
}

void LivroFiccao::atribuirCat(std::string _cat) {
    _categoria = _cat;
}

void LivroFiccao::atribuirInfoExtra(std::string _infoextra) {
    _edi = _infoextra;
}

string LivroFiccao::getCategoria() {
    return _categoria;
}