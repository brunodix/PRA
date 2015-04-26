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
#include "StackBegin.h"

void writeElements(FILE *f, long size, StudentFactory *factory);

Student * readElements(FILE *f, long size);

void writeFile(FILE *f, long iterations, StudentFactory *factory);

void orderElements(FILE *f, long iterations);

int compareByName(const void *std1, const void *std2);

Student* readElement(int index, FILE *f);

StackBegin* menor(StackBegin *s1, StackBegin *s2, int comparator(const void *, const void *)) {
    if ((s1 == NULL && s1->getSelected() == NULL) && (s2 == NULL && s2->getSelected() == NULL)) {
        return NULL;
    } else if (s1->getSelected() == NULL || s1 == NULL) {
        return s2;
    } else if (s2->getSelected() == NULL || s2 == NULL) {
        return s1;
    }
    if (comparator(s1->getSelected(), s2->getSelected()) <= 0) {
        return s1;
    } else {
        return s2;
    }

}

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
static int const FILE_SIZE = MIB*SIZE;
// Numero de regitros
static int const REG_NUM = FILE_SIZE/STUDENT_SIZE;
// Tamanho das páginas de registros
static int const REG_PAGE_SIZE = 100000;


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

    t.start();

    StackBegin stacks[iterations];

    long index[REG_PAGE_SIZE];

    /// Executa a gravação
    for (int i = 0; i < iterations; i++) {
        Student *elements = readElements(f, REG_PAGE_SIZE);
        qsort(elements, REG_PAGE_SIZE, STUDENT_SIZE, compareByName);
        stacks[i].setElements(elements, REG_PAGE_SIZE);
    }
    StackBegin *stkLesser;
    int counter = 0;
    do {
        StackBegin *stk1 = menor(&stacks[0], &stacks[1], compareByName);
        StackBegin *stk2 = menor(&stacks[2], &stacks[3], compareByName);
        StackBegin *stk3 = menor(&stacks[4], &stacks[5], compareByName);
        StackBegin *stk4 = menor(&stacks[6], &stacks[7], compareByName);
        stkLesser = menor(menor(stk1, stk2, compareByName), menor(stk3, stk4, compareByName), compareByName);
        if (stkLesser != NULL && stkLesser->getSelected() != NULL) {
            index[counter++] = stkLesser->getSelected()->getEnrollNumber();
            cout << "Index:" << stkLesser->getSelected()->getEnrollNumber() << endl;
            stkLesser->stepNext();
            if (counter > REG_PAGE_SIZE) {
                cout << "Foi uma pagina";
                counter = 0;
            }
        }
    } while (stkLesser != NULL && stkLesser->getSelected() != NULL);

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

