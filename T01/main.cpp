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
#include "constants.h"
#include "SegmentReader.h"

void writeElements(FILE *f, long size, StudentFactory *factory);

Student *readElements(FILE *f, long size);

void writeFile(FILE *f, long iterations, StudentFactory *factory);

void orderElements(FILE *fData, FILE *fIndexFile, long iterations, int comparator(const void *, const void *));

int compareByName(const void *std1, const void *std2);

Student *readElement(int index, FILE *f);

void writeIndexes(FILE *pFILE, long index[], int size);

StackBegin *menor(StackBegin *s1, StackBegin *s2, int comparator(const void *, const void *)) {
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

    FILE *fIndexName = fopen("index_name.bin", "wb+");
    orderElements(f, fIndexName, PATHWAYS, compareByName);
    //ask for indexType
    //showRegisters
    fclose(f);

    return 0;
}

void orderElements(FILE *fData, FILE *fIndexFile, long iterations, int comparator(const void *, const void *)) {
    Timer t;

    //Inicializa o arquivo de indice
    long blankIndex[REG_NUM];
    for (long i; i < REG_NUM; i++) {
        blankIndex[i] = i;
    }
    fwrite(blankIndex, sizeof(long), REG_NUM, fIndexFile);
    fflush(fIndexFile);
    delete blankIndex;

    t.start();

    for (int j = 0; j < 3; j++) {

        StackBegin stacks[iterations];

        long index[REG_PAGE_SIZE];
        SegmentReader *segmentReader = new SegmentReader(fData, fIndexFile, comparator);

        /// Executa a gravação
        for (int i = 0; i < iterations; i++) {
            stacks[i].setSegmentReader(segmentReader);
        }
        StackBegin *stkLesser;
        int counter = 0;
        do {
            StackBegin *stk1 = menor(&stacks[0], &stacks[1], comparator);
            StackBegin *stk2 = menor(&stacks[2], &stacks[3], comparator);
            StackBegin *stk3 = menor(&stacks[4], &stacks[5], comparator);
            StackBegin *stk4 = menor(&stacks[6], &stacks[7], comparator);
            stkLesser = menor(menor(stk1, stk2, comparator), menor(stk3, stk4, comparator), comparator);
            if (stkLesser != NULL && stkLesser->getSelected() != NULL) {
                index[counter++] = stkLesser->getSelected()->getEnrollNumber();
                cout << "Index:" << stkLesser->getSelected()->getEnrollNumber() << endl;
                stkLesser->stepNext();
                if (counter > REG_PAGE_SIZE) {
                    writeIndexes(fIndexFile, index, counter);
                    counter = 0;
                }
            }
        } while (stkLesser != NULL && stkLesser->getSelected() != NULL);
    }

    t.stop();
    cout << "Tempo de Ordenação:" << t.getSeconds() << endl;
}

void writeIndexes(FILE *pFILE, long index[], int size) {
    fwrite(index, STUDENT_SIZE, size, pFILE);
}

void writeFile(FILE *f, long iterations, StudentFactory *factory) {
    time_t start, end;
    time(&start);

    /// Executa a gravação
    for (int i = 0; i < iterations; i++) {
        writeElements(f, REG_PAGE_SIZE, factory);
    }

    time(&end);

    cout << "Tempo de Gravação:" << difftime(end, start) << endl;
}

void writeElements(FILE *f, long size, StudentFactory *factory) {
    for (int i = 0; i < size; i++) {
        Student *student = factory->getStochastic();
        fwrite(student, sizeof(Student), 1, f);
        delete(student);
    }
    fflush(f);
}


int compareByName(const void *std1, const void *std2) {
    Student *s1 = (Student *) std1;
    Student *s2 = (Student *) std2;

    if (s1->getName() < s2->getName()) {
        return -1;
    } else if (s1->getName() == s2->getName() && (s1->getEnrollNumber() < s2->getEnrollNumber())) {
        return -1;
    } else {
        return 1;
    }
}

