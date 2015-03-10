#include <stdlib.h>
#include "pseudo_number_generator.h"
#include "ctime"

PseudoNumberGenerator::PseudoNumberGenerator(int start, int end) {
    rangeStart = start;
    rangeEnd = end;
    srand(time(NULL));
}

int PseudoIntegerGenerator::getNumber() {
    int f = rand();
    return getRangeStart() + (rand() % getRangeEnd());
};

double PseudoDoubleGenerator::getNumber() {
    double f = (double)rand() / RAND_MAX;
    return getRangeStart() + f * (getRangeEnd() - getRangeStart());
}