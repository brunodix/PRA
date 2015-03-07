#ifndef GENERATOR_H
#define GENERATOR_H

#include <string>
#include "stdlib.h"
#include "doublelist.h"

using namespace std;

class Generator {
    DoubleList doubleList;
public:
    Generator(std::string fileName);
    std::string getRandomName();
};

#endif
