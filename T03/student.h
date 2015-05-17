#include <cstring>
#include <string>
#include "student_status.h"

#ifndef STUDENT_H
#define STUDENT_H


/**
 * Classe que representa uma matricula de um usuário, é a estrutura armazenada no arquivo.
 */
class Student {
private:
public:
    /**
     * Construtor que recebe os principais parâmetros.
     */
    Student(int _enrollNumber, std::string _name, double *_score, int _absence);
    Student(){};

private:
    /// Número da matrícula
    long enrollNumber;
    /// Nome
    char name[60];
    /// Nota das provas
    double score[4];
    /// Média
    double average;
    /// Faltas
    int absence;
    /// Situação
    StudentStatus status;

public:
    std::string   toString();     /// Retorna um representação em std::string do objeto.
    long          getEnrollNumber(); /// Retorna a Matrícula
    std::string   getName();      /// Retorna o Nome
    double        getAverage();     /// Retorna a Média
    StudentStatus getStatus();  /// Retorna a Situação
};

#endif //STUDENT_H
