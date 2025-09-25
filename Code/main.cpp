#include "Biblioteca.h"

using namespace std;

int main() {

    Biblioteca *B = new Biblioteca("ESTGV-Biblioteca");

    B->loadLivrosFile("Livros.txt");
    B->loadPessoasFile("Leitores.txt");
    B->loadFileEmprestimos("Emprestimos_Ativos.txt", "Atual");
    B->loadFileEmprestimos("Emprestimos_Ativos.txt", "Passado");
    B->loadFileEmprestimos("Reservas.txt", "Reserva");
    B->loadFileEmprestimos("Multas.txt", "Multa");

    B->menuBiblioteca();

    delete B;

    return 0;
}
