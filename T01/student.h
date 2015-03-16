#include <cstring>
#include <string>
#include "student_status.h"

#ifndef STUDENT_H
#define STUDENT_H


class Student {
private:
public:
    Student(int _enrollNumber, std::string _name, double *_score, int _absence);
    Student(){};

private:
/// Número da matrícula
    int enrollNumber;
    //Nome
    char name[60];
    ///Nota das provas
    double score[4];
    //Média
    double average;
    ///Faltas
    int absence;
    ///Situação
    StudentStatus status;

public:
    std::string toString();

};



#endif //STUDENT_H
