#include <fstream>
#include <regex>
#include <sstream>

#include "Biblioteca.h"
/*SUBCLASSES*/
#include "Jornal.h"
#include "LivroCientifico.h"
#include "LivroFiccao.h"
#include "LivroEducativo.h"
#include "Revista.h"

#include "Pessoa.h"
/*SUBCLASSES*/
#include "LeitorComum.h"
#include "Senior.h"
#include "Professor.h"
#include "Estudante.h"

Biblioteca::Biblioteca(std::string nome) {
    Nome = nome;
    Lista_Livros = new list<Livro*>();
    Lista_Pessoas = new list<Pessoa*>();
    Lista_Emprestimos_Ativos = new list<Emprestimos*>();
    Lista_Emprestimos_Passados = new list<Emprestimos*>();
    Lista_Reservas = new list <Emprestimos*>();
    Lista_Multas = new list<Emprestimos*>();
}

Biblioteca::~Biblioteca(){
    for (Livro* livro : *Lista_Livros) delete livro;
    delete Lista_Livros;

    for (Pessoa* pessoa : *Lista_Pessoas) delete pessoa;
    delete Lista_Pessoas;

    for (Emprestimos* emprestimo : *Lista_Emprestimos_Ativos) delete emprestimo;
    delete Lista_Emprestimos_Ativos;

    for (Emprestimos* emprestimo : *Lista_Emprestimos_Passados) delete emprestimo;
    delete Lista_Emprestimos_Passados;

    for (Emprestimos* emprestimo : *Lista_Multas) delete emprestimo;
    delete Lista_Multas;
}

/*LIVRO*/

void Biblioteca::loadLivrosFile(string file) {
    string id, titulo, autor, anoPub, categoria, infoextra;

    fstream F(file, ios::in);

    if (!F.is_open()) {
        cerr << "Erro ao abrir o ficheiro: " << file << endl;
        return;
    }

    if (!Lista_Livros) {
        cerr << "Erro: Lista_Livros não está inicializada!" << endl;
        return;
    }

    string linha;
    while (getline(F, linha)) {
        //cout << "Linha lida: " << linha << endl;

        stringstream ss(linha);
        getline(ss, id, '|');
        getline(ss, titulo, '|');
        getline(ss, autor, '|');
        getline(ss, anoPub, '|');
        getline(ss, infoextra, '|');
        getline(ss, categoria, '\n');

        Livro* L = nullptr;

        //cout << "Criando objeto da categoria: " << categoria << endl;

        if (categoria == "Jornal")        L = new Jornal(id, titulo, autor, anoPub, infoextra, categoria);
        else if (categoria == "Revista")  L = new Revista(id, titulo, autor, anoPub, infoextra, categoria);
        else if (categoria == "Cientifico") L = new LivroCientico(id, titulo, autor, anoPub, infoextra, categoria);
        else if (categoria == "Ficcao")   L = new LivroFiccao(id, titulo, autor, anoPub, infoextra, categoria);
        else if (categoria == "Educativo") L = new LivroEducativo(id, titulo, autor, anoPub, infoextra, categoria);
        else {
            cerr << "Erro: Categoria invalida -> " << categoria << endl;
            continue;
        }

        if (L) {
            /*
            cout << "Livro valido e adicionado" << endl;
            cout << "---------------------------------------------" << endl;
            cout << "ID: " << id << endl;
            cout << "TITULO: " << titulo << endl;
            cout << "AUTOR: " << autor << endl;
            cout << "CATEGORIA: " << categoria << endl;
            cout << "ANO PUB: " << anoPub << endl;
            cout << "INFO EXTRA: " << infoextra << endl;
            cout << "---------------------------------------------" << endl;
             */
            Lista_Livros->push_back(L);
        } else {
            cerr << "Erro: ponteiro inválido" << endl;
        }
    }

    if (Lista_Livros->empty()) {
        cout << "Não há livros para carregar." << endl;
    }

    if (F.is_open()) {
        F.close();
    }
}

void Biblioteca::showLivros() {

    if (!Lista_Livros) {
        cout << "Erro: Lista_Livros é nullptr!" << endl;
        return;
    }

    if (Lista_Livros->empty()) {
        cout << "A lista de livros está vazia." << endl;
        return;
    }

    for (auto &i : *Lista_Livros) {
        cout << "ENTROU NO FOR" << endl;

        if (!i) {
            cout << "Erro: Ponteiro de livro inválido!" << endl;
            continue;
        }

        i->showLivro();
    }
}


void Biblioteca::storeLivros(string file) {
    ofstream F(file, ios::out);

    if (!F.is_open()) {
        cerr << "Erro ao abrir o arquivo para escrita." << endl;
        return;
    }

    for (auto livro = Lista_Livros->begin(); livro != Lista_Livros->end(); ++livro) {
        F << (*livro)->getInfo() << endl;
    }
}


Livro *Biblioteca::atribuirLivro(std::string _id) {
    for (auto livro : *Lista_Livros){
        if(livro->getID() == _id){
            return livro;
        }
    }
}

void Biblioteca::relatorioCategoria(string categoria) {
    string _cat;

    cout << "===[" << categoria << "]===" << endl;

    for (auto livro = Lista_Livros->begin(); livro != Lista_Livros->end(); ++livro) {
        if ((*livro)->getCategoria() == categoria) {
            (*livro)->showLivro();
        }
    }
    return;
}

void Biblioteca::removeLivro(std::string _id) {
    for (auto livro = Lista_Livros->begin(); livro != Lista_Livros->end(); ) {
        if ((*livro)->getID() == _id) {
            // Deleta o objeto antes de removê-lo da lista
            Livro* livroParaDeletar = *livro;  // Salva o ponteiro para o livro
            livro = Lista_Livros->erase(livro);  // Atualiza o iterador após a exclusão
            delete livroParaDeletar;  // Deleta o livro depois de remover da lista
        } else {
            ++livro;  // Avança para o próximo livro se não for encontrado
        }
    }
}


/*PESSOA*/

void Biblioteca::loadPessoasFile(string file){
    fstream F(file, ios::in);

    Pessoa* p;

    string id, nome, dataNascimento, tipoPessoa;

    if (!F.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << file << endl;
    }

    string linha;

    while (getline(F, linha)) {
        stringstream ss(linha);

        // Ler os campos da linha
        getline(ss, id, '\t');
        getline(ss, nome, '\t');
        getline(ss, dataNascimento, '\t');
        getline(ss, tipoPessoa);

        // Criar objeto Pessoa e adicionar à lista
        if (tipoPessoa == "Senior") p = new Senior(id, nome, dataNascimento, tipoPessoa);
        if (tipoPessoa == "Professor")  p = new Professor(id, nome, dataNascimento, tipoPessoa);
        if (tipoPessoa == "Estudante")  p = new Estudante(id, nome, dataNascimento, tipoPessoa);
        if (tipoPessoa == "Leitor Comum")   p = new LeitorComum(id, nome, dataNascimento, tipoPessoa);

        Lista_Pessoas->push_back(p);
    }

    if (Lista_Pessoas->empty()) {
        cout << "Nao ha pessoas para carregar." << endl;
    }

    F.close();
}

void Biblioteca::storePessoas(string file){
    fstream F(file, ios::out);

    if (!F.is_open()) {
        cerr << "Erro ao abrir o ficheiro: " << file << endl;
        return;
    }

    for (auto &i : *Lista_Pessoas) {
        F << i->getID() << "\t"
            << i->getNome() << "\t" << i->getDataNasc()
            << "\t" << i->getTipoPessoa() << endl;
    }

    F.close();
}

void Biblioteca::showPessoas(){
    for (auto &i : *Lista_Pessoas) {
        i->showPessoa();
    }
}

void Biblioteca::pesquisarPessoas(string _id){
    for (auto it = Lista_Pessoas->begin(); it != Lista_Pessoas->end(); it++) {
        if ((*it)->getID() == _id) {
            (*it)->showPessoa();
            return;
        }
    }
    cerr << "ID nao corresponde a nenhuma pessoa desta biblioteca" << endl;
}

void Biblioteca::removerPessoas(string _id){
    for (auto pessoa = Lista_Pessoas->begin(); pessoa != Lista_Pessoas->end(); ++pessoa) {
        if ((*pessoa)->getID() == _id) {
            delete *pessoa;
            Lista_Pessoas->erase(pessoa);
        }
    }
}

Pessoa* Biblioteca::atribuirPessoa(string _id){
    for(auto pessoa = Lista_Pessoas->begin(); pessoa != Lista_Pessoas->end(); ++pessoa){
        if((*pessoa)->getID() == _id){
            return (*pessoa);
        }
    }
}

/*EMPRESTIMOS*/

void Biblioteca::procurarEmprestimos(std::string _id, string tipo) {
    if(tipo == "Atrasados"){
        for(auto emprestimo = Lista_Emprestimos_Passados->begin(); emprestimo != Lista_Emprestimos_Passados->end(); ++emprestimo) {
            if((*emprestimo)->getIDReq() == _id)
                (*emprestimo)->show();
        }
    }

    if(tipo == "Atual"){
        for(auto emprestimo = Lista_Emprestimos_Ativos->begin(); emprestimo != Lista_Emprestimos_Ativos->end(); ++emprestimo) {
            if((*emprestimo)->getIDReq() == _id)
                (*emprestimo)->show();
        }
    }
}

void Biblioteca::listarEmprestimos(string tipo) {
    if(tipo == "Atual"){
        for (auto &i : *Lista_Emprestimos_Ativos) {
            i->show();
        }
    }

    if(tipo == "Reserva"){
        for (auto &i : *Lista_Reservas) {
            i->show();
        }
    }

    if(tipo == "Passado"){
        for (auto &i : *Lista_Emprestimos_Passados) {
            i->show();
        }
    }

    if(tipo == "Multa"){
        Uteis* U = nullptr;

        for (auto &i : *Lista_Multas) {
            int dia = U->calcularDiferencaDias(i->getDataFim(), U->dataAtual());
            int multa = dia * 0.5;
            int desc = calculoDesc(i->getIDReq());
            int valor = multa - (multa * desc / 100);

            i->show();
            cout << "\t" << "Valor Paga: " << valor << endl;
        }
    }
}

void Biblioteca::storeEmprestimos(std::string file, string tipo) {
    fstream F(file, ios::out);

    if(tipo == "Atual"){
        for(auto emprestimos = Lista_Emprestimos_Ativos->begin(); emprestimos != Lista_Emprestimos_Ativos->end(); ++emprestimos)
            F << (*emprestimos)->getInfo() << endl;
    }
    if(tipo == "Atrasados"){
        for(auto emprestimos = Lista_Emprestimos_Passados->begin(); emprestimos != Lista_Emprestimos_Passados->end(); ++emprestimos)
            F << (*emprestimos)->getInfo() << endl;
    }
    if(tipo == "Reserva"){
        for(auto emprestimos = Lista_Reservas->begin(); emprestimos != Lista_Reservas->end(); ++emprestimos)
            F << (*emprestimos)->getInfo() << endl;
    }
    if(tipo == "Multa"){
        for(auto emprestimos = Lista_Multas->begin(); emprestimos != Lista_Multas->end(); ++emprestimos)
            F << (*emprestimos)->getInfo() << endl;
    }

}

void Biblioteca::listarAtrasos() {
    cout << "=====NOTIFICACAO DE ATRASOS====" << endl;

    for (auto atraso = Lista_Emprestimos_Ativos->begin(); atraso != Lista_Emprestimos_Ativos->end(); ++atraso) {
        if((*atraso)->isAtrasado())
            (*atraso)->show();
    }
}

void Biblioteca::loadFileEmprestimos(std::string file, std::string tipo) {
    fstream F (file, ios::in);

    Emprestimos* E = nullptr;

    string idP, idL, dataFim, dataInicio;

    if (!F.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << file << endl;
    }

    if(tipo == "Atual"){

        string linha;

        while (getline(F, linha)) {

            stringstream ss(linha);

            // Ler os campos da linha
            getline(ss, idP, '|');
            getline(ss, idL, '|');
            getline(ss, dataInicio, '|');
            getline(ss, dataFim, '|');
            /*
            cout << "ID LIVRO: " << idP << endl;
            cout << "ID PESSOA: " << idL << endl;
            cout << "DATA INCIO: " << dataInicio << endl;
            cout << "DATA FIM: " << dataFim << endl;
            */
            // Criar objeto Emprestimo e adicionar à lista
            E = new Emprestimos(idP, idL, dataInicio, dataFim);
            Lista_Emprestimos_Ativos->push_back(E);
        }

        if (Lista_Emprestimos_Ativos->empty()) {
            cout << "Nao ha emprestimos atuais para carregar." << endl;
        }
    }

    if(tipo == "Passado"){

        string linha;

        while (getline(F, linha)) {

            stringstream ss(linha);

            // Ler os campos da linha
            getline(ss, idP, '|');
            getline(ss, idL, '|');
            getline(ss, dataInicio, '|');
            getline(ss, dataFim, '|');
            /*
            cout << "ID LIVRO: " << idP << endl;
            cout << "ID PESSOA: " << idL << endl;
            cout << "DATA INCIO: " << dataInicio << endl;
            cout << "DATA FIM: " << dataFim << endl;
            */
            // Criar objeto Emprestimo e adicionar à lista
            E = new Emprestimos(idP, idL, dataInicio, dataFim);
            Lista_Emprestimos_Passados->push_back(E);
        }
    }

    if(tipo == "Reserva"){
        Uteis* U = nullptr;

        string linha;

        while (getline(F, linha)) {

            stringstream ss(linha);

            // Ler os campos da linha
            getline(ss, idP, '|');
            getline(ss, idL, '|');
            getline(ss, dataInicio, '|');
            getline(ss, dataFim, '|');
            /*
            cout << "ID LIVRO: " << idP << endl;
            cout << "ID PESSOA: " << idL << endl;
            cout << "DATA INCIO: " << dataInicio << endl;
            cout << "DATA FIM: " << dataFim << endl;
            */
            if(U->calcularDiferencaDias(U->dataAtual(), dataFim) > 0 ){
                // Criar objeto Emprestimo e adicionar à lista
                E = new Emprestimos(idP, idL, dataInicio, dataFim);
                Lista_Reservas->push_back(E);
            }
        }

        if (Lista_Reservas->empty()) {
            cout << "Nao ha reservas para carregar." << endl;
        }
    }

    F.close();
}

string Biblioteca::diasRequesicao(string _idP, string _idL){
    string diasRequesitantes;

    Pessoa* P = atribuirPessoa(_idP);
    Livro* L = atribuirLivro(_idL);

    string cat, tipo;

    if((P->getTipoPessoa() == "Estudante") && (L->getCategoria() == "Educativo")){
        diasRequesitantes = "45";
    }
    else if((P->getTipoPessoa() == "Professor") && (L->getCategoria() == "Cientifico")){
        diasRequesitantes = "45";
    }
    else if((P->getTipoPessoa() == "Senior") && (L->getCategoria() == "Jornal")){
        diasRequesitantes = "30";
    }
    else{
        diasRequesitantes = "15";
    }
    return diasRequesitantes;
}

string Biblioteca::dataEntrega(string idP, string idL){
    Uteis* U = nullptr;

    Emprestimos* E = atribuirEmprestimo(idP);

    string DataEntrega;
    string diaA, mesA, anoA;

    int contador = 0;

    string dataAtual = U->dataAtual();

    regex del("-");

    sregex_token_iterator i(dataAtual.begin(), dataAtual.end(), del, -1);

    sregex_token_iterator end;

    while (i != end){
        if (contador == 0) {
            diaA = *i;
        } else if (contador == 1) {
            mesA = *i;
        } else if (contador == 2) {
            anoA = *i;
        }
        ++i;
        ++contador;
    }

    int dia = stoi(diaA);
    int mes = stoi(mesA);
    int ano = stoi(anoA);

    string diasRequisicao = diasRequesicao(idP, idL);

    dia += stoi(diasRequisicao);

    // Verificar se o dia ultrapassa o número de dias do mês e ajustar o ano caso necessário
    while (dia > U->diasNoMes(mes, ano)) {
        dia -= U->diasNoMes(mes, ano);  // Subtrai o número de dias do mês atual
        mes++;  // Avança para o próximo mês
        if (mes > 12) {  // Se o mês ultrapassar 12, avança para o próximo ano
            mes = 1;
            ano++;
        }
    }

    string mesFinal, diaFinal;

    if(dia < 10) diaFinal = "0" + to_string(dia);
    if(mes < 10) mesFinal = "0" + to_string(mes);

    DataEntrega = diaFinal + "-" + mesFinal + "-" + to_string(ano);

    E->atribuirDataFim(DataEntrega);

    return DataEntrega;
}

bool Biblioteca::verSeLivroEstaRequesitado(string idL){
    for(auto livro = Lista_Emprestimos_Ativos->begin(); livro != Lista_Emprestimos_Ativos->end(); ++livro){
        if((*livro)->getIDLivro() == idL){
            return true;
        }
    }
    return false;
}

bool Biblioteca::verSeLivroEstaReservado(std::string idL) {
    for(auto livro = Lista_Reservas->begin(); livro != Lista_Reservas->end(); ++livro){
        if((*livro)->getIDLivro() == idL){
            return true;
        }
    }
    return false;
}

Emprestimos *Biblioteca::atribuirEmprestimo(string _id) {
    for(auto empres = Lista_Emprestimos_Ativos->begin(); empres != Lista_Emprestimos_Ativos->end(); ++empres){
        if((*empres)->getIDReq() == _id){
            return (*empres);
        }
    }
}

float Biblioteca::calculoDesc(string idP) {
    Pessoa* P = atribuirPessoa(idP);
    string tipo = P->getTipoPessoa();
    if(tipo == "Estudante"){
        float desc = 0.10;
        return desc;
    }
    if(tipo == "Professor"){
        float desc = 0.06;
        return desc;
    }
    if(tipo == "Senior"){
        float desc = 0.075;
        return desc;
    }
    if(tipo == "Leitor Comum"){
        float desc = 0.0;
        return desc;
    }
}

void Biblioteca::devolverEmprestimo() {

    string idPessoa;
    string pago;
    cout << "Digite o ID da pessoa: ";
    cin >> idPessoa;
    Emprestimos* E = atribuirEmprestimo(idPessoa);
    Uteis* U = nullptr;

    if(E->isAtrasado()){
        int dia = U->calcularDiferencaDias(E->getDataFim(), U->dataAtual());
        if (dia < 0) dia *= (-1);

        int multa = dia * 0.5;
        int desc = calculoDesc(idPessoa);

        int valorPagar = multa - (multa * desc / 100);
        cout << "Valor a pagar: " << valorPagar << endl;
        U->delay(2);
        while(pago != "Pago"){
            U->pausarTela();
            pago = "Pago";
        }
    }

    //Procura o emprestimo dento dos ativos
    for (auto it = Lista_Emprestimos_Ativos->begin(); it != Lista_Emprestimos_Ativos->end(); ++it) {

        if (*it == E) {  //VERIFICA SE É O MESMO EMPRESTIMO

            Lista_Emprestimos_Ativos->erase(it);
            Lista_Emprestimos_Passados->push_back(E);

            cout << "Emprestimo devolvido com sucesso." << endl;

            break;
        }
    }
}

string Biblioteca::calcularDataFinalReserva(string dataInicio, int diasReserva) {
    Uteis* U = nullptr;

    stringstream ss(dataInicio);

    string dia, mes, ano;

    getline(ss, dia, '-');
    getline(ss, mes, '-');
    getline(ss, ano, '-');

    // Converte para inteiros para fazer cálculos
    int diaInt = stoi(dia);
    int mesInt = stoi(mes);
    int anoInt = stoi(ano);

    diaInt += diasReserva;

    while (diaInt > U->diasNoMes(mesInt, anoInt)) {
        diaInt -= U->diasNoMes(mesInt, anoInt);
        mesInt++;
        if (mesInt > 12) {
            mesInt = 1;
            anoInt++;
        }
    }

    if(diaInt < 10)
        dia = "0" + to_string(diaInt);

    if(mesInt < 10)
        mes = "0" + to_string(mesInt);

    ano = to_string(anoInt);

    string datEntrega = dia + "-" + mes + "-" + ano;

    return datEntrega;
}

void Biblioteca::reservarLivro() {

    Uteis *U = nullptr;

    string idPessoa, idLivro;
    cout << "ID da pessoa: ";
    cin >> idPessoa;
    cout << "ID do livro: ";
    cin >> idLivro;
    /*
    cout << "----------------------[INFO]------------------------" << endl;
    pesquisarLivro(idLivro);
    cout << endl;
    pesquisarPessoas(idPessoa);
    cout << "----------------------------------------------------" << endl;
    */
    if (!verSeLivroEstaRequesitado(idLivro)) {
        if (!verSeLivroEstaReservado(idLivro)) {
            string dataInicio = U->dataAtual();
            string dataFimReserva = calcularDataFinalReserva(dataInicio, 5);

            Emprestimos *emprestimo = new Emprestimos(idPessoa, idLivro, dataInicio, dataFimReserva);
            Lista_Reservas->push_back(emprestimo);

            cout << "Livro reservado com sucesso ate " << dataFimReserva << endl;
        }
    }
}

void Biblioteca::cancelarReservaLivro(){
    string idPessoa;
    cout << "Digite o ID da pessoa: ";
    cin >> idPessoa;

    //Procura a reserva dentro da lista reserva
    for (auto it = Lista_Reservas->begin(); it != Lista_Reservas->end(); ++it) {
        if((*it)->getIDReq() == idPessoa)
            Lista_Reservas->erase(it);
    }
}

void Biblioteca::statusEmprestimo(){
    cout << "=============================[EMPRESTIMOS ATIVOS]=============================" << endl;
    listarEmprestimos("Atual");
    cout << "============================[EMPRESTIMOS PASSADOS]============================" << endl;
    listarEmprestimos("Passado");
}

void Biblioteca::statusResevervas(){
    cout << "==================================[RESERVAS]==================================" << endl;
    listarEmprestimos("Reserva");
}

/*MENUS*/

void Biblioteca::menuBiblioteca() {
    int op = 0;

    do {
        cout << "---------------------------------------" << endl;
        cout << "|          " << Nome << "              |" << endl;
        cout << "---------------------------------------" << endl;
        cout << "|        MENU DE BIBLIOTECA            |" << endl;
        cout << "---------------------------------------" << endl;
        cout << "|  1. GESTAO DE LIVROS                 |" << endl;
        cout << "|  2. GESTAO DE LEITORES               |" << endl;
        cout << "|  3. GESTAO DE EMPRESTIMOS            |" << endl;
        cout << "|  0. SAIR                             |" << endl;
        cout << "---------------------------------------" << endl;
        cout << "Escolha uma opcao: ";
        cin >> op;

        switch (op) {
            case 1: {
                menuLivros(); //FEITO TUDO
                break;
            }
            case 2: {
                menuLeitores(); //FEITO TUDO
                break;
            }
            case 3: {
                menuRequisicoes(); //FEITO TUDO
                break;
            }
            case 0: {
                storeEmprestimos("Emprestimos_Ativos.txt", "Atual");
                storeEmprestimos("Emprestimos_Historicos.txt", "Passado");
                storePessoas("Leitores.txt");
                storeLivros("Livros.txt");
                storeEmprestimos("Multas.txt", "Multas");
                storeEmprestimos("Reservas.txt", "Reserva");
                break;
            }
            default: {
                cout << "Opcao invalida! Por favor, escolha uma opcao valida." << endl;
            }
        }
    } while (op != 0);
    cout << "Programa finalizado corretamente!" << endl;
}

void Biblioteca::menuLivros() {
    int op;
    Uteis U;
    string opc = "0";

    do {
        cout << "----------------------------------------" << endl;
        cout << "|            MENU DE LIVROS            |" << endl;
        cout << "----------------------------------------" << endl;
        cout << "|  1.REGISTRAR NOVO LIVRO              |" << endl; /*FUNCIONAL*/
        cout << "|  2.EDITAR INFORMACOES DE LIVRO       |" << endl; /*FUNCIONAL*/
        cout << "|  3.LISTAR LIVROS                     |" << endl; /*FUNCIONAL*/
        cout << "|  4.PESQUISAR LIVRO                   |" << endl; /*FUNCIONAL*/
        cout << "|  5.RELATORIO DE LIVROS POR CATEGORIA |" << endl; /*FUNCIONAL*/
        cout << "|  6.EXCLUIR LIVRO                     |" << endl; /*FUNCIONAL*/
        cout << "|  0.VOLTAR A MENU PRINCIPAL           |" << endl; /*FUNCIONAL*/
        cout << "----------------------------------------" << endl;
        cout << "Escolha uma opcao: ";
        cin >> op;

        switch (op) {
            case 1: {
                cout << "Da lista abaixo que tipo de livro deseja adicionar:" << endl;
                cout << "\t[1] Jornal" << endl;
                cout << "\t[2] Revista" << endl;
                cout << "\t[3] Livro Cientifico" << endl;
                cout << "\t[4] Livro Educativo" << endl;
                cout << "\t[5] Livro Ficcao" << endl;
                cin >> opc;

                if (opc == "1") {
                    cout << "Entrou no Jornal" << endl;
                    string _id, _titulo, _autor, _anoPub, formato;
                    cout << "======[Preencher Info Livro]======" << endl;
                    cout << "ID [dddd-dddd]: ";
                    cin.ignore();
                    getline(cin, _id);
                    cout << "Titulo: ";
                    getline(cin, _titulo);
                    cout << "Autor: ";
                    getline(cin, _autor);
                    cout << "Ano de Publicacao: ";
                    cin >> _anoPub;
                    cout << "Formato: ";
                    cin.ignore();
                    getline(cin, formato);

                    Livro* L = new Jornal(_id, _titulo, _autor, _anoPub, formato, "Jornal");

                    Lista_Livros->push_front(L);
                }
                else if (opc == "2") {
                    cout << "Entrou na Revista" << endl;
                    string _id, _titulo, _autor, _anoPub, _edi;
                    cout << "======[Preencher Info Livro]======" << endl;
                    cout << "ID [dddd-dddd]:";
                    getline(cin, _id);
                    cin.ignore();
                    cout << "Titulo:";
                    getline(cin, _titulo);
                    cout << "Autor:";
                    getline(cin, _autor);
                    cout << "Ano de Publicacao:";
                    cin >> _anoPub;
                    cin.ignore();
                    cout << "Edicao:";
                    cin.ignore();
                    getline(cin, _edi);

                    Livro* L = new Revista(_id, _titulo, _autor, _anoPub, _edi, "Revista");

                    Lista_Livros->push_front(L);
                }
                else if (opc == "3") {
                    cout << "Entrou no Livro Cientifico" << endl;
                    string _id, _titulo, _autor, _anoPub, edi;
                    cout << "======[Preencher Info Livro]======" << endl;
                    cout << "ID [ddddddddd]:";
                    cin.ignore();
                    getline(cin, _id);
                    cout << "Titulo:";
                    getline(cin, _titulo);
                    cout << "Autor:";
                    getline(cin, _autor);
                    cout << "Ano de Publicacao:";
                    cin >> _anoPub;
                    cout << "Ano de Edicao:";
                    cin.ignore();
                    getline(cin, edi);

                    Livro* L = new LivroCientico(_id, _titulo, _autor, _anoPub, edi, "Cientifico");

                    Lista_Livros->push_front(L);
                }
                else if (opc == "4") {
                    cout << "Entrou no Livro Educativo" << endl;
                    string _id, _titulo, _autor, _anoPub, grauEsco;
                    cout << "======[Preencher Info Livro]======" << endl;
                    cout << "ID [ddddddddd]:";
                    cin.ignore();
                    getline(cin, _id);
                    cout << "Titulo:";
                    getline(cin, _titulo);
                    cout << "Autor:";
                    getline(cin, _autor);
                    cout << "Ano de Publicacao:";
                    cin >> _anoPub;
                    cout << "Grau de Escolaridade:";
                    cin.ignore();
                    getline(cin, grauEsco);

                    Livro* L = new LivroEducativo(_id, _titulo, _autor, _anoPub, grauEsco, "Educativo");

                    Lista_Livros->push_front(L);
                }
                else if (opc == "5") {
                    cout << "Entrou no Livro Ficcao" << endl;
                    string _id, _titulo, _autor, _anoPub, edi;
                    cout << "======[Preencher Info Livro]======" << endl;
                    cout << "ID [ddddddddd]:";
                    cin.ignore();
                    getline(cin, _id);
                    cout << "Titulo:";
                    getline(cin, _titulo);
                    cout << "Autor:";
                    getline(cin, _autor);
                    cout << "Ano de Publicacao:";
                    cin >> _anoPub;
                    cout << "Edicao:";
                    cin.ignore();
                    getline(cin, edi);

                    Livro* L = new LivroFiccao(_id, _titulo, _autor, _anoPub, edi, "Ficcao");

                    Lista_Livros->push_front(L);
                }
                else {
                    cout << "Opcao Invalida" << endl;
                    menuLivros();
                }
                break;
            }
            case 2: {
                string _id;
                cout << "ID do livro a editar: ";
                cin >> _id;

                Livro* L = atribuirLivro(_id);
                L->escolherInfoLivro();
                L->showLivro();
                break;
            }
            case 3: {
                showLivros();
                break;
            }
            case 4: {
                string _id;

                cout << "Qual o ID do livro que pretende procurar: " << endl;
                cin >> _id;
                Livro* L = atribuirLivro(_id);
                L->showLivro();

                break;
            }
            case 5: {
                string opc;

                cout << "Da lista abaixo que tipo de livro deseja adicionar:" << endl;
                cout << "\t[1] Jornal" << endl;
                cout << "\t[2] Revista" << endl;
                cout << "\t[3] Livro Cientifico" << endl;
                cout << "\t[4] Livro Educativo" << endl;
                cout << "\t[5] Livro Ficcao" << endl;
                cin >> opc;

                if (opc == "1") {
                    relatorioCategoria("Jornal");
                }
                else if (opc == "2") {
                    relatorioCategoria("Revista");
                }
                else if (opc == "3") {
                    relatorioCategoria("Cientifico");
                }
                else if (opc == "4") {
                    relatorioCategoria("Educativo");
                }
                else if (opc == "5") {
                    relatorioCategoria("Ficcao");
                }
                else {
                    cout << "OPCAO INVALIDA ..." << endl;
                    U.pausarTela();
                    menuLivros();
                }
                break;
            }
            case 6: {
                string _id;

                cout << "Qual o ID do livro que deseja remover: " << endl;
                cin >> _id;
                removeLivro(_id);
                showLivros();
                break;
            }
            case 0: {
                menuBiblioteca();
                return;
            }
            default: {
                cout << "Opcao invalida! Por favor, escolha uma opcao valida." << endl;
            }
        }
    } while (op != 0);
}

void Biblioteca::menuLeitores() {
    Uteis *U;
    Pessoa *P;

    int op;

    do {
        cout << "----------------------------------------" << endl;
        cout << "|            MENU DE LEITORES          |" << endl;
        cout << "----------------------------------------" << endl;
        cout << "|  1. REGISTRAR NOVO LEITOR           |" << endl; /*FUNCIONAL*/
        cout << "|  2. EDITAR INFORMACOES DE LEITOR    |" << endl; /*FUNCIONAL*/
        cout << "|  3. LISTAR LEITORES                 |" << endl; /*FUNCIONAL*/
        cout << "|  4. PESQUISAR LEITOR                |" << endl; /*FUNCIONAL*/
        cout << "|  5. RELATORIO DE MULTAS PENDENTES   |" << endl; /*FUNCIONAL*/
        cout << "|  6. EXCLUIR LEITOR                  |" << endl; /*FUNCIONAL*/
        cout << "|  0. VOLTAR A MENU PRINCIPAL         |" << endl;
        cout << "----------------------------------------" << endl;
        cout << "Escolha uma opcao: ";
        cin >> op;

        switch(op) {
            case 1: {
                string res;
                cout << "Da lista abaixo que tipo de pessoa deseja adicionar:" << endl;
                cout << "\t[1] Leitor Comum" << endl;
                cout << "\t[2] Estudante" << endl;
                cout << "\t[3] Professor" << endl;
                cout << "\t[4] Senior" << endl;
                cin >> res;

                // Criação do objeto Pessoa com base na opção escolhida
                if (res == "1") {
                    string _id, _nome, _dataNasc;
                    cout << "======[Preencher Info Pessoa]======" << endl;
                    cout << "ID: ";
                    cin >> _id;
                    cout << "Nome: ";
                    cin.ignore();  // Ignora o '\n' pendente no buffer de entrada
                    getline(cin, _nome);  // Lê o nome completo
                    cout << "Data de Nascimento: ";
                    cin >> _dataNasc;

                    P = new LeitorComum(_id, _nome, _dataNasc, "Leitor Comum");
                } else if (res == "2") {
                    string _id, _nome, _dataNasc;
                    cout << "======[Preencher Info Pessoa]======" << endl;
                    cout << "ID: ";
                    cin >> _id;
                    cout << "Nome: ";
                    cin.ignore();
                    getline(cin, _nome);
                    cout << "Data de Nascimento: ";
                    cin >> _dataNasc;

                    P = new Estudante(_id, _nome, _dataNasc, "Estudante");
                } else if (res == "3") {
                    string _id, _nome, _dataNasc;
                    cout << "======[Preencher Info Pessoa]======" << endl;
                    cout << "ID: ";
                    cin >> _id;
                    cout << "Nome: ";
                    cin.ignore();
                    getline(cin, _nome);
                    cout << "Data de Nascimento: ";
                    cin >> _dataNasc;

                    P = new Professor(_id, _nome, _dataNasc, "Professor");
                } else if (res == "4") {
                    string _id, _nome, _dataNasc;
                    cout << "======[Preencher Info Pessoa]======" << endl;
                    cout << "ID: ";
                    cin >> _id;
                    cout << "Nome: ";
                    cin.ignore();
                    getline(cin, _nome);
                    cout << "Data de Nascimento: ";
                    cin >> _dataNasc;

                    P = new Senior(_id, _nome, _dataNasc, "Senior");
                } else {
                    cout << "Opção inválida!" << endl;
                    menuLeitores();  // Volta para o menu
                }

                // Adicionando a pessoa à lista
                Lista_Pessoas->push_back(P);
                break;
            }
            case 2: {
                U->pausarTela();
                string _id;
                cout << "ID da pessoa a editar: ";
                cin >> _id;
                Pessoa* P = atribuirPessoa(_id);
                P->escolherInfoPessoa();
                break;
            }
            case 3: {
                U->pausarTela();
                showPessoas();
                break;
            }
            case 4: {
                U->pausarTela();

                string _id;

                cout << "Qual o ID da pessoa que procura: \t";
                cin >> _id;
                pesquisarPessoas(_id);

                break;
            }
            case 5: {
                U->pausarTela();
                listarEmprestimos("Multa");
                break;
            }
            case 6: {
                U->pausarTela();
                string _id;
                cout << "ID da pessoa que quer remover: \t";
                cin >> _id;
                removerPessoas(_id);
                break;
            }
            case 0: {
                menuBiblioteca();
            }
            default: {
                cout << "Opção inválida! Por favor, escolha uma opção válida." << endl;
                U->pausarTela();
            }
        }
    } while (op != 0);
}

void Biblioteca::menuRequisicoes() {
    Uteis* U = nullptr;

    int op;

    do {
        cout << "----------------------------------------" << endl;
        cout << "|            MENU DE REQUISICOES       |" << endl;
        cout << "----------------------------------------" << endl;
        cout << "|  1. REALIZAR NOVO EMPRESTIMO         |" << endl; /*FUNCIONAL*/
        cout << "|  2. DEVOLUCAO DE LIVRO               |" << endl; /*FUNCIONAL*/
        cout << "|  3. EXTENDER PRAZO DE EMPRESTIMO     |" << endl; /*FUNCIONAL*/
        cout << "|  4. RESERVAR LIVRO                   |" << endl; /*FUNCIONAL*/
        cout << "|  5. CANCELAR RESERVA DE LIVRO        |" << endl; /*FUNCIONAL*/
        cout << "|  6. CONSULTAR STATUS DE EMPRESTIMOS  |" << endl; /*FUNCIONAL*/
        cout << "|  7. CONSULTAR STATUS DE RESERVAS     |" << endl; /*FUNCIONAL*/
        cout << "|  8. RELATORIO DE EMPRESTIMOS         |" << endl; /*FUNCIONAL*/
        cout << "|  9. NOTIFICACOES DE ATRASOS          |" << endl; /*FUNCIONAL*/
        cout << "|  0. VOLTAR AO MENU PRINCIPAL         |" << endl; /*FUNCIONAL*/
        cout << "----------------------------------------" << endl;
        cout << "Escolha uma opcao: ";
        cin >> op;

        switch(op) {
            case 1: {
                string idP, idL, datainicio, datafim;
                cout << "Qual o seu ID de utilizador: ";
                cin >> idP;
                cout << "Qual o ID do livro: ";
                cin >> idL;
                datainicio = U->dataAtual();
                datafim = dataEntrega(idP, idL);
                if(!verSeLivroEstaRequesitado(idL)){ // Se o livro nao estiver requisitado
                    Emprestimos* E = new Emprestimos(idP, idL, datainicio, datafim);
                    Lista_Emprestimos_Ativos->push_back(E);
                    cout << "Emprestimo registrado com sucesso!" << endl;
                }else{
                    cerr << "Livro ja esta requisitado" << endl;
                    cin.ignore();
                }
                //listarEmprestimos("Atual");
                break;
            }
            case 2: { // Devolução de livro
                devolverEmprestimo();
                break;
            }
            case 3: {
                string idP, idL;
                cout << "Qual o seu ID de utilizador: ";
                cin >> idP;
                cout << "Qual o ID do livro: ";
                cin >> idL;
                string dataE = dataEntrega(idP, idL);
                cout << "A nova data de entrega e: " << dataE << endl;
                //listarEmprestimos("Atual");
                break;
            }
            case 4: {
                reservarLivro();
                //listarEmprestimos("Reserva");
                break;
            }
            case 5: {
                cancelarReservaLivro();
                //listarEmprestimos("Reserva");
                break;
            }
            case 6: {
                statusEmprestimo();
                break;
            }
            case 7: {
                statusResevervas();
                break;
            }
            case 8: {
                menuRelatorio();
                break;
            }
            case 9: {
                listarAtrasos();
                break;
            }
            case 0: {
                menuBiblioteca();
            }
            default: {
                cout << "Opcao invalida! Tente novamente." << endl;
            }
        }
    } while(op != 0);
}

void Biblioteca::menuRelatorio() {
    int opc;
    Uteis* U = nullptr;

    do {
        cout << "----------------------------------------" << endl;
        cout << "|            MENU DE RELATORIO         |" << endl;
        cout << "----------------------------------------" << endl;
        cout << "|  1. EMPRESTIMOS ATIVOS               |" << endl;
        cout << "|  2. HISTORICO DE EMPRESTIMOS         |" << endl;
        cout << "|  0. VOLTAR A REQUESICAO              |" << endl;
        cout << "----------------------------------------" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opc;

        switch(opc) {
            case 1: {
                listarEmprestimos("Atual");
                break;
            }
            case 2: {
                listarEmprestimos("Passado");
                break;
            }
            case 0: {
                menuRequisicoes();
                return;
            }
            default: {
                cout << "Opcao invalida! Por favor, escolha uma opcao válida." << endl;
                U->pausarTela();
            }
        }
    } while(opc != 0);
}
