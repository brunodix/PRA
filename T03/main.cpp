#include <iostream>
#include "student.h"
#include "student_factory.h"
#include "timer.h"
#include "btree.h"
#include "constants.h"


void writeElements(FILE *f, long size, StudentFactory *factory, BTree *btree);

void readElements(FILE *f, long size);

Student *readElement(FILE *f, long index);

void traverse(DoubleList<long> *list, BTree *pTree);

long *readIndex(FILE *pFILE);

void writeIndex(FILE *pFILE, DoubleList<long> *pList);

void readIndex(FILE *pFILE, DoubleList<long> *pList);

int comparatorName(const void *key1, const void *key2) {
    Student *s1 = ((Key *) key1)->getStudent();
    Student *s2 = ((Key *) key2)->getStudent();
    return s1->getName().compare(s2->getName());
}

using namespace std;



int main(int argc, char *argv[]) {


    BTree *btree = new BTree(8, comparatorName);
    if (argc != 3) {
       cout << "Informe os parâmetros: <tamanho da pagina> <tamanho em Mib>" << endl;
       return 1;
    }

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
    Timer *timer = new Timer();

    StudentFactory *factory = new StudentFactory();

    timer->start();

    /// Executa a gravação
    for (int i = 0; i < iterations; i++) {
        writeElements(f, pageSize, factory, btree);
    }
    /// Grava o resto da quantidade de registros
    writeElements(f, remaining, factory, btree);

    timer->stop();
    cout << "Tempo de gravação: " << timer->getSeconds() << "milisegundos" << endl;
    rewind(f);

    FILE *indexFile = fopen("index.bin", "wb");
    DoubleList<long> *indexList = new DoubleList<long>();
    traverse(indexList, btree);
    btree->clear();
    writeIndex(indexFile, indexList);
    readIndex(indexFile, indexList);

    /// Executa a gravação
    for (int i = 0; i < iterations; i++) {
        cout << i << endl;
        cout << indexList->getByIndex(i)->getValue() << endl;
        cout << readElement(f, indexList->getByIndex(i)->getValue())->toString() << endl;
    }
    // Le o que sobrou dos registros
    readElement(f, remaining);

    fclose(f);
    fclose(indexFile);

    return 0;
}

void readIndex(FILE *pFILE, DoubleList<long> *pList) {
    pList->clear();
    fseek(pFILE, 0, SEEK_END);
    int size = ftell(pFILE)/LONG_SIZE;
    rewind(pFILE);
    long *value = new long[size-1];
    fread(value, LONG_SIZE, size, pFILE);
    for (int i = 0; i < size; i++) {
       pList->add(new Node<long>(value[i]));
    }
}

void writeIndex(FILE *pFILE, DoubleList<long> *pList) {
    long *arr = new long[pList->getSize()];
    int count;
    Node<long> *n = pList->getByIndex(0);
    if (n != NULL) {
        do {
            arr[count++] = n->getValue();
            n = n->getNext();
        } while (n != NULL);
        rewind(pFILE);
        fwrite(arr, LONG_SIZE, count-1, pFILE);
        fflush(pFILE);
    }
}


void traverse(DoubleList<long> *doubleList, BTree *pTree) {
    pTree->traverse(doubleList);
}

void writeElements(FILE *f, long size, StudentFactory *factory, BTree *btree) {
    for (int i = 0; i < size; i++) {
        Student *student = factory->getStochastic();
        fwrite(student, STUDENT_SIZE, 1, f);
        btree->insert(new Key(student));
    }
    fflush(f);
}

void readElements(FILE *f, long count) {
        Student *students = new Student[count];
        fread(students, STUDENT_SIZE, count, f);
	for (int i = 0; i < count; i++) {
		cout << students[i].toString() << endl;
	}
	delete[] students;
        
}

Student *readElement(FILE *f, long index) {
    fseek(f, (index * STUDENT_SIZE), SEEK_SET);
    Student *student = new Student();
    fread(student, STUDENT_SIZE, 1, f);
    return student;
}