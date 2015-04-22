#include <iostream>
#include "student.h"
#include "student_factory.h"
#include <stdio.h>
#include <iostream>
#include <ctime>
#include <printf.h>
#include "comparators.h"
#include "timer.h"
#include <list>
#include "tree.h"


void writeElements(FILE *f, long size, StudentFactory *factory);

Student * readElements(FILE *f, long size);

void writeFile(FILE *f, long iterations, StudentFactory *factory);

void orderElements(FILE *f, long iterations);

int compareByName(const void *std1, const void *std2);

Student* readElement(int index, FILE *f);

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
    StudentFactory *factory = new StudentFactory();

    writeFile(f, PATHWAYS, factory);

    rewind(f);

    orderElements(f, PATHWAYS);

    return 0;
}

void orderElements(FILE *f, long iterations) {
    Timer t;

    std::list<long> indexes[PATHWAYS];
    std::list<long>::iterator iterators[PATHWAYS];
    Tree<long> trees[PATHWAYS];
    for (int i = 0; i < PATHWAYS; i++){
        iterators[i]= indexes[i].begin();
    }
    t.start();

    /// Executa a gravação
    for (int i = 0; i < iterations; i++) {
        Student *elements = readElements(f, REG_PAGE_SIZE);
        qsort(elements, REG_PAGE_SIZE, STUDENT_SIZE, compareByName);
        for (int j =0; j < REG_PAGE_SIZE; j++) {
            indexes[i].insert(iterators[i], elements[j].getEnrollNumber());
        }
    }

    for (int i = 0; i < PATHWAYS; i++){
        iterators[i]= indexes[i].begin();
    }
    t.stop();
    cout << "Tempo de Leitura:" << t.getSeconds() << endl;

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

Student * readElements(FILE *f, long count) {
    Student *students = new Student[count];
    fread(students, sizeof(Student), count, f);
    return students;
        
}

int compareByName(const void *std1, const void *std2) {
    Student *s1 = (Student*) std1;
    Student *s2 = (Student*) std2;

    if (s1->getName() < s2->getName()) {
        return -1;
    } else if (s1->getName() == s2->getName()  && (s1->getEnrollNumber() < s2->getEnrollNumber())) {
        return -1;
    } else {
        return 1;
    }
}

Student* readElement(int index, FILE *f) {
        fseek(f, (index * STUDENT_SIZE), SEEK_SET);
        Student *student = new Student();
        fread(student, STUDENT_SIZE, 1, f);
        return student;
}

