#include <iostream>
#include "doublelist.h"
#include "generator.h"

using namespace std;


int main() {

    Generator *nameGenerator = new Generator("names.txt");
    Generator *surnameGenerator = new Generator("surnames.txt");
    cout << nameGenerator->getRandomName() << " " << surnameGenerator->getRandomName() << endl;
    flush(cout);
    cout << nameGenerator->getRandomName() << " " << surnameGenerator->getRandomName() << endl;
    flush(cout);
    cout << nameGenerator->getRandomName() << " " << surnameGenerator->getRandomName() << endl;
    flush(cout);
    cout << nameGenerator->getRandomName() << " " << surnameGenerator->getRandomName() << endl;
    flush(cout);
    cout << nameGenerator->getRandomName() << " " << surnameGenerator->getRandomName() << endl;
    flush(cout);

    return 0;
}


