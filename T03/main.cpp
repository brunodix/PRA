
#include <iostream>
#include <fstream>
#include "student.h"
#include "student_factory.h"
#include "timer.h"
#include "btree.h"


void writeElements(FILE *f, long size, StudentFactory *factory, BTree *btree);

Student *readElement(FILE *f, long index);

void writeIndex(FILE *pFILE, DoubleList<long> *pList);

void readIndex(FILE *pFILE, DoubleList<long> *pList);

int comparatorName(const void *key1, const void *key2) {
    Student *s1 = ((Key *) key1)->getStudent();
    Student *s2 = ((Key *) key2)->getStudent();
    int result = s1->getName().compare(s2->getName());
    return result;
}

int comparatorAverage(const void *key1, const void *key2) {
    Student *s1 = ((Key *) key1)->getStudent();
    Student *s2 = ((Key *) key2)->getStudent();
    if (s1->getAverage() < s2->getAverage()) {
        return -1;
    } else if (s1->getAverage() > s2->getAverage()) {
        return 1;
    } else {
        return 0;
    }
}

using namespace std;



int main(int argc, char *argv[]) {

    StudentFactory *factory = new StudentFactory();
    Timer *timer = new Timer();
    timer->start();

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

    /**
     * Descobre quantos registros são necessário para atingir o tamanho
     * tamanho em Mebibytes
     */
    long regNum = (size * 1024 * 1024) / sizeof(Student);
    cout << regNum << endl;
    // Calcula as iterações com base do numero de elementos e páginas
    long iterations = regNum / pageSize;
    long remaining = regNum % pageSize;

    BTree *btree;
//    cout << "Informe o tipo de ordenação:" << endl;
//    cout << "1 - Nome, 2 - Média" <<endl;
    int opcao;
//    cin >> opcao;
    if (opcao == 1) {
        btree = new BTree(1000, comparatorName);
    } else {
        btree = new BTree(1000, comparatorAverage);
    }

    FILE *f = fopen("data.bin", "wb+");

    /// Executa a gravação
    for (int i = 0; i < iterations; i++) {
        writeElements(f, pageSize, factory, btree);
    }
    /// Grava o resto da quantidade de registros
    writeElements(f, remaining, factory, btree);

    timer->stop();
    cout << "Tempo de gravação: " << timer->getSeconds() << "milisegundos" << endl;
    //rewind(f);

    FILE *indexFile = fopen("index.bin", "wb+");
    DoubleList<long> *indexList = new DoubleList<long>();
    btree->traverse(indexList);
    //writeIndex(indexFile, indexList);
    //delete indexList;
    //indexList = new DoubleList<long>();
    //readIndex(indexFile, indexList);

    /// Executa a gravação
    int i = 0;
    while (i < indexList->getSize()) {
	for (int j = 0; j < pageSize; j++) {
	    i++;
	    Node<long> *node = indexList->getByIndex(i);
	    if (node != NULL) {
		//cout << "::::" << j << "::::" << indexList->getByIndex(i*j);
		//cout << "getIndex" << endl;
		Student *student = readElement(f, indexList->getByIndex(i)->getValue());
                cout << i << "::" << student->toString() << endl;
	    }
	}
        getchar();
    }
    // Le o que sobrou dos registros

    btree->clear();
    delete btree;
    fclose(f);
    fclose(indexFile);

    return 0;
}

void readIndex(FILE *pFILE, DoubleList<long> *pList) {
    //pega o tamanho do arquivo
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
	    cout << count << "::";
            n = n->getNext();
        } while (n != NULL);
        rewind(pFILE);
        fwrite(arr, LONG_SIZE, count, pFILE);
        fflush(pFILE);
    }

    delete arr;
}

void writeElements(FILE *f, long size, StudentFactory *factory, BTree *btree) {
    for (int i = 0; i < size; i++) {
        Student *student = factory->getStochastic();
        btree->insert(new Key(student));
        fwrite(student, STUDENT_SIZE, 1, f);
    }
    fflush(f);
}

Student *readElement(FILE *f, long index) {
    fseek(f, (index-1) * STUDENT_SIZE, SEEK_SET);
    Student *student = new Student();
    fread(student, STUDENT_SIZE, 1, f);
    cout << endl;
    return student;
}
