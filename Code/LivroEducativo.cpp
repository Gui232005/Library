#include "LivroEducativo.h"

LivroEducativo::LivroEducativo(string _id, string _titulo, string _autor, string _anoPub, string grauescolaridade, string categoria)
        : Livro(_id, _titulo, _autor, _anoPub){
    grauEscolaridade = grauescolaridade;
    _categoria = categoria;
}

void LivroEducativo::showLivro() {
    Livro::showLivro();
    cout << "GRAU ESCOLARIDADE:" << grauEscolaridade
         << "|" << "CATEGORIA: " << _categoria << endl;
}

void LivroEducativo::atribuirCat(std::string _cat) {
    _categoria = _cat;
}

void LivroEducativo::atribuirInfoExtra(std::string _infoextra) {
    grauEscolaridade = _infoextra;
}

string LivroEducativo::getInfo() {
    return Livro::getInfo() + "|" + grauEscolaridade + "|" + _categoria;
}

string LivroEducativo::getCategoria() {
    return _categoria;
}

string LivroEducativo::getInfoExtra() {
    return grauEscolaridade;
}
