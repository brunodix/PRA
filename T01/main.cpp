#include <iostream>
#include "doublelist.h"

using namespace std;


int main() {

    DoubleList *doubleList = new DoubleList();
    doubleList->add(new Node(1));
    doubleList->add(new Node(2));
    doubleList->add(new Node(3));
    doubleList->add(new Node(4));
    doubleList->add(new Node(5));
    doubleList->add(new Node(6));

    cout << "=============";
    cout << doubleList->getByIndex(0)->getValue();
    cout << doubleList->getByIndex(1)->getValue();
    cout << doubleList->getByIndex(2)->getValue();


    return 0;
}


