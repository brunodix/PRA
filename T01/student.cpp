#include "student.h"
#include <sstream>
#include <ostream>


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

    double total = 0;
    for (int i = 0; i < 4; i++) {
        score[i] = _score[i];
        total += _score[i];
    }
    average = total / 4;
}

std::string Student::toString() {
    std::ostringstream os ;
    os << "Matricula: " << enrollNumber;
    os << " | Faltas: " << absence;
    os << " | Nome: " << name;
    os << " | Nota 1: " << score[0];
    os << " | Nota 2: " << score[1];
    os << " | Nota 3: " << score[2];
    os << " | Nota 4: " << score[3];
    os << " | Média: " << average;
    os << " | Situação: " << status;
    os << std::endl;
    return os.str();
}

/// Retorna a Matrícula
int Student::getMatricula(){ return enrollNumber; }

/// Retorna o Nome
std::string Student::getNome(){ return name; }

/// Retorna a Média
double Student::getMedia(){ return average; }

/// Retorna a Situação
StudentStatus Student::getSituacao(){ return status; }

