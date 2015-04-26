#include <stdlib.h>
#include "comparators.h"
#include "student.h"
#include <iostream>

using namespace std;

Comparator::Comparator() {
    // Cria objeto com indice default. (1)
    this->index = 0;
}

/*
    Define indice a ser utilizado
*/
void Comparator::setIndice() {
    // Listar indices disponíveis
    cout << "Lista de indices" << endl;
    cout << "[1] Name; Matricula" << endl;
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
int Comparator::getIndice() { return this->index; }

/*
    Retorna descricao do indice
*/
std::string Comparator::getDescricaoIndice() {
    std::string sRetorno;

    if (this->index == 0) sRetorno = "Matricula";
    else if (this->index == 1) sRetorno = "Name, Matricula";
    else if (this->index == 2) sRetorno = "Situacao, Name, Matricula";
    else if (this->index == 3) sRetorno = "Maior Media, Name, Matricula";
    else if (this->index == 4) sRetorno = "Menor Media, Name, Matricula";

    return sRetorno;
}

/*
    Compara os valores dos indices entre dois Estudantes.
*/
int Comparator::getComparaIndice(Student *s1, Student *s2) {
    // Matricula;
    if (this->index == 0) {
        if (s1->getEnrollNumber() < s2->getEnrollNumber())
            return -1;
        else
            return 1;
    }

    // Name; Matricula;


    // Situacao; Name; Matricula
    if (this->index == 2) {
        if (s1->getStatus() < s2->getStatus())
            return -1;
        else if (s1->getStatus() == s2->getStatus()) {
            if (s1->getName() < s2->getName())
                return -1;
            else if (s1->getName() == s2->getName()) {
                if (s1->getEnrollNumber() < s2->getEnrollNumber())
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

    // Maior Media, Name, Matricula;
    if (this->index == 3) {
        if (s1->getAverage() > s2->getAverage())
            return -1;
        else if (s1->getAverage() == s2->getAverage()) {
            if (s1->getName() < s2->getName())
                return -1;
            else if (s1->getName() == s2->getName()) {
                if (s1->getEnrollNumber() < s2->getEnrollNumber())
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
    // Menor Average, Name, EnrollNumber
    if (this->index == 4) {
        if (s1->getAverage() < s2->getAverage())
            return -1;
        else if (s1->getAverage() == s2->getAverage()) {
        if (s1->getName() < s2->getName())
                return -1;
            else if (s1->getName() == s2->getName()) {
                if (s1->getEnrollNumber() < s2->getEnrollNumber())
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