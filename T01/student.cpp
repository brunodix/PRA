#include "student.h"
#include <stdio.h>


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

char* Student::toString() {
    char *str;
    sprintf(str, "Matricula: %d | Faltas: %d | Nome: %s | Nota 1: %0.2f | Nota 2: %0.2f | Nota 3: %0.2f | Nota 4: %0.2f | Média: %0.2f | Situação: %d", enrollNumber, absence, name, score[0], score[1], score[2], score[3], average, status);
    return str;
}
