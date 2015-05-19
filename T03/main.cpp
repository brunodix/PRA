#include <iostream>
#include "student.h"
#include "student_factory.h"
#include "timer.h"
#include "btree.h"
#include "constants.h"


void writeElements(FILE *f, long size, StudentFactory *factory, BTree *btree);

void readElements(FILE *f, long size);

Student *readElement(FILE *f, long index);

void writeIndex(FILE *file, BTree *pTree);

long *readIndex(FILE *pFILE);

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
    cout << "Tempo de gravação: " << timer->getSeconds() << endl;

    FILE *indexFile = fopen("index.bin", "wb");
    writeIndex(indexFile, btree);

    long *index = readIndex(indexFile);
    cout << index[0];
    cout << index[1];
    cout << index[2];
    cout << index[3];
    cout << index[4];
    cout.flush();



    rewind(f);
    /// Executa a gravação
//    for (int i = 0; i < iterations; i++) {
//        readElements(f, pageSize);
//    }
    /// Le o que sobrou dos registros
    //readElements(f, remaining);

    fclose(f);
    fclose(indexFile);

    return 0;
}

long *readIndex(FILE *pFILE) {
    cout << "pos0 " << ftell(pFILE) << endl ;
    fseek(pFILE, 0, SEEK_END);
    int size = ftell(pFILE)/sizeof(long);
    rewind(pFILE);
    long index[size];
    cout << "pos1 " << ftell(pFILE) << endl ;
    fread(index, sizeof(long), size, pFILE);
    int res = ferror(pFILE);
    cout << "pos2 " << ftell(pFILE) << endl ;
    return index;
}


void writeIndex(FILE *file, BTree *pTree) {
    pTree->traverseToFile(file);
    fflush(file);
}

void writeElements(FILE *f, long size, StudentFactory *factory, BTree *btree) {
    for (int i = 0; i < size; i++) {
        Student *student = factory->getStochastic();
        fwrite(student, sizeof(Student), 1, f);
        btree->insert(new Key(student));
        //delete(student);
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

Student *readElement(FILE *f, long index) {
    fseek(f, (index * STUDENT_SIZE), SEEK_SET);
    Student *student = new Student();
    fread(student, STUDENT_SIZE, 1, f);
    return student;
}
