#ifndef STUDENTGENERATOR_H
#define STUDENTGENERATOR_H

#include "student.h"
#include "student_factory.h"
#include <iostream>

using namespace std;

class StudentGenerator {
    char   sName[60];
    double score[4];
    int    absence;
public:
    Student *getStudentGenerator(StudentFactory *factory);
};

/*
    Cadastra novo objeto Student
*/
Student* StudentGenerator::getStudentGenerator(StudentFactory *factory) {
    cout << endl << "- CADASTRO DE ALUNO -" << endl;
    cout << "Nome:";
    cin.getline(this->sName, sizeof(this->sName));
    cout << "Informar notas do aluno." << endl;
    cout << "Nota 1:";          cin >> this->score[0];
    cout << "Nota 2:";          cin >> this->score[1];
    cout << "Nota 3:";          cin >> this->score[2];
    cout << "Nota 4:";          cin >> this->score[3];
    cout << "Nr. de faltas:";   cin >> this->absence;

    int iCounter = factory->getStudentCounter();

    Student *student = new Student(iCounter++, this->sName, this->score, this->absence);
    return student;
}

#endif //STUDENTGENERATOR_H
