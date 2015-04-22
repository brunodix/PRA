#include <stdlib.h>
#include "indexador.h"
#include "student.h"
#include <iostream>

using namespace std;

Indexador::Indexador() {
    // Cria objeto com indice default. (1)
    this->index = 0;
}

/*
    Define indice a ser utilizado
*/
void Indexador::setIndice() {
    // Listar indices disponíveis
    cout << "Lista de indices" << endl;
    cout << "[1] Nome; Matricula" << endl;
    cout << "[2] Situacao; Nome; Matricula" << endl;
    cout << "[3] Maior Media; Nome; Matricula" << endl;
    cout << "[4] Menor Media; Nome; Matricula" << endl;

    // Solicitar escolha de indices
    cout << "Informe o indice desejado:" << endl;
    cin >> this->index;
    if (this->index < 0 || this->index > 4) this->index = 0;
}

/*
    Retorna numero do indice
*/
int Indexador::getIndice() { return this->index; }

/*
    Retorna descricao do indice
*/
std::string Indexador::getDescricaoIndice() {
    std::string sRetorno;

    if (this->index == 0) sRetorno = "Matricula";
    else if (this->index == 1) sRetorno = "Nome, Matricula";
    else if (this->index == 2) sRetorno = "Situacao, Nome, Matricula";
    else if (this->index == 3) sRetorno = "Maior Media, Nome, Matricula";
    else if (this->index == 4) sRetorno = "Menor Media, Nome, Matricula";

    return sRetorno;
}

/*
    Compara os valores dos indices entre dois Estudantes.
*/
int Indexador::getComparaIndice(Student *s1, Student *s2) {
    // Matricula;
    if (this->index == 0) {
        if (s1->getMatricula() < s2->getMatricula())
            return -1;
        else
            return 1;
    }

    // Nome; Matricula;


    // Situacao; Nome; Matricula
    if (this->index == 2) {
        if (s1->getSituacao() < s2->getSituacao())
            return -1;
        else if (s1->getSituacao() == s2->getSituacao()) {
            if (s1->getNome() < s2->getNome())
                return -1;
            else if (s1->getNome() == s2->getNome()) {
                if (s1->getMatricula() < s2->getMatricula())
                    return -1;
                else
                    return 1;
            }
            else
                return 1;
        }
        else
            return 1;
    }

    // Maior Media, Nome, Matricula;
    if (this->index == 3) {
        if (s1->getMedia() > s2->getMedia())
            return -1;
        else if (s1->getMedia() == s2->getMedia()) {
            if (s1->getNome() < s2->getNome())
                return -1;
            else if (s1->getNome() == s2->getNome()) {
                if (s1->getMatricula() < s2->getMatricula())
                    return -1;
                else
                    return 1;
            }
            else
                return 1;
        }
        else
            return 1;
    }
    // Menor Media, Nome, Matricula
    if (this->index == 4) {
        if (s1->getMedia() < s2->getMedia())
            return -1;
        else if (s1->getMedia() == s2->getMedia()) {
            if (s1->getNome() < s2->getNome())
                return -1;
            else if (s1->getNome() == s2->getNome()) {
                if (s1->getMatricula() < s2->getMatricula())
                    return -1;
                else
                    return 1;
            }
            else return 1;
        }
        else return 1;
    }
    return -1;
}