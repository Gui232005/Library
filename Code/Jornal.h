#ifndef PROJETO_POO_EXP_JORNAL_H
#define PROJETO_POO_EXP_JORNAL_H

#include "Livro.h"

class Jornal : public Livro{
private:
    string _formato;
    string _categoria;
public:
    Jornal(string _id, string _titulo, string _autor, string _anoPub, string formato, string categoria);
    ~Jornal(){}

    void showLivro();

    void atribuirCat(string _cat);
    void atribuirInfoExtra(string _infoextra);

    string getInfo();
    string getCategoria();
    string getInfoExtra();
};

#endif //PROJETO_POO_EXP_JORNAL_H
