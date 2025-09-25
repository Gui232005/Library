#ifndef PROJETO_POO_EXP_EMPRESTIMOS_H
#define PROJETO_POO_EXP_EMPRESTIMOS_H

#include <iostream>
#include <string>

#include "Biblioteca.h"
#include "Livro.h"
#include "Pessoa.h"
#include "Uteis.h"

using namespace std;

class Emprestimos{
private:
    string idP;
    string idL;
    string dataFim;
    string dataInicio;
public:
    Emprestimos(){}
    Emprestimos(string IDP, string IDL, string _dataF, string _dataI); //FEITO
    ~Emprestimos(){}

    void atribuirDataFim(string _dataf){ dataFim = _dataf; }
    void atribuitDataInicio(string _datai){ dataFim = _datai; }

    void menuRelatorio();

    string getIDLivro(){ return idL; }
    string getDataIncio(){ return dataInicio; }
    string getDataFim(){ return dataFim; }
    string getIDReq(){ return idP; }
    string getInfo();

    bool isAtrasado(); /*FUNCIONAL*/

    void show();
};

#endif //PROJETO_POO_EXP_EMPRESTIMOS_H
