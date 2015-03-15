#include "student.h"
#include "student_status.h"


Student::Student(int _enrollNumber, std::string _name, double *_score, int _absence) {
    enrollNumber = _enrollNumber;
    absence = _absence;
    strcpy(name, _name.c_str());

    if (average > 7) {
        status = APPROVED;
    } else if (average > 4) {
        status = EXAM;
    } else {
        status = REPROVED;
    }

    double total;
    for (int i = 0; i < 4; i++) {
        score[i] = _score[i];
        total = _score[i];
    }
    average = total / 4;
}