#ifndef COMPARATOR_H
#define COMPARATOR_H

#include "student.h"
#include "stdlib.h"
#include <string>

using namespace std;

/*
    Classe: Indexador
    Criado para definir um indice para a geração de ordenação dos dados do arquivo.
*/
class Comparator {
    int index;
public:
    Comparator();
    void setIndice();
    int  getIndice();
    int  getComparaIndice(Student *estudante1, Student *estudante2);
    std::string getDescricaoIndice();
//    int compareByName(const void *std1, const void *std2);
//    int compareByStatusAndName(const void* student1, const void* student2);
//    int compareByDescAvgAndName(const void* student1, const void* student2);
//    int compareByAscAvgAndName(const void* student1, const void* student2);
};
#endif
