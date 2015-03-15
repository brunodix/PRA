#include <iostream>
#include "student.h"
#include "student_factory.h"

using namespace std;


int main() {

    StudentFactory *factory = new StudentFactory();
    factory->getStochastic();
    factory->getStochastic();
    factory->getStochastic();
    factory->getStochastic();
    factory->getStochastic();

    return 0;
}

Student* getStudent() {

}
