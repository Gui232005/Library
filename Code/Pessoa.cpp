#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <thread>
#include <regex>
#include <algorithm>
#include <sstream>

#include "LeitorComum.h"
#include "Professor.h"
#include "Senior.h"
#include "Estudante.h"
#include "Uteis.h"
#include "Livro.h"

using namespace std;

void Pessoa::showPessoa() {
    cout << "ID: " << ID << "\t" << "NOME: "
         << Nome << "\t"  << "DATA NASCIMENTO: " << Data_Nasc << endl;
}

void Pessoa::escolherInfoPessoa() {
    string tipo = getTipoPessoa();
    int opc = -1;

    do {
        cout << "\nEscolha uma opcao para editar:\n";
        cout << "[1] NOME\n";
        cout << "[2] DATA NASCIMENTO\n";
        cout << "[3] TIPO PESSOA\n";
        cout << "[0] VOLTAR\n";
        cout << "Opcao: ";
        cin >> opc;
        switch (opc) {
            case 1: {
                string nome;
                cout << "Qual o novo nome: ";
                cin.ignore();
                getline(cin, nome);
                Nome = nome;
                break;
            }
            case 2: {
                string ano;
                cout << "Qual a nova data de nascimento [dd-mm-aaaa]: ";
                cin.ignore();
                getline(cin, ano);
                Data_Nasc = ano;
                break;
            }
            case 3: {
                string tipo;
                cout << "Qual o novo tipo de pessoa: ";
                cin.ignore();
                getline(cin, tipo);
                atribuitTipo(tipo);
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