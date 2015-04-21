#ifndef INDEXADOR_H
#define NODE_H

#include "student.h"
#include "stdlib.h"
#include <string>

using namespace std;

/*
    Classe: Indexador
    Criado para definir um indice para a geração de ordenação dos dados do arquivo.
*/
class Indexador {
    int index;
public:
    Indexador();
    void setIndice();
    int  getIndice();
    int  getComparaIndice(Student *estudante1, Student *estudante2);
    std::string getDescricaoIndice();
};
#endif
