#ifndef STUDENTGENERATOR_H
#define STUDENTGENERATOR_H
#include "student.h"
#include "student_factory.h"

using namespace std;

class StudentGenerator {
    char   sName[60];
    double score[4];
    int    absence;
public:
    Student* getStudentGenerator(StudentFactory *factory);
};
#endif //STUDENTFACTORY_H
