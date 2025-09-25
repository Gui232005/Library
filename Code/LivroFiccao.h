#ifndef PROJETO_POO_EXP_LIVROFICCAO_H
#define PROJETO_POO_EXP_LIVROFICCAO_H

#include "Livro.h"

class LivroFiccao : public Livro{
private:
    string _edi;
    string _categoria;
public:
    LivroFiccao(string _id, string _titulo, string _autor, string _anoPub, string edi, string categoria);
    ~LivroFiccao(){}

    void showLivro();

    void atribuirCat(string _cat);
    void atribuirInfoExtra(string _infoextra);

    string getInfo();
    string getCategoria();
    string getInfoExtra();
};

#endif //PROJETO_POO_EXP_LIVROFICCAO_H
