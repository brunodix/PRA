#include <iostream>
#include "student.h"
#include "student_factory.h"
#include <stdio.h>

void writeElements(FILE *f, long size, StudentFactory *factory);

void readElements(FILE *f, long size);

using namespace std;


int main(int argc, char *argv[]) {

    long pageSize = atoi(argv[1]);
    long size = atoi(argv[2]);

    FILE *f = fopen("/tmp/t.bin", "wb+");
    /// Descobre quantos registros são necessário para atingir o tamanho
    /// tamanho em Mebibytes
    long regNum = (size * 1024 * 1024) / sizeof(Student);
    cout << regNum << endl;
    // Calcula as iterações com base do numero de elementos e páginas
    long iterations = regNum / pageSize;
    cout << iterations << endl;
    long remaining = regNum % pageSize;
    cout << remaining << endl;
    StudentFactory *factory = new StudentFactory();
    for (int i = 0; i < iterations; i++) {
        writeElements(f, pageSize, factory);
    }
    writeElements(f, remaining, factory);

    //delete(factory);

    rewind(f);

    for (int i = 0; i < iterations; i++) {
        readElements(f, pageSize);
    }
    readElements(f, remaining);


    fclose(f);

    return 0;
}

void writeElements(FILE *f, long size, StudentFactory *factory) {
    for (int i = 0; i < size; i++) {
        Student *student = factory->getStochastic();
        fwrite(student, sizeof(Student), 1, f);
        delete(student);
    }
    fflush(f);
}

void readElements(FILE *f, long size) {
    for (int i = 0; i < size; i++) {
        Student *student = new Student;
        fread(student, sizeof(Student), 1, f);
        cout << student->toString() << endl;
        delete(student);
    }
}
