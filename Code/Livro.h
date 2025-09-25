#ifndef PROJETO_POO_EXP_LIVRO_H
#define PROJETO_POO_EXP_LIVRO_H

#include <iostream>
#include <string>
#include <list>

using namespace std;

class Livro {
private:
    string ID;
    string Titulo;
    string Autor;
    string Ano_Pub;
public:
    Livro(){}
    Livro(string _id, string _titulo, string _autor, string _anoPub) {
        ID = _id;
        Titulo = _titulo;
        Autor = _autor;
        Ano_Pub = _anoPub;
    }
    virtual ~Livro() {}

    string getID() { return ID; }

    void escolherInfoLivro();//FUNCIONA

    virtual void showLivro(); //FUNCIONA

    virtual void atribuirCat(string _cat) {}
    virtual void atribuirInfoExtra(string _infoextra) {}

    virtual string getInfo();
    virtual string getInfoExtra() {} //FEITO
    virtual string getCategoria() { return  "CHORICO"; } //FEITO
};

#endif //PROJETO_POO_EXP_LIVRO_H
