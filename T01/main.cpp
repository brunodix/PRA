#include <iostream>
#include "student.h"
#include "student_factory.h"
#include <stdio.h>
#include <iostream>
#include <ctime>
#include <printf.h>


void writeElements(FILE *f, long size, StudentFactory *factory);

void readElements(FILE *f, long size);

using namespace std;

static int const MIB = 1024 * 1024;
static int const FILE_SIZE = MIB*10;
static int const PATHWAYS = 8;
static int const PAGE_SIZE = FILE_SIZE / PATHWAYS;

int main(int argc, char *argv[]) {

//    if (argc != 3) {
//       cout << "Informe os parâmetros: <tamanho da pagina> <tamanho em Mib>" << endl;
//       return 1;
//    }
//    /**
//     * Carrega os argumentos da linha de comando.
//     */
//    long pageSize = atoi(argv[1]);
//    long size = atoi(argv[2]);
//
//    cout << "Quantidade de registros da Pagina:" << pageSize << endl;
//    cout << "Tamanho do arquivo gerado em MiB:" << size << endl;

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
    time_t start,end;
    StudentFactory *factory = new StudentFactory();

    time (&start);

    /// Executa a gravação
    for (int i = 0; i < iterations; i++) {
        writeElements(f, PAGE_SIZE, factory);
    }
    /// Grava o resto da quantidade de registros
    writeElements(f, remaining, factory);

    time (&end);
    cout << "Tempo de Gravação:" << difftime (end,start) << endl;

    rewind(f);

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

void readElements(FILE *f, long count) {
        Student *students = new Student[count];
        fread(students, sizeof(Student), count, f);
	for (int i = 0; i < count; i++) {
		cout << students[i].toString() << endl;
	}
	delete[] students;
        
}
