#include <iostream>
#include "student.h"
#include "student_factory.h"
#include <ctime>
#include "btree.h"


void writeElements(FILE *f, long size, StudentFactory *factory, BTree *btree);

void readElements(FILE *f, long size);

void writeIndex(BTree *pTree);

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
    time_t start,end;
    StudentFactory *factory = new StudentFactory();

    time (&start);

    /// Executa a gravação
    for (int i = 0; i < iterations; i++) {
        writeElements(f, pageSize, factory, btree);
    }
    /// Grava o resto da quantidade de registros
    writeElements(f, remaining, factory, btree);

    writeIndex(btree);

    time (&end);
    cout << "Tempo de Gravação:" << difftime (end, start) << endl;

    rewind(f);

    time (&start);

    /// Executa a gravação
    for (int i = 0; i < iterations; i++) {
        readElements(f, pageSize);
    }
    /// Le o que sobrou dos registros
    readElements(f, remaining);

    time (&end);
    cout << "Tempo de Leitura:" << end-start << endl;

    fclose(f);

    return 0;
}

void writeIndex(BTree *pTree) {
    FILE *file = fopen("index.bin", "wb");
    pTree->traverseToFile(file);
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
