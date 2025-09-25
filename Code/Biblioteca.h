#ifndef PROJETO_POO_EXP_BIBLIOTECA_H
#define PROJETO_POO_EXP_BIBLIOTECA_H

#include <iostream>
#include <string>
#include <list>

#include "Livro.h"
#include "Pessoa.h"
#include "Emprestimos.h"

using namespace std;

class Livro;
class Pessoa;
class Emprestimos;

class Biblioteca{
private:
    string Nome;
    list <Livro*> *Lista_Livros;
    list <Pessoa*> *Lista_Pessoas;
    list <Emprestimos*> *Lista_Emprestimos_Ativos;
    list <Emprestimos*> *Lista_Emprestimos_Passados;
    list <Emprestimos*> *Lista_Reservas;
    list <Emprestimos* > *Lista_Multas;

public:
    Biblioteca(string nome);
    ~Biblioteca();

    //LIVRO

    void loadLivrosFile(string file); /*FUNCIONAL*/
    void storeLivros(string file); /*FEITO*/
    void showLivros(); /*FUNCIONAL*/
    void relatorioCategoria(string categoria); /*FEITO*/
    void removeLivro(string _id); /*FUNCIONAL*/

    Livro* atribuirLivro(string _id); /*FUNCIONAL*/

    //PESSOAS

    void loadPessoasFile(string file); /*FUNCIONAL*/
    void storePessoas(string file); /*FEITO*/
    void showPessoas(); /*FUNCIONAL*/
    void pesquisarPessoas(string _id); /*FUNCIONAL*/
    void removerPessoas(string _id); /*FUNCIONAL*/

    Pessoa* atribuirPessoa(string _id);

    //EMPRESTIMOS

    void listarEmprestimos(string tipo); /*FUNCIONAL*/
    void procurarEmprestimos(string _id, string tipo); /*FUNCIONAL*/
    void storeEmprestimos(string file, string tipo); /*REVER*/
    void loadFileEmprestimos(string file, string tipo); /*FUNCIONAL*/
    void listarAtrasos(); /*FUNCIONAL*/
    void reservarLivro(); /*FUNCIONAL*/
    void cancelarReservaLivro();
    void statusEmprestimo();
    void statusResevervas();
    void menuRelatorio();
    void devolverEmprestimo();

    float calculoDesc(string idP);

    Emprestimos* atribuirEmprestimo(string _id);

    bool verSeLivroEstaRequesitado(string idL); /*FUNCIONAL*/
    bool verSeLivroEstaReservado(string idL); /*FUNCIONAL*/

    string calcularDataFinalReserva(string dataInicio, int diasReserva); /*FUNCIONAL*/
    string diasRequesicao(string _idP, string _idL); /*FUNCIONAL*/
    string dataEntrega(string idP, string idL); /*FUNCIONAL*/

    //MENUS

    void menuBiblioteca();
    void menuLivros();
    void menuRequisicoes();
    void menuLeitores();

    //MULTAS

    //MEMORIA


};

#endif //PROJETO_POO_EXP_BIBLIOTECA_H
