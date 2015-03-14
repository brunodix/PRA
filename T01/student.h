#include <cstring>

#ifndef STUDENT_H
#define STUDENT_H



enum StudentStatus { APPROVED, EXAM, REPROVED };


class Student {
private:
public:
    Student(int _enrollNumber, char *_name, double _score[4], int _absence, StudentStatus _status) {
        enrollNumber = _enrollNumber;
        absence = _absence;
        strcpy(name, _name);
        score = _score;
        status = _status;
    }

private:
/// Número da matrícula
    int enrollNumber;
    //Nome
    char name[60];
    ///Nota das provas
    double score[4];
    ///Faltas
    int absence;
    ///Situação
    StudentStatus status;

public:

};


#endif //STUDENT_H
