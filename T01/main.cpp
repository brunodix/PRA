#include <iostream>
#include "student.h"
#include "student_factory.h"
#include <stdio.h>
#include <iostream>
#include <ctime>
#include <printf.h>


void writeElements(FILE *f, long size, StudentFactory *factory);

void readElements(FILE *f, long size);

void writeFile(FILE *f, long iterations, StudentFactory *factory);

void readFile(FILE *f, long iterations);

using namespace std;

//Tamanho do arquivo em MEGAS
static int const SIZE = 10;
// 1 MiB
static int const MIB = 1024 * 1024;
// Número de vias
static int const PATHWAYS = 8;
// Tamanho do definição de estudante
static int const STUDENT_SIZE = sizeof(Student);
// Tamanho do arquivo final, que não tenha sobras
static int const FILE_SIZE = MIB*SIZE - (((MIB*SIZE)/PATHWAYS)%STUDENT_SIZE)*PATHWAYS;
// Numero de regitros
static int const REG_NUM = FILE_SIZE/STUDENT_SIZE;
// Tamanho das páginas de registros
static int const REG_PAGE_SIZE = REG_NUM / PATHWAYS;

int main(int argc, char *argv[]) {

    FILE *f = fopen("data.bin", "wb+");
    /**
     * Descobre quantos registros são necessário para atingir o tamanho
     * tamanho em Mebibytes
     */
    cout << REG_NUM << endl;
    // Calcula as iterações com base do numero de elementos e páginas
    long iterations = REG_NUM / REG_PAGE_SIZE;
    StudentFactory *factory = new StudentFactory();

    writeFile(f, iterations, factory);

    rewind(f);

    readFile(f, iterations);

    return 0;
}

void readFile(FILE *f, long iterations) {
    time_t start,end;
    time (&start);

    /// Executa a gravação
    for (int i = 0; i < iterations; i++) {
        readElements(f, REG_PAGE_SIZE);
    }

    time (&end);
    cout << "Tempo de Leitura:" << end -start << endl;

    fclose(f);
}

void writeFile(FILE *f, long iterations, StudentFactory *factory) {
    time_t start,end;
    time (&start);

    /// Executa a gravação
    for (int i = 0; i < iterations; i++) {
        writeElements(f, REG_PAGE_SIZE, factory);
    }

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
