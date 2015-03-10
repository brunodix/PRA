#ifndef GENERATOR_H
#define GENERATOR_H

#include <string>
#include "stdlib.h"
#include "doublelist.h"

using namespace std;

class PseudoNameGenerator {
    DoubleList doubleList;
public:
    PseudoNameGenerator(std::string fileName);
    std::string getRandomName();
};

#endif
