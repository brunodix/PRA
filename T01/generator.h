#ifndef GENERATOR_H
#define GENERATOR_H
#include "node.h"

using namespace std;

class Generator {

public:
    Generator(void);
    string getName();
    string getSurname();
    string getFullName();
    string getDate();

};

#endif
