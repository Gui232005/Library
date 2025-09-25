#ifndef PROJETO_POO_EXP_LIVROCIENTIFICO_H
#define PROJETO_POO_EXP_LIVROCIENTIFICO_H

#include "Livro.h"

class LivroCientico : public Livro{
private:
    string _edi;
    string _categoria;
public:
    LivroCientico(string _id, string _titulo, string _autor, string _anoPub, string edi, string categoria);
    ~LivroCientico() {}

    void showLivro();

    void atribuirCat(string _cat);
    void atribuirInfoExtra(string _infoextra);

    string getInfo();
    string getCategoria();
    string getInfoExtra();
};

#endif //PROJETO_POO_EXP_LIVROCIENTIFICO_H
