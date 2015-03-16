#include <iostream>
#include "student.h"
#include "student_factory.h"
#include <stdio.h>
#include <iostream>
#include <ctime>


void writeElements(FILE *f, long size, StudentFactory *factory);

void readElements(FILE *f, long size);

using namespace std;


int main(int argc, char *argv[]) {

    long pageSize = atoi(argv[1]);
    long size = atoi(argv[2]);

    cout << "Pagina:" << pageSize << endl;
    cout << "Tamanho:" << size << endl;

    FILE *f = fopen("/tmp/t.bin", "wb+");
    /// Descobre quantos registros são necessário para atingir o tamanho
    /// tamanho em Mebibytes
    long regNum = (size * 1024 * 1024) / sizeof(Student);
    cout << regNum << endl;
    // Calcula as iterações com base do numero de elementos e páginas
    long iterations = regNum / pageSize;
    long remaining = regNum % pageSize;
	time_t start,end;
    StudentFactory *factory = new StudentFactory();

	time (&start);

    for (int i = 0; i < iterations; i++) {
        writeElements(f, pageSize, factory);
    }
    writeElements(f, remaining, factory);

	time (&end);
	cout << "Gravação:" << difftime (end,start) << endl;

    //delete(factory);

    rewind(f);

	time (&start);

	for (int i = 0; i < iterations; i++) {
		readElements(f, pageSize);
	}
	readElements(f, remaining);


	time (&end);
	cout << "Leitura:" << end -start << endl;


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
        //cout << student->toString() << endl;
        delete(student);
    }
}
