#include <iostream>
#include "doublelist.h"
#include "pseudo_name_generator.h"
#include "pseudo_number_generator.h"
#include "student.h"

using namespace std;


int main() {

    PseudoDoubleGenerator *doubleGenerator = new PseudoDoubleGenerator(1, 2);
    cout << doubleGenerator->getNumber() << endl;
    cout << doubleGenerator->getNumber() << endl;
    cout << doubleGenerator->getNumber() << endl;
    cout << doubleGenerator->getNumber() << endl;
    cout << doubleGenerator->getNumber() << endl;
    PseudoIntegerGenerator *integerGenerator = new PseudoIntegerGenerator(1, 2);
    cout << integerGenerator->getNumber() << endl;
    cout << integerGenerator->getNumber() << endl;
    cout << integerGenerator->getNumber() << endl;
    cout << integerGenerator->getNumber() << endl;
    cout << integerGenerator->getNumber() << endl;
    cout << integerGenerator->getNumber() << endl;
    cout << integerGenerator->getNumber() << endl;

    PseudoNameGenerator *nameGenerator = new PseudoNameGenerator("names.txt");
    PseudoNameGenerator *surnameGenerator = new PseudoNameGenerator("surnames.txt");
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

Student* getStudent() {

}
