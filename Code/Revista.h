#ifndef PROJETO_POO_EXP_REVISTA_H
#define PROJETO_POO_EXP_REVISTA_H

#include "Livro.h"

class Revista : public Livro {
private:
    string _edi;
    string _categoria;
public:
    Revista(string _id, string _titulo, string _autor, string _anoPub, string edi, string categoria);
    ~Revista(){}

    void showLivro();

    void atribuirCat(string _cat);
    void atribuirInfoExtra(string _infoextra);

    string getInfo();
    string getCategoria();
    string getInfoExtra();
};

#endif //PROJETO_POO_EXP_REVISTA_H
