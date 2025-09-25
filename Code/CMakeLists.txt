cmake_minimum_required(VERSION 3.27)
project(Projeto_POO_EXP)

set(CMAKE_CXX_STANDARD 17)

add_executable(Projeto_POO_EXP main.cpp
        Biblioteca.cpp
        Biblioteca.h
        LivroFiccao.h
        LivroCientifico.h
        LivroEducativo.h
        Jornal.h
        Revista.h
        Uteis.h
        Pessoa.h
        Estudante.h
        LeitorComum.h
        Senior.h
        Professor.h
        Emprestimos.h
        Emprestimos.cpp
        Estudante.cpp
        Jornal.cpp
        LeitorComum.cpp
        Livro.cpp
        LivroCientifico.cpp
        LivroEducativo.cpp
        LivroFiccao.cpp
        Pessoa.cpp
        Professor.cpp
        Revista.cpp
        Senior.cpp
        Uteis.cpp
)