#include <iostream>
#include "student.h"
#include "student_factory.h"
#include <stdio.h>
#include <iostream>
#include <ctime>
#include <printf.h>


void writeElements(FILE *f, long size, StudentFactory *factory);

void readElements(FILE *f, long size);

void writeFile(FILE *f, long iterations, long remaining, StudentFactory *factory);

void readFile(FILE *f, long iterations, long remaining);

using namespace std;

static int const MIB = 1024 * 1024;
static int const FILE_SIZE = MIB*10;
static int const PATHWAYS = 8;
static int const PAGE_SIZE = FILE_SIZE / PATHWAYS;

int main(int argc, char *argv[]) {

    FILE *f = fopen("data.bin", "wb+");
    /**
     * Descobre quantos registros são necessário para atingir o tamanho
     * tamanho em Mebibytes
     */
    long regNum = FILE_SIZE /sizeof(Student);
    cout << regNum << endl;
    // Calcula as iterações com base do numero de elementos e páginas
    long iterations = regNum / PAGE_SIZE;
    long remaining = regNum % PAGE_SIZE;
    StudentFactory *factory = new StudentFactory();

    writeFile(f, iterations, remaining, factory);

    rewind(f);

    readFile(f, iterations, remaining);

    return 0;
}

void readFile(FILE *f, long iterations, long remaining) {
    time_t start,end;
    time (&start);

    /// Executa a gravação
    for (int i = 0; i < iterations; i++) {
        readElements(f, PAGE_SIZE);
    }
    /// Le o que sobrou dos registros
    readElements(f, remaining);

    time (&end);
    cout << "Tempo de Leitura:" << end -start << endl;

    fclose(f);
}

void writeFile(FILE *f, long iterations, long remaining, StudentFactory *factory) {
    time_t start,end;
    time (&start);

    /// Executa a gravação
    for (int i = 0; i < iterations; i++) {
        writeElements(f, PAGE_SIZE, factory);
    }
    /// Grava o resto da quantidade de registros
    writeElements(f, remaining, factory);

    time (&end);
    cout << "Tempo de Gravação:" << difftime (end,start) << endl;
}

void writeElements(FILE *f, long size, StudentFactory *factory) {
    for (int i = 0; i < size; i++) {
        Student *student = factory->getStochastic();
        fwrite(student, sizeof(Student), 1, f);
        delete(student);
    }
    fflush(f);
}

void readElements(FILE *f, long count) {
        Student *students = new Student[count];
        fread(students, sizeof(Student), count, f);
	for (int i = 0; i < count; i++) {
		cout << students[i].toString() << endl;
	}
	delete[] students;
        
}
