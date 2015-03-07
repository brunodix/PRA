#include "generator.h"
#include "fstream"
#include "iostream"


Generator::Generator(std::string fileName) {

    srand (time(NULL));

    ifstream input(fileName );

    for( std::string line; getline( input, line ); )
    {
        doubleList.add(new Node(line));
    }
    input.close();
}

std::string Generator::getRandomName() {
    int rd = rand() % doubleList.getSize();
    cout << rd;
    return doubleList.getByIndex(rd)->getValue();
}
