#include <iostream>

#include "Livro.h"

using namespace std;

string Livro::getInfo() {
    return ID + "|" + Titulo + "|" + Autor + "|" + Ano_Pub;
}

void Livro::showLivro() {
    cout << "ID: " << ID << "|" << "TITULO: " << Titulo << "|"
         << "AUTOR: " << Autor << "|"
         << "ANO PUBLICACAO: " << Ano_Pub << endl;
}

void Livro::escolherInfoLivro() {
    cout << "Entrou na funcao" << __FUNCTION__ << endl;
    string cat = getCategoria();
    cout << cat;
    int opc = -1;
    do {
        // Exibe o menu genérico
        cout << "\nEscolha uma opcao para editar:\n";
        cout << "[1] TITULO\n";
        cout << "[2] AUTOR\n";
        cout << "[3] CATEGORIA\n";
        cout << "[4] ANO PUBLICACAO\n";

        if (cat == "Cientifico" || cat == "Revista") {
            cout << "[5] EDICAO\n";
        } else if (cat == "Educativo") {
            cout << "[5] GRAU ESCOLARIDADE\n";
        } else if (cat == "Jornal") {
            cout << "[5] FORMATO\n";
        }

        cout << "[0] VOLTAR\n";
        cout << "Opcao: ";
        cin >> opc;

        switch (opc) {
            case 1: {
                string titulo;
                cout << "Qual o novo titulo: ";
                cin.ignore();
                getline(cin, titulo);
                Titulo = titulo;
                break;
            }
            case 2: {
                string autor;
                cout << "Qual o novo nome do autor: ";
                cin.ignore();
                getline(cin, autor);
                Autor = autor;
                break;
            }
            case 3: {
                string novaCat;
                cout << "Qual a nova categoria: ";
                cin.ignore();
                getline(cin, novaCat);
                atribuirCat(novaCat);
                break;
            }
            case 4: {
                string anoPub;
                cout << "Qual o novo ano de publicacao: ";
                cin.ignore();
                getline(cin, anoPub);
                Ano_Pub = anoPub;
                break;
            }
            case 5: {
                string extra;
                if (cat == "Cientifico" || cat == "Revista") {
                    cout << "Qual a nova edicao: ";
                } else if (cat == "Educativo") {
                    cout << "Qual o novo grau de escolaridade: ";
                } else if (cat == "Jornal") {
                    cout << "Qual o novo formato: ";
                }
                cin.ignore();
                getline(cin, extra);
                atribuirInfoExtra(extra);
                break;
            }
            case 0:
                /*COLOCAR O MENU CORRESPONDENTE*/
                break;
            default:
                cout << "Opcao invalida. Tente novamente.\n";
                break;
        }
    } while (opc != 0);
}
