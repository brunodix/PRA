#include "pseudo_name_generator.h"
#include "fstream"
#include "iostream"


PseudoNameGenerator::PseudoNameGenerator(std::string fileName) {

    srand (time(NULL));

    ifstream input(fileName );

    for( std::string line; getline( input, line ); )
    {
        doubleList.add(new Node(line));
    }
    input.close();
}

std::string PseudoNameGenerator::getRandomName() {
    int rd = rand() % doubleList.getSize();
    cout << rd;
    return doubleList.getByIndex(rd)->getValue();
}
