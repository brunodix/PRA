//
// Created by bruno on 14/03/15.
//

#ifndef STUDENTFACTORY_H
#define STUDENTFACTORY_H

#include "student.h"
#include "pseudo_name_generator.h"
#include "pseudo_number_generator.h"

class StudentFactory {
private:
    int counter;
    PseudoNameGenerator* nameGenerator;
    PseudoNameGenerator* surnameGenerator;
    PseudoIntegerGenerator* absenceGenerator;
    PseudoDoubleGenerator* scoreGenerator;
public:
    Student* getStochastic();
    StudentFactory();
    ~StudentFactory();
    int getStudentCounter();
};


#endif //STUDENTFACTORY_H

Student *StudentFactory::getStochastic() {
    std:string str = nameGenerator->getRandomName() + " " + surnameGenerator->getRandomName();
    double score[4];
    for (int i = 0; i < 4; i++) {
        score[i] = scoreGenerator->getNumber();
    }
    int absence = absenceGenerator->getNumber();
    Student *student = new Student(++counter, str, score, absence);
    return student;
}

StudentFactory::StudentFactory() {
    nameGenerator = new PseudoNameGenerator("names.txt");
    surnameGenerator = new PseudoNameGenerator("surnames.txt");
    absenceGenerator = new PseudoIntegerGenerator(0, 50);
    scoreGenerator = new PseudoDoubleGenerator(0, 10);
}

StudentFactory::~StudentFactory() {
    delete(nameGenerator);
    delete(surnameGenerator);
    delete(absenceGenerator);
    delete(scoreGenerator);
}

int StudentFactory::getStudentCounter() {
    return counter;
}
