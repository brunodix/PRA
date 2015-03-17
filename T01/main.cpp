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

    /**
     * Carrega os argumentos da linha de comando.
     */
    long pageSize = atoi(argv[1]);
    long size = atoi(argv[2]);

    cout << "Quantidade de registros da Pagina:" << pageSize << endl;
    cout << "Tamanho do arquivo gerado em MiB:" << size << endl;

    FILE *f = fopen("data.bin", "wb+");
    /**
     * Descobre quantos registros são necessário para atingir o tamanho
     * tamanho em Mebibytes
     */
    long regNum = (size * 1024 * 1024) / sizeof(Student);
    cout << regNum << endl;
    // Calcula as iterações com base do numero de elementos e páginas
    long iterations = regNum / pageSize;
    long remaining = regNum % pageSize;
    time_t start,end;
    StudentFactory *factory = new StudentFactory();

    time (&start);

    /// Executa a gravação
    for (int i = 0; i < iterations; i++) {
        writeElements(f, pageSize, factory);
    }
    /// Grava o resto da quantidade de registros
    writeElements(f, remaining, factory);

    time (&end);
    cout << "Tempo de Gravação:" << difftime (end,start) << endl;

    rewind(f);

    time (&start);

    /// Executa a gravação
    for (int i = 0; i < iterations; i++) {
        readElements(f, pageSize);
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

void readElements(FILE *f, long size) {
    for (int i = 0; i < size; i++) {
        Student *student = new Student;
        fread(student, sizeof(Student), 1, f);
        //cout << student->toString() << endl;
        delete(student);
    }
}
