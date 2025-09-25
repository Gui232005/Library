#ifndef PROJETO_POO_EXP_LIVROEDUCATIVO_H
#define PROJETO_POO_EXP_LIVROEDUCATIVO_H

#include "Livro.h"

class LivroEducativo : public Livro{
private:
    string grauEscolaridade;
    string _categoria;
public:
    LivroEducativo(string _id, string _titulo, string _autor, string _anoPub, string grauescolaridade, string categoria);
    ~LivroEducativo(){}

    void showLivro();

    void atribuirCat(string _cat);
    void atribuirInfoExtra(string _infoextra);

    string getInfo();
    string getCategoria();
    string getInfoExtra();
};

#endif //PROJETO_POO_EXP_LIVROEDUCATIVO_H
