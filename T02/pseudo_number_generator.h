#ifndef NUMGENERATOR_H
#define NUMGENERATOR_H

class PseudoNumberGenerator {

    int rangeStart;
    int rangeEnd;

public:
    explicit PseudoNumberGenerator(int start, int end);
    int getRangeStart() { return rangeStart; };
    int getRangeEnd() { return rangeEnd; };
};

class PseudoIntegerGenerator : PseudoNumberGenerator {

public:
    explicit PseudoIntegerGenerator(int x, int y) : PseudoNumberGenerator(x, y) {};
    int getNumber();
};

class PseudoDoubleGenerator : PseudoNumberGenerator {

public:
    explicit PseudoDoubleGenerator(int x, int y) : PseudoNumberGenerator(x, y) {};
    double getNumber();
};


#endif