#include <stdlib.h>
#include "student_generator.h"
#include "student.h"
#include <iostream>

using namespace std;

/*
    Cadastra novo objeto Student
*/
Student StudentGenerator::getStudentGenerator(StudentFactory *factory) {
    cout << endl << "- CADASTRO DE ALUNO -"           << endl;
    cout << "Nome:";
    cin.getline(this->sName, sizeof(this->sName));
    cout << "Informar notas do aluno."                << endl;
    cout << "Nota 1:";          cin >> this->score[0];
    cout << "Nota 2:";          cin >> this->score[1];
    cout << "Nota 3:";          cin >> this->score[2];
    cout << "Nota 4:";          cin >> this->score[3];
    cout << "Nota 5:";          cin >> this->score[4];
    cout << "Nr. de faltas:";   cin >> this->absence;

    int iCounter = factory->getStudentCounter();

    Student *student = new Student(iCounter++, this->sName, this->score, this->absence);
    return student;
}
