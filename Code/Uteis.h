#ifndef PROJETO_POO_EXP_UTEIS_H
#define PROJETO_POO_EXP_UTEIS_H

#include <iostream>
#include <list>
#include <ostream>
#include <map>

using namespace std;

class Pessoa;
class Livro;

class Uteis{
private:
    static size_t memoria_alocada;
public:
    Uteis() {}
    ~Uteis() {}

    void pausarTela(); /*FEITO*/
    void delay(int s); /*FEITO*/

    string dataAtual(); /*FEITO*/

    bool anoBissexto(int ano); /*FEITO*/

    int calcularDiferencaDias(string data1, string data2);/*FEITO*/
    int diasNoMes(int mes, int ano); /*FEITO*/

    //MEMORIA
    void adicionarMemoria(size_t tamanho); /*FEITO*/
    void removerMemoria(size_t tamanho); /*FEITO*/
    size_t memoriaAtual(); /*FEITO*/
    void exibirMemoriaFinal(); /*FEITO*/
};

#endif //PROJETO_POO_EXP_UTEIS_H
